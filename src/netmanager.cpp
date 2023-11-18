#include "netmanager.h"
#include <cstdio>
#include <vector>

namespace NetManager
{
	std::function<void(const char *match_code)> on_match_found{};
	std::function<void()> on_match_not_found{};
	std::function<void()> on_match_full{};
	std::function<void()> on_punch_fail{};
	std::function<void(ENetPeer *enemy)> on_punched{};
	std::function<void(double rtt)> on_peer_ping{};
	std::function<void()> on_enemy_data_received{};

	ENetPeer *enemy;
	ENetHost *host;
	double elapsedTime = 0;
	bool waitForPong = false;
	std::string match_code;

	void init_matchmaking()
	{
		ENetAddress hostAddress;
		hostAddress.host = ENET_HOST_ANY;
		hostAddress.port = ENET_PORT_ANY;
		host = enet_host_create(&hostAddress, 100, 2, 0, 0);
		if (host == nullptr)
		{
			fprintf (stderr, "An error occurred while trying to create an ENet host host.\n");
			return;
		}

		ENetAddress serverAddress;
		enet_address_set_host(&serverAddress, "localhost");
		serverAddress.port = 7788;

		if (!enet_host_connect(host, &serverAddress, 2, Packet::CREATE_MATCH << 26))
		{
			fprintf(stderr, "No available peers for initiating an ENet connection.\n");
			return;
		}
	}

	void join_match(const char *match_code)
	{
		ENetAddress hostAddress;
		hostAddress.host = ENET_HOST_ANY;
		hostAddress.port = ENET_PORT_ANY;
		host = enet_host_create(&hostAddress, 100, 2, 0, 0);
		if (host == nullptr)
		{
			fprintf (stderr, "An error occurred while trying to create an ENet host host.\n");
			return;
		}

		ENetAddress serverAddress;
		enet_address_set_host(&serverAddress, "localhost");
		serverAddress.port = 7788;

		unsigned int encoded = strtoul(match_code, nullptr, 36);
		if (!enet_host_connect(host, &serverAddress, 2, encoded | Packet::JOIN_MATCH << 26))
		{
			fprintf(stderr, "No available peers for initiating an ENet connection.\n");
			return;
		}
		NetManager::match_code = std::string(match_code);
	}

	void handle_response(const ENetEvent &event, Buffer &buffer)
	{
		switch (buffer.Read<Packet>())
		{
		case Packet::MATCH_FOUND: {
			NetManager::match_code = buffer.Read<std::string>();
			NetManager::on_match_found(NetManager::match_code.c_str());
			break;
		}
		case Packet::MATCH_NOT_FOUND: {
			NetManager::on_match_not_found();
			break;
		}
		case Packet::MATCH_FULL: {
			NetManager::on_match_full();
			break;
		}
		case Packet::PUNCH_THROUGH: {
			ENetAddress address = buffer.Read<ENetAddress>();
			char newPeerIp[40];
			enet_address_get_host_ip(&address, newPeerIp, 40);
			printf("Punching through to %s:%d\n", newPeerIp, address.port);
			enemy = enet_host_connect(host, &address, 2, 0);
			if (enemy == nullptr)
			{
				fprintf(stderr, "No available peers for initiating an ENet connection.\n");
				on_punch_fail();
				return;
			}
			Buffer b;
			b.Write(Packet::CLIENT_PUNCHED);
			b.Write(NetManager::match_code);
			ENetPacket *packet = enet_packet_create(b.GetBuffer(), b.GetSize(), ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(event.peer, 0, packet);
			break;
		}
		case Packet::PUNCH_DONE: {
			enet_peer_disconnect(event.peer, 0);
			on_punched(enemy);
		}
		case Packet::PEER_PING: {
			Buffer b;
			b.Write(Packet::PEER_PONG);
			ENetPacket *packet = enet_packet_create(b.GetBuffer(), b.GetSize(), ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(event.peer, 0, packet);
			break;
		}
		case Packet::PEER_PONG: {
			on_peer_ping(elapsedTime);
			waitForPong = false;
			break;
		}
		case Packet::PEER_ENEMY_DATA: {
			on_enemy_data_received();
			break;
		}
		default:
			break;
		}
	}

	void update(double deltaTime)
	{
		if (host == nullptr) return;

		elapsedTime += deltaTime;
		if (!waitForPong && enemy != nullptr && enemy->state == ENET_PEER_STATE_CONNECTED && elapsedTime > 0.5)
		{
			Buffer b;
			b.Write(Packet::PEER_PING);
			ENetPacket *packet = enet_packet_create(b.GetBuffer(), b.GetSize(), ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(enemy, 0, packet);
			elapsedTime = 0;
			waitForPong = true;
		}

		ENetEvent event;
		if (enet_host_service(host, &event, 0) > 0) {
			char ip[40];
			enet_address_get_host_ip(&event.peer->address, ip, 40);

			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT: {
				printf("Connected to %s:%d\n", ip, (int)event.peer->address.port);
				break;
			}
			case ENET_EVENT_TYPE_DISCONNECT: {
				printf("Disconnected from %s:%d\n", ip, (int)event.peer->address.port);
				break;
			}
			case ENET_EVENT_TYPE_RECEIVE: {
				Buffer b((char*)event.packet->data, event.packet->dataLength);
				handle_response(event, b);
				enet_packet_destroy(event.packet);
				break;
			}
			case ENET_EVENT_TYPE_NONE: {
				break;
			} }
		}
	}
}