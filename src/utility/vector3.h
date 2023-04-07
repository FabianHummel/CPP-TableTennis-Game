//
// Created by Fabian Hummel on 13.06.22.
//

#pragma once

struct Vector3
{
  public:
	float x, y, z;

	Vector3(float x, float y, float z);
	~Vector3();

	Vector3 operator+(const Vector3 &other) const;
	Vector3 operator-(const Vector3 &other) const;
	Vector3 operator*(const Vector3 &other) const;
	Vector3 operator/(const Vector3 &other) const;

	Vector3 operator+(const float &other) const;
	Vector3 operator-(const float &other) const;
	Vector3 operator*(const float &other) const;
	Vector3 operator/(const float &other) const;

	Vector3 &operator+=(const Vector3 &other);
	Vector3 &operator-=(const Vector3 &other);
	Vector3 &operator*=(const Vector3 &other);
	Vector3 &operator/=(const Vector3 &other);

	Vector3 &operator+=(const float &other);
	Vector3 &operator-=(const float &other);
	Vector3 &operator*=(const float &other);
	Vector3 &operator/=(const float &other);

	bool operator==(const Vector3 &other) const;
	bool operator!=(const Vector3 &other) const;

	float magnitude() const;
	Vector3 normalized() const;
};