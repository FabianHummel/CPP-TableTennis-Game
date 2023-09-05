#pragma once

#include "../ecs/ecs.h"
#include "../utility/vector2int.h"
#include "../utility/vector3.h"
#include <SDL_rect.h>
#include <SDL_render.h>

class Transform : public Component
{
  private:
	Vector3 position = {0, 0, 0};
	Vector2Int scale = {0, 0};
	float rotation = 0.0f;
	int zIndex = 0;
	SDL_FPoint anchor = {0, 0};

  public:
	Transform(const Vector3 &position, const Vector2Int &scale, const SDL_FPoint &anchor, float angle, int zIndex = 0);
	Transform();

	void setPosition(const Vector3 &v);
	[[nodiscard]] Vector3 getPosition() const;
	void setX(float nX);
	void setY(float nY);
	void setZ(float nZ);
	[[nodiscard]] float getX() const;
	[[nodiscard]] float getY() const;
	[[nodiscard]] float getZ() const;
	void mvByX(float v);
	void mvByY(float v);
	void mvByZ(float v);
	void printPosition() const;

	void setScale(const Vector2Int &v);
	[[nodiscard]] Vector2Int getScale() const;
	void setScaleX(int nX);
	void setScaleY(int nY);
	[[nodiscard]] int getScaleX() const;
	[[nodiscard]] int getScaleY() const;
	void mvByScaleX(int v);
	void mvByScaleY(int v);
	void printScale() const;

	void setRotation(float v);
	[[nodiscard]] float getRotation() const;
	void printRotation() const;

	void setI(int v);
	[[nodiscard]] int getI() const;
	void printI() const;

	Entity *apply(const Vector3 &pos, const Vector2Int &scl, const SDL_FPoint &anchor, float rot, int zIndex);

	void setAnchor(const SDL_FPoint &v);
	[[nodiscard]] SDL_FPoint getAnchor() const;

	[[nodiscard]] bool inTableBounds() const;
	[[nodiscard]] bool inTransformBounds(int x, int y) const;

	[[nodiscard]] SDL_Rect asRect() const;
};
