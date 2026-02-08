//
// Created by Fabian Hummel on 17.04.22.
//

#pragma once

struct Vector2
{
  public:
	float x, y;

	Vector2(float x, float y);
	~Vector2();

	Vector2 operator+(const Vector2 &other) const;
	Vector2 operator-(const Vector2 &other) const;
	Vector2 operator*(const Vector2 &other) const;
	Vector2 operator/(const Vector2 &other) const;

	Vector2 operator+(const float &other) const;
	Vector2 operator-(const float &other) const;
	Vector2 operator*(const float &other) const;
	Vector2 operator/(const float &other) const;

	Vector2 &operator+=(const Vector2 &other);
	Vector2 &operator-=(const Vector2 &other);
	Vector2 &operator*=(const Vector2 &other);
	Vector2 &operator/=(const Vector2 &other);

	Vector2 &operator+=(const float &other);
	Vector2 &operator-=(const float &other);
	Vector2 &operator*=(const float &other);
	Vector2 &operator/=(const float &other);

	bool operator==(const Vector2 &other) const;
	bool operator!=(const Vector2 &other) const;

	float magnitude() const;
	Vector2 normalized() const;
};
