//
// Created by Fabian Hummel on 13.06.22.
//

#include "vector2int.h"
#include <cmath>

Vector2Int::Vector2Int(int x, int y) : x(x), y(y){};

Vector2Int::~Vector2Int() = default;

Vector2Int Vector2Int::operator+(const Vector2Int &other) const
{
	return {this->x + other.x, this->y + other.y};
}

Vector2Int Vector2Int::operator-(const Vector2Int &other) const
{
	return {this->x - other.x, this->y - other.y};
}

Vector2Int Vector2Int::operator*(const Vector2Int &other) const
{
	return {this->x * other.x, this->y * other.y};
}

Vector2Int Vector2Int::operator/(const Vector2Int &other) const
{
	return {this->x / other.x, this->y / other.y};
}

Vector2Int Vector2Int::operator+(const int &other) const
{
	return {this->x + other, this->y + other};
}

Vector2Int Vector2Int::operator-(const int &other) const
{
	return {this->x - other, this->y - other};
}

Vector2Int Vector2Int::operator*(const int &other) const
{
	return {this->x * other, this->y * other};
}

Vector2Int Vector2Int::operator/(const int &other) const
{
	return {this->x / other, this->y / other};
}

Vector2Int &Vector2Int::operator+=(const Vector2Int &other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Vector2Int &Vector2Int::operator-=(const Vector2Int &other)
{
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

Vector2Int &Vector2Int::operator*=(const Vector2Int &other)
{
	this->x *= other.x;
	this->y *= other.y;
	return *this;
}

Vector2Int &Vector2Int::operator/=(const Vector2Int &other)
{
	this->x /= other.x;
	this->y /= other.y;
	return *this;
}

Vector2Int &Vector2Int::operator+=(const int &other)
{
	this->x += other;
	this->y += other;
	return *this;
}

Vector2Int &Vector2Int::operator-=(const int &other)
{
	this->x -= other;
	this->y -= other;
	return *this;
}

Vector2Int &Vector2Int::operator*=(const int &other)
{
	this->x *= other;
	this->y *= other;
	return *this;
}

Vector2Int &Vector2Int::operator/=(const int &other)
{
	this->x /= other;
	this->y /= other;
	return *this;
}

bool Vector2Int::operator==(const Vector2Int &other) const
{
	return this->x == other.x && this->y == other.y;
}

bool Vector2Int::operator!=(const Vector2Int &other) const
{
	return !(*this == other);
}

float Vector2Int::magnitude() const
{
	return sqrt((float)(this->x * this->x) + (float)(this->y * this->y));
}

Vector2Int Vector2Int::normalized() const
{
	int magnitude = (int)this->magnitude();
	return {this->x / magnitude, this->y / magnitude};
}