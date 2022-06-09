//
// Created by Fabian Hummel on 16.04.22.
//

#pragma once

#include "vector"

class RenderWindow {
public:
	const static int SCREEN_WIDTH = 700;
	const static int SCREEN_HEIGHT = 1100;

    SDL_Window *window;
    SDL_Renderer *renderer;

    RenderWindow(int width, int height, const char *title);
    ~RenderWindow();

    void drawBG(SDL_Color color) const;
    void clear() const;
    void destroy() const;
};