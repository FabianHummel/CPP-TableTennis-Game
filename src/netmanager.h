#pragma once

#include <enet/enet.h>
#include <thread>
#include "shared/buffer.h"
#include "shared/packets.h"

namespace NetManager
{
	extern std::vector<ENetPeer*> remote_peers;
	extern ENetHost *client;

	void init_matchmaking();
	void join_match(const char *match_code);
	void handle_response(const ENetEvent &event, Buffer &buffer);
	void update();
}