#include "shadowtransformer.h"
#include "spriterenderer.h"

ShadowTransformer::ShadowTransformer(Entity* shadow)
{
    this->name = "Shadow Transformer";
    this->target = shadow;
}

void ShadowTransformer::on_initialize()
{
    this->ball = parent->get_component<Transform>();
    this->transform = target->get_component<Transform>();
}

void ShadowTransformer::on_update(double delta_time)
{
    // TODO: Push new values instead of pulling them! (Prevent lag behind)
    transform->position.x = ball->position.x + ball->position.y;
    transform->position.z = ball->position.z;
    transform->z_index = ball->z_index - 1;

    if (transform->in_table_bounds())
    {
        target->opacity = SDL_ALPHA_OPAQUE;
    }
    else
    {
        target->opacity = SDL_ALPHA_TRANSPARENT;
    }
}