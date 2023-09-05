//
// Created by Fabian Hummel on 17.04.22.
//

#pragma once

struct Vector2Int
{
  public:
	int x, y;

	Vector2Int(int x, int y);
	~Vector2Int();

	Vector2Int operator+(const Vector2Int &other) const;
	Vector2Int operator-(const Vector2Int &other) const;
	Vector2Int operator*(const Vector2Int &other) const;
	Vector2Int operator/(const Vector2Int &other) const;

	Vector2Int operator+(const int &other) const;
	Vector2Int operator-(const int &other) const;
	Vector2Int operator*(const int &other) const;
	Vector2Int operator/(const int &other) const;

	Vector2Int &operator+=(const Vector2Int &other);
	Vector2Int &operator-=(const Vector2Int &other);
	Vector2Int &operator*=(const Vector2Int &other);
	Vector2Int &operator/=(const Vector2Int &other);

	Vector2Int &operator+=(const int &other);
	Vector2Int &operator-=(const int &other);
	Vector2Int &operator*=(const int &other);
	Vector2Int &operator/=(const int &other);

	bool operator==(const Vector2Int &other) const;
	bool operator!=(const Vector2Int &other) const;

	float magnitude() const;
	Vector2Int normalized() const;
};
