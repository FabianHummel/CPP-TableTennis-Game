#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
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
    RenderManager *manager = new RenderManager(window->renderer);

    BallEntity *ball = new BallEntity();

    SDL_Delay(500);

    ball->setPosX(SCREEN_WIDTH/3.0);
    ball->setPosY(SCREEN_HEIGHT/3.0 * 2);

    ball->applyForce(
    Vector3(0.0f, 13.0f, 0.0f)
    );

    // Load pngs
    RenderTarget *tableTex = window->createTarget("../res/table.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    RenderTarget *netTex = window->createTarget("../res/net.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    RenderTarget *ballTex = window->createTarget("../res/ball.png", ball, 40, 40);
    RenderTarget *ballShadowTex = window->createTarget("../res/ballshadow.png", ball->shadow, 40, 40);

    manager->addTarget(tableTex);
    manager->addTarget(netTex);
    manager->addTarget(ballShadowTex);
    manager->addTarget(ballTex);

//    manager->move(3, 1);

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

//        ball->moveByX(
//            (float) ( sin(SDL_GetTicks()/500.0) )
//        );
//
//        ball->moveByY(
//            (float) ( cos(SDL_GetTicks()/500.0) )
//        );

        ball->applyGravity();
        ball->applyFriction();
        ball->applyVelocity();
        ball->checkGround();
        ball->updateShadow();

        window->drawBG(BG);
        window->clear();

        // Render pngs
        manager->renderAll();

        SDL_RenderPresent(window->renderer);
    }

    window->destroy();
    return 0;
}