#include "transform.h"
#include <SDL_rect.h>

Transform::Transform(const Vector3 &position, const Vector2Int &scale, const SDL_FPoint &anchor, float angle,
                     int zIndex)
	: position(position), scale(scale), anchor(anchor), rotation(angle), zIndex(zIndex)
{
}

Transform::Transform() : position(0, 0, 0), scale(0, 0), anchor(), rotation(0.0f), zIndex(0)
{
}

void Transform::setPosition(const Vector3 &v)
{
	position = v;
}

Vector3 Transform::getPosition() const
{
	return position;
}

void Transform::setX(float nX)
{
	this->position.x = nX;
}

void Transform::setY(float nY)
{
	this->position.y = nY;
}

void Transform::setZ(float nZ)
{
	this->position.z = nZ;
}

float Transform::getX() const
{
	if (parent->parent == nullptr)
		return position.x;

	return position.x + parent->parent->transform->position.x;
}

float Transform::getY() const
{
	if (parent->parent == nullptr)
		return position.y;

	return position.y + parent->parent->transform->position.y;
}

float Transform::getZ() const
{
	if (parent->parent == nullptr)
		return position.z;

	return position.z + parent->parent->transform->position.z;
}

void Transform::mvByX(float v)
{
	position.x += v;
}

void Transform::mvByY(float v)
{
	position.y += v;
}

void Transform::mvByZ(float v)
{
	position.z += v;
}

void Transform::printPosition() const
{
	printf("%s: Position: %f, %f, %f\n", parent->name, position.x, position.y, position.z);
}

void Transform::setScale(const Vector2Int &v)
{
	this->scale = v;
}

Vector2Int Transform::getScale() const
{
	if (parent->parent == nullptr)
		return scale;

	return scale + parent->parent->transform->scale;
}

void Transform::setScaleX(int nX)
{
	this->scale.x = nX;
}

void Transform::setScaleY(int nY)
{
	this->scale.y = nY;
}

int Transform::getScaleX() const
{
	if (parent->parent == nullptr)
		return scale.x;

	return scale.x + parent->parent->transform->scale.x;
}

int Transform::getScaleY() const
{
	if (parent->parent == nullptr)
		return scale.y;

	return scale.y + parent->parent->transform->scale.y;
}

void Transform::mvByScaleX(int v)
{
	scale.x += v;
}

void Transform::mvByScaleY(int v)
{
	scale.y += v;
}

void Transform::printScale() const
{
	printf("%s: Scale: %d, %d\n", parent->name, scale.x, scale.y);
}

void Transform::setRotation(float v)
{
	this->rotation = v;
}

float Transform::getRotation() const
{
	if (parent->parent == nullptr)
		return rotation;

	return rotation + parent->parent->transform->rotation;
}

void Transform::printRotation() const
{
	printf("%s: Rotation: %f\n", parent->name, rotation);
}

void Transform::setI(int v)
{
	this->zIndex = v;
}

int Transform::getI() const
{
	if (parent->parent == nullptr)
	{
		return zIndex;
	}

	return zIndex + parent->parent->transform->zIndex;
}

void Transform::printI() const
{
	printf("%s: Z-Index: %d\n", parent->name, zIndex);
}

Entity *Transform::apply(const Vector3 &pos, const Vector2Int &scl, const SDL_FPoint &anchor, float rot, int zIndex)
{
	setPosition(pos);
	setScale(scl);
	setAnchor(anchor);
	setRotation(rot);
	setI(zIndex);
	return parent;
}

void Transform::setAnchor(const SDL_FPoint &v)
{
	this->anchor = v;
}

SDL_FPoint Transform::getAnchor() const
{
	return anchor;
}

bool Transform::inTableBounds() const
{
	return getX() > 35 && getX() < 665 && getZ() > 72 && getZ() < 938;
}

bool Transform::inTransformBounds(int x, int y) const
{
	return x >= getX() - getScaleX() * getAnchor().x && x <= getX() + getScaleX() - getScaleX() * getAnchor().x &&
	       y >= getZ() - getScaleY() * getAnchor().y && y <= getZ() + getScaleY() - getScaleY() * getAnchor().y;
}

SDL_Rect Transform::asRect() const
{
	SDL_Rect ret;
	ret.x = getX();
	ret.y = getZ();
	ret.w = getScaleX();
	ret.h = getScaleY();
	return ret;
}
