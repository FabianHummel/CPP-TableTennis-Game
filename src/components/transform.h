#pragma once

#include "../utility/vector2int.h"
#include "../utility/vector3.h"
#include "../componentsystem.h"
#include <SDL_rect.h>

class Transform : public Component
{
  private:
	Vector3 position = {0, 0, 0};
	Vector2Int scale = {0, 0};
	float rotation = 0.0f;
	int zIndex = 0;
	SDL_FPoint anchor = {0, 0};

  public:
	Transform *animation{};

	Transform(const Vector3 &position, const Vector2Int &scale, const SDL_FPoint &anchor, float angle, int zIndex = 0);
	Transform();

	void onDelete() override;

	void setPosition(const Vector3 &v);
	Vector3 getPosition() const;
	void setX(float nX);
	void setY(float nY);
	void setZ(float nZ);
	float getX() const;
	float getY() const;
	float getZ() const;
	void mvByX(float v);
	void mvByY(float v);
	void mvByZ(float v);
	void printPosition() const;

	void setScale(const Vector2Int &v);
	Vector2Int getScale() const;
	void setScaleX(int nX);
	void setScaleY(int nY);
	int getScaleX() const;
	int getScaleY() const;
	void mvByScaleX(int v);
	void mvByScaleY(int v);
	void printScale() const;

	void setRotation(float v);
	float getRotation() const;
	void printRotation() const;

	void setI(int v);
	int getI() const;
	void printI() const;

	Entity *apply(const Vector3 &pos, const Vector2Int &scl, const SDL_FPoint &anchor, float rot, int zIndex);

	void setAnchor(const SDL_FPoint &v);
	SDL_FPoint getAnchor() const;

	bool inTableBounds() const;
	bool inTransformBounds(int x, int y) const;

	SDL_Rect asRect() const;
};
