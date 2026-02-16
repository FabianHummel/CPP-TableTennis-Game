#include "../managers/gamemanager.h"
#include "../components/ballmovement.h"
#include "../components/transform.h"
#include "../managers/ecsmanager.h"
#include "../utility/renderwindow.h"

namespace GameManager
{
    Pane* current_pane = {};
}

void GameManager::next_round()
{
    Entity* ball = EcsManager::find_entity("Ball");
    Transform* transform = ball->get_component<Transform>();
    transform->position = {RenderWindow::SCREEN_CENTER_X, 10, 650};

    BallMovement* ballMovement = ball->get_component<BallMovement>();
    ballMovement->idle = true;
    ballMovement->velocity = {0, 8, 0};
}

void GameManager::switch_scene(const Pane* from, Pane* to)
{
    delete from;

    current_pane = to;
    EcsManager::initialize();
    current_pane->on_start();
    EcsManager::start();
}