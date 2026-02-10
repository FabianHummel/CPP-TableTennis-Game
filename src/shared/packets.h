#pragma once

#include "enet.h"

enum Packet : enet_uint32
{
//	Client -> Server (initial)
	CREATE_MATCH,
	JOIN_MATCH,
// TODO: Split the above packet types into a separate type just for connecting (uint32). \
//  The other types can be uint8

//	Client -> Server (runtime)
	CANCEL_MATCH,
	CLIENT_PUNCHED,

//	Client -> Client
	PEER_PING,
	PEER_PONG,
	PEER_ENEMY_DATA,

//	Server -> Client (response)
	MATCH_NOT_FOUND,
	MATCH_FOUND,
	MATCH_FULL,
	PUNCH_THROUGH,
	PUNCH_DONE,
};