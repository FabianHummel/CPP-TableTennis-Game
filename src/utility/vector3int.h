//
// Created by Fabian Hummel on 17.04.22.
//

#pragma once

struct Vector3Int {
public:
    int x, y, z;

    Vector3Int(int x, int y, int z);
    ~Vector3Int();

    Vector3Int operator+(const Vector3Int& other) const;
    Vector3Int operator-(const Vector3Int& other) const;
    Vector3Int operator*(const Vector3Int& other) const;
    Vector3Int operator/(const Vector3Int& other) const;

    Vector3Int operator+(const int& other) const;
    Vector3Int operator-(const int& other) const;
    Vector3Int operator*(const int& other) const;
    Vector3Int operator/(const int& other) const;

    Vector3Int& operator+=(const Vector3Int& other);
    Vector3Int& operator-=(const Vector3Int& other);
    Vector3Int& operator*=(const Vector3Int& other);
    Vector3Int& operator/=(const Vector3Int& other);

    Vector3Int& operator+=(const int& other);
    Vector3Int& operator-=(const int& other);
    Vector3Int& operator*=(const int& other);
    Vector3Int& operator/=(const int& other);

    bool operator==(const Vector3Int& other) const;
    bool operator!=(const Vector3Int& other) const;

    float magnitude() const;
    Vector3Int normalized() const;
};
