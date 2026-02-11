//
// Created by Fabian Hummel on 13.06.22.
//

#pragma once

struct Vector3
{
  public:
	double x, y, z;

	Vector3(double x, double y, double z);
	~Vector3();

	Vector3 operator+(const Vector3 &other) const;
	Vector3 operator-(const Vector3 &other) const;
	Vector3 operator*(const Vector3 &other) const;
	Vector3 operator/(const Vector3 &other) const;

	Vector3 operator+(const double &other) const;
	Vector3 operator-(const double &other) const;
	Vector3 operator*(const double &other) const;
	Vector3 operator/(const double &other) const;

	Vector3 &operator+=(const Vector3 &other);
	Vector3 &operator-=(const Vector3 &other);
	Vector3 &operator*=(const Vector3 &other);
	Vector3 &operator/=(const Vector3 &other);

	Vector3 &operator+=(const double &other);
	Vector3 &operator-=(const double &other);
	Vector3 &operator*=(const double &other);
	Vector3 &operator/=(const double &other);

	bool operator==(const Vector3 &other) const;
	bool operator!=(const Vector3 &other) const;

	double magnitude() const;
	Vector3 normalized() const;
};