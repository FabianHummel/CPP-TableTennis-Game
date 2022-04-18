//
// Created by Fabian Hummel on 17.04.22.
//

#include "shadowentity.h"

ShadowEntity::ShadowEntity(BallEntity *ball) {
    this->ball = ball;
}

ShadowEntity::~ShadowEntity() {
    delete this;
}