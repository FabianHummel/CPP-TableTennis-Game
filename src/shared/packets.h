#include <enet/enet.h>

enum Request : enet_uint32
{
	CREATE_MATCH,
	JOIN_MATCH,
};

enum Command : uint8_t
{
	CANCEL_MATCH,
};

enum Response : uint8_t
{
	MATCH_NOT_FOUND,
	MATCH_FOUND,
	MATCH_FULL,
	PUNCH_THROUGH,
};