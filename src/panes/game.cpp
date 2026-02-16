#include "game.h"
#include "../components/ballmovement.h"
#include "../components/button.h"
#include "../components/powerbar.h"
#include "../components/shadowtransformer.h"
#include "../components/spriterenderer.h"
#include "../managers/ecsmanager.h"
#include "../managers/errormanager.h"
#include "../managers/gamemanager.h"
#include "../managers/netmanager.h"
#include "../utility/renderindexes.h"
#include "../utility/renderwindow.h"
#include "home.h"

GamePane::GamePane(SDL_Renderer *renderer) : Pane(renderer)
{
    NetManager::on_timeout = [this]
    {
        ErrorManager::queue_error("Connection timed out.\nCheck your connection.");
        this->back();
    };

    set_entity(table, new Entity("Table"))
        ->transform
        ->apply({0, 0, 0}, {RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT}, {0.0f, 0.0f}, 0.0f,
                RenderIndexes::Game::TABLE)
        ->add_component(new SpriteRenderer("res/table.png", renderer));

    set_entity(net, new Entity("Net"))
        ->transform
        ->apply({RenderWindow::SCREEN_CENTER_X, 0, RenderWindow::SCREEN_CENTER_Y - 100},
                {RenderWindow::SCREEN_WIDTH, 129}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Game::NET)
        ->add_component(new SpriteRenderer("res/net.png", renderer));

    set_entity(shadow, new Entity("Shadow"))
        ->transform->apply({0, 0, 0}, {40, 40}, {0.5f, 0.0f}, 0.0f, RenderIndexes::Game::DEFAULT)
        ->add_component(new SpriteRenderer("res/shadow.png", renderer));

    set_entity(ball, new Entity("Ball"))
        ->transform->apply({0, 0, 0}, {40, 40}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Game::DEFAULT)
        ->add_component(new SpriteRenderer("res/ball.png", renderer))
        ->add_component(new BallMovement())
        ->add_component(new ShadowTransformer(shadow));

    set_entity(indicator, new Entity("Indicator"))
        ->transform->apply({0, 0, 0}, {112, 112}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Game::UI + 1)
        ->add_component(new SpriteRenderer("res/indicator.png", renderer));

    set_entity(power_bar, new Entity("PowerBar"))
        ->transform->apply({0, 0, 0}, {70, 70}, {0.5f, 1.0f}, 0.0f, RenderIndexes::Game::UI + 0)
        ->add_component(new SpriteRenderer("res/powerbar.png", renderer))
        ->add_component(new PowerBar());

    set_entity(power_box, new Entity("Powerbox"))
        ->transform->apply({0, 0, 0}, {70, 70}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Game::UI + 1)
        ->add_component(new SpriteRenderer("res/powerbox.png", renderer));

    set_entity(prediction_segments, new Entity("Prediction"))
        ->transform
        ->apply({0, 0, 0}, {RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT}, {0.0f, 0.0f}, 0.0f,
                RenderIndexes::Game::PREDICTION)
        ->add_component(new Prediction("res/predictionsegment.png", renderer));

    set_entity(back_button, new Entity("Back-Button"))
        ->add_component(new SpriteRenderer("res/menuarrow.png", renderer))
        ->add_component(new Button(std::bind(&GamePane::back, this)))
        ->transform->apply({40, 0, 40}, {50, 50}, {0.5f, 0.5f}, 180.0f, RenderIndexes::Menu::UI);
}

GamePane::~GamePane()
{
    delete table;
    delete net;
    delete ball;
    delete shadow;
    delete indicator;
    delete power_bar;
    delete power_box;
    delete prediction_segments;
}

void GamePane::on_event(const SDL_Event *event)
{
    if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE)
    {
        this->back();
    }
}

void GamePane::back() const
{
    EcsManager::clear();
    Pane *pane = new HomePane(renderer);
    GameManager::switch_scene(this, pane);
}