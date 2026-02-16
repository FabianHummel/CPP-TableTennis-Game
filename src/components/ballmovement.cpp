#include "ballmovement.h"
#include "../managers/gamemanager.h"
#include "../managers/soundmanager.h"
#include "../utility/mathutil.h"
#include "../utility/renderindexes.h"
#include "../utility/renderwindow.h"

BallMovement::BallMovement()
{
    this->name = "Ball Movement";
}

void BallMovement::on_initialize()
{
    this->transform = parent->get_component<Transform>();
    this->ball_track = MIX_CreateTrack(SoundManager::mixer);

    SoundManager::add_sound("res/sounds/ball-bounce-1.wav", "bounce 1");
    SoundManager::add_sound("res/sounds/ball-bounce-2.wav", "bounce 2");
    SoundManager::add_sound("res/sounds/ball-bounce-3.wav", "bounce 3");
}

void BallMovement::on_start()
{
    this->idle = true;
    this->transform->position = {RenderWindow::SCREEN_CENTER_X, 100, 650};
}

void BallMovement::on_update(const double delta_time)
{
    this->check_ground();
    this->check_net(delta_time);
    this->check_idle(delta_time);
    this->check_fell_off();

    this->apply_z_index();
    this->apply_gravity(delta_time);
    this->apply_friction(delta_time);
    this->apply_velocity(delta_time);
}

void BallMovement::apply_gravity(const double delta_time)
{
    this->velocity.y -= GRAVITY * delta_time * 100.0;
}

void BallMovement::apply_friction(const double delta_time)
{
    if (MathUtil::close_to_point(transform->position.y, 0.1))
    {
        auto vel = Vector3(velocity.x, 0.0f, velocity.z);
        MathUtil::move_towards_zero(vel, FRICTION * delta_time);
        velocity.x = vel.x;
        velocity.z = vel.z;
    }
}

void BallMovement::apply_velocity(const double delta_time) const
{
    transform->position.x += this->velocity.x * delta_time * 100.0;
    transform->position.y += this->velocity.y * delta_time * 100.0;
    transform->position.z += this->velocity.z * delta_time * 100.0;
}

void BallMovement::apply_z_index() const
{
    // Move ball behind when it falls off at the top
    if (transform->position.y < 0 /* && transform->getZ() < 470 */)
    {
        transform->z_index = RenderIndexes::Game::TABLE - 1;
        return;
    }

    if (transform->position.z > 470)
    {
        transform->z_index = RenderIndexes::Game::NET + 2;
    }
    else
    {
        transform->z_index = RenderIndexes::Game::NET - 2;
    }
}

void BallMovement::check_ground()
{
    if (transform->position.y >= 0)
    {
        parent->opacity = SDL_ALPHA_OPAQUE;
        return;
    }

    // Bounce off the table
    if (transform->in_table_bounds())
    {
        transform->position.y = 0;
        velocity.y *= -0.8f;

        if (velocity.y < 1.0f)
        {
            velocity.y = 0.0f;
        }

        if (idle)
        {
            velocity.y = 8.0f;
        }

        parent->opacity = SDL_ALPHA_OPAQUE;
        const float gain = (float)std::clamp(velocity.y * 0.5, 0.0, 1.0);
        SoundManager::play_sound_random(ball_track, {"bounce 1", "bounce 2", "bounce 3"}, gain);
    }
    else
    {
        // Otherwise, fall off the table and fade away
        parent->opacity = std::clamp(SDL_ALPHA_OPAQUE - (int)abs(transform->position.y), 0, 255);
    }
}

void BallMovement::check_net(const double delta_time)
{
    if (transform->position.y > 70)
    {
        return;
    }

    if (const double new_z = transform->position.z + velocity.z * delta_time * 100.0;
        transform->position.z > 470 && new_z < 470 || transform->position.z < 470 && new_z > 470)
    {
        // Ball is going to be in the net
        transform->position.z = 470;
        this->velocity.z *= -0.2f;
        this->velocity.x *= 0.5f;
    }
}

void BallMovement::check_idle(const double delta_time)
{
    if (!MathUtil::close_to_point(velocity.magnitude(), 0.3f))
    {
        idle_time = 0.0;
        return;
    }

    idle_time += delta_time;
    if (idle_time > IDLE_TIME)
    {
        GameManager::next_round();
        idle_time = 0;
    }
}

void BallMovement::check_fell_off() const
{
    if (transform->position.y < 0)
    {
        // setIdle();
    }

    if (transform->position.y < -1000)
    {
        GameManager::next_round();
    }
}

TableSideX BallMovement::get_side_x() const
{
    return transform->position.x < RenderWindow::SCREEN_CENTER_X ? TableSideX::LEFT : TableSideX::RIGHT;
}

TableSideY BallMovement::get_side_y() const
{
    return transform->position.y < RenderWindow::SCREEN_CENTER_Y ? TableSideY::BOTTOM : TableSideY::TOP;
}