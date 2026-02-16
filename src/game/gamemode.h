#pragma once

#include "../utility/magic_enum.hpp"

enum class GameMode
{
    SINGLEPLAYER,
    MULTIPLAYER,
};

const int NUM_GAME_MODES = magic_enum::enum_count<typeof(GameMode)>();

inline GameMode &operator++(GameMode &gamemode, int)
{
    const int i = static_cast<int>(gamemode) + 1;
    gamemode = static_cast<GameMode>(i % NUM_GAME_MODES);
    return gamemode;
}

inline GameMode &operator--(GameMode &gamemode, int)
{
    const int i = static_cast<int>(gamemode) - 1;
    gamemode = static_cast<GameMode>(i < 0 ? NUM_GAME_MODES - 1 : i);
    return gamemode;
}