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
	Vector2Int scale = this->scale;
	if (parent && parent->parent)
		scale += parent->parent->transform->getScale();
	if (animation)
		scale += animation->getScale();
	return scale;
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
	int x = scale.x;
	if (parent && parent->parent)
		x += parent->parent->transform->getScaleX();
	if (animation)
		x += animation->getScaleX();
	return x;
}

int Transform::getScaleY() const
{
	int y = scale.y;
	if (parent && parent->parent)
		y += parent->parent->transform->getScaleY();
	if (animation)
		y += animation->getScaleY();
	return y;
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

void Transform::setI(int v)
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
