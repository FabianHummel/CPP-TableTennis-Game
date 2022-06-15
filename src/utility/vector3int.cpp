//
// Created by Fabian Hummel on 17.04.22.
//

#include "vector3int.h"
#include <cmath>

Vector3Int::Vector3Int(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3Int::~Vector3Int() = default;

Vector3Int Vector3Int::operator+(const Vector3Int &other) const {
    return {this->x + other.x, this->y + other.y, this->z + other.z};
}

Vector3Int Vector3Int::operator-(const Vector3Int &other) const {
    return {this->x - other.x, this->y - other.y, this->z - other.z};
}

Vector3Int Vector3Int::operator*(const Vector3Int &other) const {
    return {this->x * other.x, this->y * other.y, this->z * other.z};
}

Vector3Int Vector3Int::operator/(const Vector3Int &other) const {
    return {this->x / other.x, this->y / other.y, this->z / other.z};
}

Vector3Int Vector3Int::operator+(const int &other) const {
    return {this->x + other, this->y + other, this->z + other};
}

Vector3Int Vector3Int::operator-(const int &other) const {
    return {this->x - other, this->y - other, this->z - other};
}

Vector3Int Vector3Int::operator*(const int &other) const {
    return {this->x * other, this->y * other, this->z * other};
}

Vector3Int Vector3Int::operator/(const int &other) const {
    return {this->x / other, this->y / other, this->z / other};
}

Vector3Int &Vector3Int::operator+=(const Vector3Int &other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

Vector3Int &Vector3Int::operator-=(const Vector3Int &other) {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
}

Vector3Int &Vector3Int::operator*=(const Vector3Int &other) {
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    return *this;
}

Vector3Int &Vector3Int::operator/=(const Vector3Int &other) {
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
    return *this;
}

Vector3Int &Vector3Int::operator+=(const int &other) {
    this->x += other;
    this->y += other;
    this->z += other;
    return *this;
}

Vector3Int &Vector3Int::operator-=(const int &other) {
    this->x -= other;
    this->y -= other;
    this->z -= other;
    return *this;
}

Vector3Int &Vector3Int::operator*=(const int &other) {
    this->x *= other;
    this->y *= other;
    this->z *= other;
    return *this;
}

Vector3Int &Vector3Int::operator/=(const int &other) {
    this->x /= other;
    this->y /= other;
    this->z /= other;
    return *this;
}

bool Vector3Int::operator==(const Vector3Int &other) const {
    return this->x == other.x && this->y == other.y && this->z == other.z;
}

bool Vector3Int::operator!=(const Vector3Int &other) const {
    return !(*this == other);
}

float Vector3Int::magnitude() const {
    return sqrt( (float) (this->x * this->x) + (float) (this->y * this->y) + (float) (this->z * this->z));
}

Vector3Int Vector3Int::normalized() const {
    int magnitude = (int) this->magnitude();
    return {this->x / magnitude, this->y / magnitude, this->z / magnitude};
}