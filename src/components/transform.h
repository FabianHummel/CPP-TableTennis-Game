#pragma once

#include "../utility/vector2.h"
#include "../utility/vector3.h"
#include "../componentsystem.h"
#include <SDL3/SDL_rect.h>

class Transform : public Component
{
  public:
	Transform *animation{nullptr};
	Vector3 position = {0, 0, 0};
	Vector2 scale = {0, 0};
	float rotation = 0.0f;
	int zIndex = 0;
	SDL_FPoint anchor = {0, 0};

	Transform();

	void onDelete() override;

	Vector3 getCalculatedPos() const;
	Vector2 getCalculatedScale() const;
	float getCalculatedRotation() const;
	int getCalculatedZIndex() const;

	Entity *apply(const Vector3 &pos, const Vector2 &scl, const SDL_FPoint &anchor, float rot, int zIndex);

	bool inTableBounds() const;
	bool inTransformBounds(float x, float y) const;

	SDL_FRect getCalculatedRect() const;
};
