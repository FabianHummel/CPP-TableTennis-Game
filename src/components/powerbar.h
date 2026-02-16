#pragma once

#include "ballmovement.h"
#include "componentsystem.h"
#include "prediction.h"
#include "spriterenderer.h"

class PowerBar : public Component
{
private:
    float size{0};
    bool is_dragging{0};
    float start_x{0}, start_y{0};
    float delta_x{0}, delta_y{0};
    float strength{0};

    BallMovement* ball{nullptr};
    Transform* indicator{nullptr};
    SpriteRenderer* indicator_sprite{nullptr};
    Transform* powerbox{nullptr};
    SpriteRenderer* powerbox_sprite{nullptr};
    Transform* powerbar{nullptr};
    SpriteRenderer* powerbar_sprite{nullptr};
    Prediction* prediction{nullptr};

    void on_click(float x, float y);
    void on_release();
    void on_drag(float x, float y);
    void set_progress(float v, float y);
    Vector3 calculate_force() const;

public:
    PowerBar();

    void on_initialize() override;
    void on_start() override;
    void on_update(double delta_time) override;
    void on_event(const SDL_Event* event) override;
};