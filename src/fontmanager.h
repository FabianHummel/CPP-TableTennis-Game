#pragma once

#include <SDL_ttf.h>

namespace FontManager
{
	constexpr int DEFAULT = 42;
	constexpr int BIG = 64;

	extern TTF_Font *main;
	void init();
	void close();
};
