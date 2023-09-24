#include "netmanager.h"
#include <cstdio>
#include <vector>

namespace NetManager
{
	std::vector<ENetPeer*> remote_peers;
	ENetHost *client;

	void init_matchmaking()
	{
		client = enet_host_create(nullptr, 1, 2, 0, 0);
		if (client == nullptr)
		{
			fprintf (stderr, "An error occurred while trying to create an ENet client host.\n");
			return;
		}

		ENetAddress serverAddress;
		enet_address_set_host(&serverAddress, "localhost");
		serverAddress.port = 7788;
		ENetPeer *peer = enet_host_connect(client, &serverAddress, 2, Request::CREATE_MATCH << 26);
		if (peer == nullptr)
		{
			fprintf(stderr, "No available peers for initiating an ENet connection.\n");
			return;
		}
	}

	void join_match(const char *match_code)
	{
		client = enet_host_create(nullptr, 1, 2, 0, 0);
		if (client == nullptr)
		{
			fprintf (stderr, "An error occurred while trying to create an ENet client host.\n");
			return;
		}

		ENetAddress serverAddress;
		enet_address_set_host(&serverAddress, "localhost");
		serverAddress.port = 7788;

		unsigned int encoded = strtoul(match_code, nullptr, 36);
		ENetPeer *peer = enet_host_connect(client, &serverAddress, 2, encoded | Request::JOIN_MATCH << 26);
		if (peer == nullptr)
		{
			fprintf(stderr, "No available peers for initiating an ENet connection.\n");
			return;
		}
	}

	void handle_response(const ENetEvent &event, Buffer &buffer)
	{
		switch (buffer.Read<Response>())
		{
		case Response::MATCH_FOUND: {
			std::string match_code = buffer.Read<std::string>();
			printf("Match found! Code: %s\n", match_code.c_str());
			break;
		}
		case Response::MATCH_NOT_FOUND:
			printf("Match not found!\n");
			break;
		case MATCH_FULL:
			printf("Match is full!\n");
			break;
		case PUNCH_THROUGH:
			ENetAddress address = buffer.Read<ENetAddress>();
			printf("Punching through to %u:%u\n", address.host, address.port);
			break;
		}
	}

	void update()
	{
		if (client == nullptr) return;

		ENetEvent event;
		while (enet_host_service(client, &event, 0) > 0) {
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
				printf("Data received! %d bytes from %s\n", (int)event.packet->dataLength, ip);
				Buffer b((char*)event.packet->data, event.packet->dataLength);
				handle_response(event, b);
				enet_packet_destroy(event.packet);
				break;
			}
			case ENET_EVENT_TYPE_NONE: {
				break;
			}
			}
		}
	}
}