#pragma once

#include "componentsystem.h"

struct Positions
{
    int top, right, bottom, left;
};

class NineSlice : public Component
{
private:
    SDL_Texture* texture{};
    SDL_Renderer* renderer;
    Transform* transform{};
    Positions positions{};
    const char* img;

public:
    bool visible = true;

    NineSlice(const char* img, Positions positions, SDL_Renderer* renderer);

    void on_initialize() override;
    void on_start() override;
    void on_update(double delta_time) override;
    void on_delete() override;

    void setImage(const char* img, Positions positions);
};