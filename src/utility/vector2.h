//
// Created by Fabian Hummel on 17.04.22.
//

#pragma once

struct Vector2
{
public:
    double x, y;

    Vector2(double x, double y);
    ~Vector2();

    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(const Vector2& other) const;
    Vector2 operator/(const Vector2& other) const;

    Vector2 operator+(const double& other) const;
    Vector2 operator-(const double& other) const;
    Vector2 operator*(const double& other) const;
    Vector2 operator/(const double& other) const;

    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2& operator*=(const Vector2& other);
    Vector2& operator/=(const Vector2& other);

    Vector2& operator+=(const double& other);
    Vector2& operator-=(const double& other);
    Vector2& operator*=(const double& other);
    Vector2& operator/=(const double& other);

    bool operator==(const Vector2& other) const;
    bool operator!=(const Vector2& other) const;

    double magnitude() const;
    Vector2 normalized() const;
};