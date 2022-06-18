//
// Created by Fabian Hummel on 12.06.22.
//

#include "transform.h"

Transform::Transform(const Vector3& position, const Vector2Int& scale, float angle)
	: position(position), scale(scale), rotation(angle) {}

void Transform::onInitialize() {
	printf("Initializing Transform on %s\n", parent->getName());
}

void Transform::onStart() {}

void Transform::onUpdate(double deltaTime) {}

void Transform::setPosition(const Vector3& v) {
	position = v;
}

Vector3 Transform::getPosition() const {
	return position;
}

void Transform::setX(float nX) {
	this->position.x = nX;
}

void Transform::setY(float nY) {
	this->position.y = nY;
}

void Transform::setZ(float nZ) {
	this->position.z = nZ;
}

float Transform::getX() const {
	return position.x;
}

float Transform::getY() const {
	return position.y;
}

float Transform::getZ() const {
	return position.z;
}

void Transform::mvByX(float v) {
	position.x += v;
}

void Transform::mvByY(float v) {
	position.y += v;
}

void Transform::mvByZ(float v) {
	position.z += v;
}

void Transform::printPosition() const {
	printf("Position: %f, %f, %f\n", position.x, position.y, position.z);
}

void Transform::setScale(const Vector2Int& v) {
	this->scale = v;
}

Vector2Int Transform::getScale() const {
	return scale;
}

void Transform::setScaleX(int nX) {
	this->scale.x = nX;
}

void Transform::setScaleY(int nY) {
	this->scale.y = nY;
}

int Transform::getScaleX() const {
	return scale.x;
}

int Transform::getScaleY() const {
	return scale.y;
}

void Transform::mvByScaleX(int v) {
	scale.x += v;
}

void Transform::mvByScaleY(int v) {
	scale.y += v;
}

void Transform::printScale() const {
	printf("Scale: %d, %d\n", scale.x, scale.y);
}

void Transform::setRotation(float v) {
	this->rotation = v;
}

float Transform::getRotation() const {
	return rotation;
}

void Transform::printRotation() const {
	printf("Rotation: %f\n", rotation);
}

void Transform::setAnchor(SDL_Point v) {
	this->anchor = new SDL_Point(v);
}

SDL_Point* Transform::getAnchor() const {
	return anchor;
}

bool Transform::inTableBounds() const {
	return getX() > 35 && getX() < 665 && getZ() > 72 && getZ() < 938;
}