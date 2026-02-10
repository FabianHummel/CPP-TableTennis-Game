#include "transform.h"
#include <SDL3/SDL_rect.h>

Transform::Transform(const Vector3 &position, const Vector2 &scale, const SDL_FPoint &anchor, const float angle,
                     const int zIndex)
	: position(position), scale(scale), anchor(anchor), rotation(angle), zIndex(zIndex)
{
}

Transform::Transform() : position(0, 0, 0), scale(0, 0), anchor(), rotation(0.0f), zIndex(0)
{
}

void Transform::onDelete()
{
	delete animation;
}

void Transform::setPosition(const Vector3 &v)
{
	position = v;
}

Vector3 Transform::getPosition() const
{
	return position;
}

void Transform::setX(const float nX)
{
	this->position.x = nX;
}

void Transform::setY(const float nY)
{
	this->position.y = nY;
}

void Transform::setZ(const float nZ)
{
	this->position.z = nZ;
}

float Transform::getX() const
{
	float x = position.x;
	if (parent && parent->parent)
		x += parent->parent->transform->getX();
	if (animation)
		x += animation->getX();
	return x;
}

float Transform::getY() const
{
	float y = position.y;
	if (parent && parent->parent)
		y += parent->parent->transform->getY();
	if (animation)
		y += animation->getY();
	return y;
}

float Transform::getZ() const
{
	float z = position.z;
	if (parent && parent->parent)
		z += parent->parent->transform->getZ();
	if (animation)
		z += animation->getZ();
	return z;
}

void Transform::mvByX(const float v)
{
	position.x += v;
}

void Transform::mvByY(const float v)
{
	position.y += v;
}

void Transform::mvByZ(const float v)
{
	position.z += v;
}

void Transform::printPosition() const
{
	printf("%s: Position: %f, %f, %f\n", parent->name, position.x, position.y, position.z);
}

void Transform::setScale(const Vector2 &v)
{
	this->scale = v;
}

Vector2 Transform::getScale() const
{
	Vector2 scale = this->scale;
	if (animation)
		scale += animation->getScale();
	return scale;
}

void Transform::setScaleX(const float nX)
{
	this->scale.x = nX;
}

void Transform::setScaleY(const float nY)
{
	this->scale.y = nY;
}

float Transform::getScaleX() const
{
	float x = scale.x;
	if (animation)
		x += animation->getScaleX();
	return x;
}

float Transform::getScaleY() const
{
	float y = scale.y;
	if (animation)
		y += animation->getScaleY();
	return y;
}

void Transform::mvByScaleX(const float v)
{
	scale.x += v;
}

void Transform::mvByScaleY(const float v)
{
	scale.y += v;
}

void Transform::printScale() const
{
	printf("%s: Scale: %f, %f\n", parent->name, scale.x, scale.y);
}

void Transform::setRotation(const float v)
{
	this->rotation = v;
}

float Transform::getRotation() const
{
	float rot = rotation;
	if (parent && parent->parent)
		rot += parent->parent->transform->getRotation();
	if (animation)
		rot += animation->getRotation();
	return rot;
}

void Transform::printRotation() const
{
	printf("%s: Rotation: %f\n", parent->name, rotation);
}

void Transform::setI(const int v)
{
	this->zIndex = v;
}

int Transform::getI() const
{
	int i = zIndex;
	if (parent && parent->parent)
		i += parent->parent->transform->getI();
	if (animation)
		i += animation->getI();
	return i;
}

void Transform::printI() const
{
	printf("%s: Z-Index: %d\n", parent->name, zIndex);
}

Entity *Transform::apply(const Vector3 &pos, const Vector2 &scl, const SDL_FPoint &anchor, const float rot, const int zIndex)
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

bool Transform::inTransformBounds(const float x, const float y) const
{
	const SDL_FRect rect = asRect();
	return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}

SDL_FRect Transform::asRect() const
{
	SDL_FRect ret;
	ret.x = getX() - getScaleX() * anchor.x;
	ret.y = getZ() - getScaleY() * anchor.y - getY();
	ret.w = getScaleX();
	ret.h = getScaleY();
	return ret;
}
