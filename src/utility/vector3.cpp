//
// Created by Fabian Hummel on 13.06.22.
//

#include "vector3.h"
#include <cmath>

Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::~Vector3() = default;

Vector3 Vector3::operator+(const Vector3 &other) const {
	return {this->x + other.x, this->y + other.y, this->z + other.z};
}

Vector3 Vector3::operator-(const Vector3 &other) const {
	return {this->x - other.x, this->y - other.y, this->z - other.z};
}

Vector3 Vector3::operator*(const Vector3 &other) const {
	return {this->x * other.x, this->y * other.y, this->z * other.z};
}

Vector3 Vector3::operator/(const Vector3 &other) const {
	return {this->x / other.x, this->y / other.y, this->z / other.z};
}

Vector3 Vector3::operator+(const float &other) const {
	return {this->x + other, this->y + other, this->z + other};
}

Vector3 Vector3::operator-(const float &other) const {
	return {this->x - other, this->y - other, this->z - other};
}

Vector3 Vector3::operator*(const float &other) const {
	return {this->x * other, this->y * other, this->z * other};
}

Vector3 Vector3::operator/(const float &other) const {
	return {this->x / other, this->y / other, this->z / other};
}

Vector3 &Vector3::operator+=(const Vector3 &other) {
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

Vector3 &Vector3::operator-=(const Vector3 &other) {
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

Vector3 &Vector3::operator*=(const Vector3 &other) {
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
	return *this;
}

Vector3 &Vector3::operator/=(const Vector3 &other) {
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;
	return *this;
}

Vector3 &Vector3::operator+=(const float &other) {
	this->x += other;
	this->y += other;
	this->z += other;
	return *this;
}

Vector3 &Vector3::operator-=(const float &other) {
	this->x -= other;
	this->y -= other;
	this->z -= other;
	return *this;
}

Vector3 &Vector3::operator*=(const float &other) {
	this->x *= other;
	this->y *= other;
	this->z *= other;
	return *this;
}

Vector3 &Vector3::operator/=(const float &other) {
	this->x /= other;
	this->y /= other;
	this->z /= other;
	return *this;
}

bool Vector3::operator==(const Vector3 &other) const {
	return this->x == other.x && this->y == other.y && this->z == other.z;
}

bool Vector3::operator!=(const Vector3 &other) const {
	return !(*this == other);
}

float Vector3::magnitude() const {
	return sqrt( (float) (this->x * this->x) + (float) (this->y * this->y) + (float) (this->z * this->z));
}

Vector3 Vector3::normalized() const {
	float magnitude = (float) this->magnitude();
	return {this->x / magnitude, this->y / magnitude, this->z / magnitude};
}