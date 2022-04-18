//
// Created by Fabian Hummel on 17.04.22.
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
    return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector3 Vector3::operator-(const Vector3 &other) const {
    return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vector3 Vector3::operator*(const Vector3 &other) const {
    return Vector3(this->x * other.x, this->y * other.y, this->z * other.z);
}

Vector3 Vector3::operator/(const Vector3 &other) const {
    return Vector3(this->x / other.x, this->y / other.y, this->z / other.z);
}

Vector3 Vector3::operator+(const float &other) const {
    return Vector3(this->x + other, this->y + other, this->z + other);
}

Vector3 Vector3::operator-(const float &other) const {
    return Vector3(this->x - other, this->y - other, this->z - other);
}

Vector3 Vector3::operator*(const float &other) const {
    return Vector3(this->x * other, this->y * other, this->z * other);
}

Vector3 Vector3::operator/(const float &other) const {
    return Vector3(this->x / other, this->y / other, this->z / other);
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
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector3 Vector3::normalized() const {
    float magnitude = this->magnitude();
    return Vector3(this->x / magnitude, this->y / magnitude, this->z / magnitude);
}