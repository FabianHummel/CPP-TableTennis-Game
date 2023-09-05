#pragma once

#include "../utility/magic_enum.hpp"

enum class GameMode
{
	SINGLEPLAYER,
	MULTIPLAYER,
};

const int enum_length = magic_enum::enum_count<typeof(GameMode)>();

inline GameMode &operator++(GameMode &gamemode, int)
{
	const int i = static_cast<int>(gamemode) + 1;
	gamemode = static_cast<GameMode>(i % enum_length);
	return gamemode;
}

inline GameMode &operator--(GameMode &gamemode, int)
{
	const int i = static_cast<int>(gamemode) - 1;
	gamemode = static_cast<GameMode>(i < 0 ? enum_length - 1 : i);
	return gamemode;
}
