//
// Created by Fabian Hummel on 13.06.22.
//

#include "vector3.h"
#include <cmath>

Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z){};

Vector3::~Vector3() = default;

Vector3 Vector3::operator+(const Vector3 &other) const
{
	return {this->x + other.x, this->y + other.y, this->z + other.z};
}

Vector3 Vector3::operator-(const Vector3 &other) const
{
	return {this->x - other.x, this->y - other.y, this->z - other.z};
}

Vector3 Vector3::operator*(const Vector3 &other) const
{
	return {this->x * other.x, this->y * other.y, this->z * other.z};
}

Vector3 Vector3::operator/(const Vector3 &other) const
{
	return {this->x / other.x, this->y / other.y, this->z / other.z};
}

Vector3 Vector3::operator+(const double &other) const
{
	return {this->x + other, this->y + other, this->z + other};
}

Vector3 Vector3::operator-(const double &other) const
{
	return {this->x - other, this->y - other, this->z - other};
}

Vector3 Vector3::operator*(const double &other) const
{
	return {this->x * other, this->y * other, this->z * other};
}

Vector3 Vector3::operator/(const double &other) const
{
	return {this->x / other, this->y / other, this->z / other};
}

Vector3 &Vector3::operator+=(const Vector3 &other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}

Vector3 &Vector3::operator-=(const Vector3 &other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

Vector3 &Vector3::operator*=(const Vector3 &other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
	return *this;
}

Vector3 &Vector3::operator/=(const Vector3 &other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;
	return *this;
}

Vector3 &Vector3::operator+=(const double &other)
{
	this->x += other;
	this->y += other;
	this->z += other;
	return *this;
}

Vector3 &Vector3::operator-=(const double &other)
{
	this->x -= other;
	this->y -= other;
	this->z -= other;
	return *this;
}

Vector3 &Vector3::operator*=(const double &other)
{
	this->x *= other;
	this->y *= other;
	this->z *= other;
	return *this;
}

Vector3 &Vector3::operator/=(const double &other)
{
	this->x /= other;
	this->y /= other;
	this->z /= other;
	return *this;
}

bool Vector3::operator==(const Vector3 &other) const
{
	return this->x == other.x && this->y == other.y && this->z == other.z;
};

bool Vector3::operator!=(const Vector3 &other) const
{
	return !(*this == other);
}

double Vector3::magnitude() const
{
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector3 Vector3::normalized() const
{
	const double magnitude = this->magnitude();
	return {this->x / magnitude, this->y / magnitude, this->z / magnitude};
}