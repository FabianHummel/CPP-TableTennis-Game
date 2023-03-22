#include "circle.h"
#include "SDL_render.h"
#include "SDL.h"

void CircleDrawer::DrawCircle(int posX, int posY, int radius, SDL_Color color, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int y = 0; y < radius * 2; y++) {
        for (int x = 0; x < radius * 2; x++) {
            int dx = radius - x; // horizontal offset
            int dy = radius - y; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + posX, y + posY);
            }
        }
    }
}
