//
// Created by Fabian Hummel on 17.04.22.
//

#pragma once

#include "entitybase.h"
#include "utility/vector3.h"

class BallEntity : public EntityBase {
private:
    float height;
    float posX;
    float posY;

public:
    EntityBase *shadow;
    Vector3 velocity;

    static const float GRAVITY = 0.2f;
    static const float FRICTION = 0.05f;

    BallEntity();
    ~BallEntity();

    void updateShadow();
    void updateRenderPos();

    float getHeight();
    void setHeight(float height);
    void moveByHeight(float v);

    float getPosX();
    void setPosX(float posX);
    void moveByX(float v);

    float getPosY();
    void setPosY(float posY);
    void moveByY(float v);

    void applyForce(const Vector3& force);
    void applyGravity();
    void applyFriction();
    void applyVelocity();

    void checkGround();
};
