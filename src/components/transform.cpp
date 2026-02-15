#include "transform.h"
#include <SDL3/SDL_rect.h>

Transform::Transform()
{
	this->name = "Transform";
}

void Transform::onDelete()
{
	delete animation;
}

Vector3 Transform::getCalculatedPos() const
{
	Vector3 pos = position;
	if (parent && parent->parent)
		pos += parent->parent->transform->getCalculatedPos();
	if (animation)
		pos += animation->getCalculatedPos();
	return pos;
}

Vector2 Transform::getCalculatedScale() const
{
	Vector2 scl = scale;
	if (animation)
		scl += animation->getCalculatedScale();
	return scl;
}

float Transform::getCalculatedRotation() const
{
	float rot = rotation;
	if (parent && parent->parent)
		rot += parent->parent->transform->getCalculatedRotation();
	if (animation)
		rot += animation->getCalculatedRotation();
	return rot;
}

int Transform::getCalculatedZIndex() const
{
	int i = zIndex;
	if (parent && parent->parent)
		i += parent->parent->transform->getCalculatedZIndex();
	if (animation)
		i += animation->getCalculatedZIndex();
	return i;
}

Entity *Transform::apply(const Vector3 &pos, const Vector2 &scl, const SDL_FPoint &anchor, const float rot, const int zIndex)
{
	this->position = pos;
	this->scale = scl;
	this->anchor = anchor;
	this->rotation = rot;
	this->zIndex = zIndex;
	return parent;
}

bool Transform::inTableBounds() const
{
	Vector3 pos = getCalculatedPos();
	return pos.x > 35 && pos.x < 665 && pos.z > 72 && pos.z < 938;
}

bool Transform::inTransformBounds(const float x, const float y) const
{
	const SDL_FRect rect = getCalculatedRect();
	return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}

SDL_FRect Transform::getCalculatedRect() const
{
	const Vector3 pos = getCalculatedPos();
	const Vector2 scale = getCalculatedScale();

	SDL_FRect ret;
	ret.x = (float)(pos.x - scale.x * anchor.x);
	ret.y = (float)(pos.z - scale.y * anchor.y - pos.y);
	ret.w = (float)scale.x;
	ret.h = (float)scale.y;
	return ret;
}
