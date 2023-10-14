#include "src/shared/buffer.h"
#include "src/shared/packets.h"
#include <cstdio>
#include <stdlib.h>
#include <random>
#include <string>
#include <enet/enet.h>
#include <unordered_map>
#include <vector>

typedef struct {
	bool punched; // NAT punch-through
	ENetPeer *peer;
} Client;

static std::vector<ENetPeer*> peers;
static std::unordered_map<std::string, std::pair<Client, Client>> matches;
static const char* alphanum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/// <summary>
/// Converts an unsigned integer to a string.
/// Based on <a href="https://stackoverflow.com/a/43888717">this</a> StackOverflow answer.
/// char* s must point to the end of the string.
/// </summary>
void utoa(unsigned x, char *s, int radix)
{
	for (; x; x/=radix) *--s = alphanum[x%radix];
}

void handle_request(const ENetEvent &event, Packet request)
{
	switch (request >> 26)
	{
	case Packet::CREATE_MATCH: {
		std::string match_code(5, '\0');
		do {
			static std::random_device rd;
			static std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(0, 35);
			for (int i = 0; i < 5; i++) {
				match_code[i] = alphanum[dis(gen)];
			}
		} while (matches.find(match_code) != matches.end());
		matches[match_code] = std::make_pair(
			Client { false, event.peer },
			Client { false, nullptr });

		Buffer b;
		b.Write(Packet::MATCH_FOUND);
		b.Write(match_code);
		ENetPacket *packet = enet_packet_create(b.GetBuffer(), b.GetSize(), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(event.peer, 0, packet);
		break;
	}

	case Packet::JOIN_MATCH: {
		std::string match_code(5, '\0');
		utoa(request & 0x03FFFFFF, &match_code[5], 36);

		if (matches.find(match_code) == matches.end())
		{
			Buffer b;
			b.Write(Packet::MATCH_NOT_FOUND);
			ENetPacket *packet = enet_packet_create(b.GetBuffer(), b.GetSize(), ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(event.peer, 0, packet);
			enet_peer_disconnect(event.peer, 0);
			break;
		}
		std::pair<Client, Client> &match = matches.at(match_code);
		if (match.second.peer != nullptr && match.second.peer->state == ENET_PEER_STATE_CONNECTED)
		{
			Buffer b;
			b.Write(Packet::MATCH_FULL);
			ENetPacket *packet = enet_packet_create(b.GetBuffer(), b.GetSize(), ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(event.peer, 0, packet);
			enet_peer_disconnect(event.peer, 0);
			break;
		}
		else
		{
			match.second.peer = event.peer;

			Buffer b1;
			b1.Write(Packet::PUNCH_THROUGH);
			b1.Write(match.first.peer->address);
			ENetPacket *packet1 = enet_packet_create(b1.GetBuffer(), b1.GetSize(), ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(match.second.peer, 0, packet1);

			Buffer b2;
			b2.Write(Packet::PUNCH_THROUGH);
			b2.Write(match.second.peer->address);
			ENetPacket *packet2 = enet_packet_create(b2.GetBuffer(), b2.GetSize(), ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(match.first.peer, 0, packet2);
		}
		break;
	}
	}
}

void handle_command(const ENetEvent &event, Buffer &buffer)
{
	switch (buffer.Read<Packet>())
	{
	case Packet::CANCEL_MATCH: {
		std::string match_code = buffer.Read<std::string>();
		if (matches.count(match_code) && matches[match_code].first.peer == event.peer)
		{
			matches.erase(match_code);
			auto peers = matches[match_code];
			enet_peer_disconnect(peers.first.peer, 0);
			enet_peer_disconnect(peers.second.peer, 0);
		}
		break;
	}
	case Packet::CLIENT_PUNCHED: {
		std::string match_code = buffer.Read<std::string>();
		if (matches.count(match_code))
		{
			std::pair<Client, Client>& peers = matches[match_code];
			if (peers.first.peer == event.peer) {
				peers.first.punched = true;
			}
			if (peers.second.peer == event.peer) {
				peers.second.punched = true;
			}
			if (peers.first.punched && peers.second.punched) {
				Buffer b;
				b.Write(Packet::PUNCH_DONE);
				ENetPacket *packet = enet_packet_create(b.GetBuffer(), b.GetSize(), ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peers.first.peer, 0, packet);
				enet_peer_send(peers.second.peer, 0, packet);
			}
		}
		break;
	}
	default:
		break;
	}
}

int main(int argc, char **argv)
{
	fprintf(stdout, "Starting host server...\n");

	if (enet_initialize() < 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return EXIT_FAILURE;
	}

	ENetAddress address;
	address.host = ENET_HOST_ANY;
	address.port = 7788;
	ENetHost *server = enet_host_create(&address, 100, 2, 0, 0);

	if (server == nullptr)
	{
		fprintf(stderr, "An error occurred while trying to create an ENet server host.\n");
		return EXIT_FAILURE;
	}

	fprintf(stdout, "Listening on port %u\n", address.port);

	while (true)
	{
		ENetEvent event;
		if (enet_host_service(server, &event, 1000) > 0)
		{
			char ip[40];
			enet_address_get_host_ip(&event.peer->address, ip, 40);

			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT: {
				fprintf(stdout, "\rA new host connected from %s:%u.\n", ip, event.peer->address.port);
				handle_request(event, (Packet)event.data);
				peers.push_back(event.peer);
				break;
			}
			case ENET_EVENT_TYPE_DISCONNECT: {
				fprintf(stdout, "\r%s:%u disconnected.\n", ip, event.peer->address.port);
				event.peer->data = nullptr;
				peers.erase(std::find(peers.begin(), peers.end(), event.peer));
				break;
			}
			case ENET_EVENT_TYPE_RECEIVE: {
				fprintf(stdout, "\rPacket received from %s:%u.\n", ip, event.peer->address.port);
				Buffer b ((char*)event.packet->data, event.packet->dataLength);
				handle_command(event, b);
				enet_packet_destroy(event.packet);
				break;
			}
			case ENET_EVENT_TYPE_NONE: {
				break;
			}
			}
		}

		printf("\r[INFO] %zu peers", peers.size());
		fflush(stdout);
	}

	enet_host_destroy(server);
	enet_deinitialize();
	return 0;
}