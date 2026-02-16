#include "powerbar.h"
#include "../managers/ecsmanager.h"
#include "ballmovement.h"
#include "prediction.h"
#include "spriterenderer.h"
#include <cstdio>

PowerBar::PowerBar()
{
    this->name = "Power Bar";
}

void PowerBar::on_initialize()
{
    indicator = EcsManager::find_entity("Indicator")->get_component<Transform>();
    indicator_sprite = EcsManager::find_entity("Indicator")->get_component<SpriteRenderer>();
    ball = EcsManager::find_entity("Ball")->get_component<BallMovement>();

    Entity *powerbox_entity = EcsManager::find_entity("Powerbox");
    powerbox = powerbox_entity->get_component<Transform>();
    powerbox_sprite = powerbox_entity->get_component<SpriteRenderer>();

    Entity *powerbar_entity = EcsManager::find_entity("PowerBar");
    powerbar = powerbar_entity->get_component<Transform>();
    powerbar_sprite = powerbar_entity->get_component<SpriteRenderer>();

    Entity *prediction_entity = EcsManager::find_entity("Prediction");
    prediction = prediction_entity->get_component<Prediction>();
}

void PowerBar::on_event(const SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_EVENT_MOUSE_BUTTON_DOWN: {
        float x, y;
        SDL_GetMouseState(&x, &y);
        on_click(x * 2, y * 2);
        break;
    }
    case SDL_EVENT_MOUSE_BUTTON_UP: {
        on_release();
        break;
    }
    case SDL_EVENT_MOUSE_MOTION: {
        float x, y;
        SDL_GetMouseState(&x, &y);
        on_drag(x * 2, y * 2);
        break;
    }
    default:
        break;
    }
}

void PowerBar::set_progress(const float v, float y)
{
    this->size = v;

    const float progress = size / 100.0f * 250;
    powerbar_sprite->set_src_rect({0, 250.0f - progress, 250, progress});

    powerbar->scale.y = size / 100.0f * 70;
}

void PowerBar::on_start()
{
    indicator_sprite->visible = false;
    powerbox_sprite->visible = false;
    powerbar_sprite->visible = false;
}

void PowerBar::on_update(double delta_time)
{
    if (is_dragging)
    {
        const Vector3 force = calculate_force();
        prediction->on_predict(force);
    }
}

Vector3 PowerBar::calculate_force() const
{
    const double length = sqrt(delta_x * delta_x + delta_y * delta_y);
    const double force_x = -(double)delta_x / length * strength * 7.0;
    const double force_y = -(double)delta_y / length * strength * 7.0;
    return {(float)force_x, 8.f, (float)force_y};
}

void PowerBar::on_click(const float x, const float y)
{
    is_dragging = true;
    start_x = x;
    start_y = y;
    // printf("began mouse drag at: %d, %d\n", startX, startY);

    indicator->position = {start_x, 0.0f, start_y};
    powerbox->position = {start_x - 100.0f, 0.0f, start_y};
    powerbar->position = {start_x - 100.0f, 0.0f, start_y + powerbox->scale.y / 2.0f};
}

void PowerBar::on_release()
{
    indicator_sprite->visible = false;
    powerbox_sprite->visible = false;
    powerbar_sprite->visible = false;

    is_dragging = false;
    // printf("ended mouse drag at: %d, %d, ", currentX, currentY);
    // printf("with a delta of: %d, %d ", deltaX, deltaY);
    // printf("and an angle of: %d°\n", angle);

    if (strength > 0.1f && ball->parent->transform->scale.y > -10.0f)
    {
        ball->idle = false;

        const Vector3 force = calculate_force();
        ball->velocity = force;
    }

    strength = 0.0f;
}

void PowerBar::on_drag(const float x, const float y)
{
    if (is_dragging)
    {
        indicator_sprite->visible = true;
        powerbox_sprite->visible = true;
        powerbar_sprite->visible = true;

        const float current_x = x;
        const float current_y = y;

        delta_x = current_x - start_x;
        delta_y = current_y - start_y;

        const float angle = 180.0f - atan2(delta_x, delta_y) * 180.0f / (float)M_PI;
        indicator->rotation = angle;

        strength = std::clamp(sqrt(delta_x * delta_x + delta_y * delta_y) / 200.0f, 0.0f, 1.0f);
        set_progress(strength * 100.0f, start_y);
    }
}