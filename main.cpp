#include <SDL.h>
#include "src/renderwindow.h"
#include "src/rendermanager.h"
#include "src/ballentity.h"
#include "src/utility/vector3.h"
#include "vector"

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 1100;
const SDL_Color BG = {203, 211, 235, 255};

int main(int argc, char** argv){
    RenderWindow *window = new RenderWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Table Tennis");
    BallEntity *ball = new BallEntity();

    SDL_Delay(500);

    ball->setPosX(SCREEN_WIDTH/2.0);
    ball->setPosY(SCREEN_HEIGHT/4.0 * 3);

    ball->applyForce(
        Vector3(0.5f, 5.5f, -8.0f)
    );

    // Load pngs
    RenderTarget *tableTex = window->createTarget("../res/table.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	RenderTarget *netTex = window->createTarget("../res/net.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	RenderTarget *ballTex = window->createTarget("../res/ball.png", ball, 40, 40);
	RenderTarget *ballShadowTex = window->createTarget("../res/ballshadow.png", ball->shadow, 40, 40);

    RenderManager::addTarget(tableTex);
    RenderManager::addTarget(netTex);
    RenderManager::addTarget(ballShadowTex);
    RenderManager::addTarget(ballTex);

    bool running = true;
    while(running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                default:
                    break;
            }
        }

        ball->applyGravity();
        ball->applyFriction();
        ball->applyVelocity();
        ball->checkGround();
        ball->updateShadow();

        window->drawBG(BG);
        window->clear();

        // Render pngs
        RenderManager::renderAll(
            window->renderer
        );

        SDL_RenderPresent(
            window->renderer
        );
    }

    window->destroy();
    return 0;
}