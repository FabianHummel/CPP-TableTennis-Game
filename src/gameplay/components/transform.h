//
// Created by Fabian Hummel on 12.06.22.
//

#pragma once

#include <tuple>
#include <SDL_rect.h>
#include "../component.h"
#include "../../entity/entity.h"
#include "../../utility/vector3.h"
#include "../../utility/vector2int.h"

class Transform : public Component {
private:
	Vector3 position = { 0, 0, 0 };
	Vector2Int scale = { 0, 0 };

	float rotation = 0.0f;
	SDL_Point *anchor = nullptr;

public:
	Transform(const Vector3& position, const Vector2Int& scale, float angle);

	void onInitialize() override;
	void onStart() override;
	void onUpdate(double deltaTime) override;

	void setPosition(const Vector3& v);
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

	void setScale(const Vector2Int& v);
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

	void setAnchor(SDL_Point v);
	SDL_Point* getAnchor() const;

	bool inTableBounds() const;
};