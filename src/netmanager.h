#pragma once

#include <enet/enet.h>
#include <thread>
#include <functional>
#include "shared/buffer.h"
#include "shared/packets.h"

namespace NetManager
{
	extern std::function<void(const char *match_code)> on_match_found;
	extern std::function<void()> on_match_not_found;
	extern std::function<void()> on_match_full;
	extern std::function<void()> on_punch_fail;
	extern std::function<void(ENetPeer *enemy)> on_punched;
	extern std::function<void(double rtt)> on_peer_ping;
	extern std::function<void()> on_enemy_data_received;

	void init_matchmaking();
	void join_match(const char *match_code);
	void handle_response(const ENetEvent &event, Buffer &buffer);
	void update(double deltaTime);
}