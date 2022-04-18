//
// Created by Fabian Hummel on 17.04.22.
//

#pragma once

#include "entitybase.h"
#include "ballentity.h"

class ShadowEntity : public EntityBase {
public:
    static const float SHADOW_ANGLE_Y = 0.0f;
    static const float SHADOW_ANGLE_Z = 0.0f;
    BallEntity *ball;

    ShadowEntity(BallEntity *ball);
    ~ShadowEntity();
};