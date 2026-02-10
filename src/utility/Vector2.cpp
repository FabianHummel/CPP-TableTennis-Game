//
// Created by Fabian Hummel on 13.06.22.
//

#include "vector2.h"
#include <cmath>

Vector2::Vector2(const float x, const float y) : x(x), y(y){};

Vector2::~Vector2() = default;

Vector2 Vector2::operator+(const Vector2 &other) const
{
	return {this->x + other.x, this->y + other.y};
}

Vector2 Vector2::operator-(const Vector2 &other) const
{
	return {this->x - other.x, this->y - other.y};
}

Vector2 Vector2::operator*(const Vector2 &other) const
{
	return {this->x * other.x, this->y * other.y};
}

Vector2 Vector2::operator/(const Vector2 &other) const
{
	return {this->x / other.x, this->y / other.y};
}

Vector2 Vector2::operator+(const float &other) const
{
	return {this->x + other, this->y + other};
}

Vector2 Vector2::operator-(const float &other) const
{
	return {this->x - other, this->y - other};
}

Vector2 Vector2::operator*(const float &other) const
{
	return {this->x * other, this->y * other};
}

Vector2 Vector2::operator/(const float &other) const
{
	return {this->x / other, this->y / other};
}

Vector2 &Vector2::operator+=(const Vector2 &other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Vector2 &Vector2::operator-=(const Vector2 &other)
{
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

Vector2 &Vector2::operator*=(const Vector2 &other)
{
	this->x *= other.x;
	this->y *= other.y;
	return *this;
}

Vector2 &Vector2::operator/=(const Vector2 &other)
{
	this->x /= other.x;
	this->y /= other.y;
	return *this;
}

Vector2 &Vector2::operator+=(const float &other)
{
	this->x += other;
	this->y += other;
	return *this;
}

Vector2 &Vector2::operator-=(const float &other)
{
	this->x -= other;
	this->y -= other;
	return *this;
}

Vector2 &Vector2::operator*=(const float &other)
{
	this->x *= other;
	this->y *= other;
	return *this;
}

Vector2 &Vector2::operator/=(const float &other)
{
	this->x /= other;
	this->y /= other;
	return *this;
}

bool Vector2::operator==(const Vector2 &other) const
{
	return this->x == other.x && this->y == other.y;
}

bool Vector2::operator!=(const Vector2 &other) const
{
	return !(*this == other);
}

float Vector2::magnitude() const
{
	return sqrt(this->x * this->x + this->y * this->y);
}

Vector2 Vector2::normalized() const
{
	float magnitude = this->magnitude();
	return {this->x / magnitude, this->y / magnitude};
}