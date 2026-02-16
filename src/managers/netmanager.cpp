#include "netmanager.h"
#include "../shared/packets.h"
#include <SDL3/SDL_log.h>

#include "errormanager.h"

namespace NetManager
{
    std::function<void(const char* match_code)> on_match_found{};
    std::function<void()> on_match_not_found{};
    std::function<void()> on_match_full{};
    std::function<void()> on_punch_fail{};
    std::function<void(ENetPeer * enemy)> on_punched{};
    std::function<void(double rtt)> on_peer_ping{};
    std::function<void(const std::string & enemyName, bool readyStatus)> on_enemy_data_received{};
    std::function<void(bool readyStatus)> on_enemy_ready_status_received{};
    std::function<void()> on_timeout{};

    ENetPeer* enemy;
    ENetHost* host;
    double elapsed_time = 0;
    bool wait_for_pong = false;
    std::string match_code;
}

bool NetManager::start(const char* match_code)
{
    ENetAddress host_address;
    host_address.host = ENET_HOST_ANY;
    host_address.port = ENET_PORT_ANY;
    host = enet_host_create(&host_address, 1, 1, 0, 0);
    if (host == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "An error occurred while trying to create an ENet host.\n");
        return false;
    }

    ENetAddress server_address;
    enet_address_set_host(&server_address, "localhost");
    server_address.port = 7788;

    enet_uint32 server_data;
    if (match_code != nullptr && strlen(match_code) > 0)
    {
        const unsigned int encoded = strtoul(match_code, nullptr, 36);
        server_data = encoded | JOIN_MATCH << 26;
    }
    else
    {
        server_data = CREATE_MATCH << 26;
    }

    if (!enet_host_connect(host, &server_address, 1, server_data))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "No available peers for initiating an ENet connection.\n");
        return false;
    }

    char server_ip[40];
    enet_address_get_host_ip(&server_address, server_ip, 40);

    ENetEvent event;
    if (enet_host_service(host, &event, 1000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
    {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Connected to %s:%d.\n", server_ip, server_address.port);
        return true;
    }

    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Connection to %s:%d failed.\n", server_ip, server_address.port);
    enet_host_destroy(host);
    host = nullptr;
    return false;
}

void NetManager::handle_response(const ENetEvent& event, Buffer& buffer)
{
    switch (buffer.read<Packet>())
    {
    case MATCH_FOUND:
        {
            match_code = buffer.read<std::string>();
            on_match_found(match_code.c_str());
            break;
        }
    case MATCH_NOT_FOUND:
        {
            on_match_not_found();
            break;
        }
    case MATCH_FULL:
        {
            on_match_full();
            break;
        }
    case PUNCH_THROUGH:
        {
            const auto address = buffer.read<ENetAddress>();
            char new_peer_ip[40];
            enet_address_get_host_ip(&address, new_peer_ip, 40);
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Punching through to %s:%d.\n", new_peer_ip, address.port);
            enemy = enet_host_connect(host, &address, 2, 0);
            if (enemy == nullptr)
            {
                SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "No available peers for initiating an ENet connection.\n");
                on_punch_fail();
                return;
            }
            Buffer b(128);
            b.write(CLIENT_PUNCHED);
            b.write(match_code);
            ENetPacket* packet = enet_packet_create(b.data(), b.size(), ENET_PACKET_FLAG_RELIABLE);
            enet_peer_send(event.peer, 0, packet);
            break;
        }
    case PUNCH_DONE:
        {
            enet_peer_disconnect(event.peer, 0);
            on_punched(enemy);
        }
    case PEER_PING:
        {
            Buffer b(sizeof(Packet));
            b.write(PEER_PONG);
            ENetPacket* packet = enet_packet_create(b.data(), b.size(), ENET_PACKET_FLAG_RELIABLE);
            enet_peer_send(event.peer, 0, packet);
            break;
        }
    case PEER_PONG:
        {
            on_peer_ping(elapsed_time);
            wait_for_pong = false;
            break;
        }
    case PEER_ENEMY_DATA:
        {
            const auto enemy_name = buffer.read<std::string>();
            const bool ready_status = buffer.read<bool>();
            on_enemy_data_received(enemy_name, ready_status);
            break;
        }
    case PEER_ENEMY_READY_STATUS:
        {
            const bool ready_status = buffer.read<bool>();
            on_enemy_ready_status_received(ready_status);
            break;
        }
    default:
        break;
    }
}

void NetManager::update(const double delta_time)
{
    if (host == nullptr)
    {
        return;
    }

    elapsed_time += delta_time;
    if (!wait_for_pong && enemy != nullptr && enemy->state == ENET_PEER_STATE_CONNECTED && elapsed_time > 0.5)
    {
        Buffer b(sizeof(Packet));
        b.write(PEER_PING);
        ENetPacket* packet = enet_packet_create(b.data(), b.size(), ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(enemy, 0, packet);
        elapsed_time = 0;
        wait_for_pong = true;
    }

    ENetEvent event;
    if (enet_host_service(host, &event, 0) != 0)
    {
        char ip[40];
        enet_address_get_host_ip(&event.peer->address, ip, 40);

        switch (event.type)
        {
        case ENET_EVENT_TYPE_CONNECT:
            {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Connected to %s:%d.\n", ip, (int)event.peer->address.port);
                break;
            }
        case ENET_EVENT_TYPE_DISCONNECT:
            {
                SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Disconnected from %s:%d.\n", ip,
                            (int)event.peer->address.port);
                break;
            }
        case ENET_EVENT_TYPE_RECEIVE:
            {
                Buffer b((char*)event.packet->data, event.packet->dataLength);
                handle_response(event, b);
                enet_packet_destroy(event.packet);
                break;
            }
        case ENET_EVENT_TYPE_NONE:
            break;
        case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
            on_timeout();
            break;
        }
    }
}