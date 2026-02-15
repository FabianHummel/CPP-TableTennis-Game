#pragma once

#include <SDL3_ttf/SDL_ttf.h>

namespace FontManager
{
	constexpr int BIG = 64;
	constexpr int DEFAULT = 42;
	constexpr int SMALL = 32;

	extern TTF_Font *main;
	extern TTF_Font *mono;
	void init();
	void close();
};
