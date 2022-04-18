//
// Created by Fabian Hummel on 17.04.22.
//

#include "ballentity.h"
#include "shadowentity.h"
#include "utility/vector3.h"
#include "utility/mathutil.h"
#include <iostream>

BallEntity::BallEntity() : posX(), posY(), velocity(Vector3(0.0f, 0.0f, 0.0f)) {
    height = 0.0f;
    shadow = new ShadowEntity(
        this
    );
}

BallEntity::~BallEntity() {
    delete this->shadow;
    delete this;
}

void BallEntity::updateShadow() {
    shadow->setRenderX( (int) ( getPosX() + getHeight() * ShadowEntity::SHADOW_ANGLE_Z ) );
    shadow->setRenderY( (int) ( getPosY() + 20 - getHeight() * ShadowEntity::SHADOW_ANGLE_Y ) );

    shadow->moveByX(
    (int) height
    );
}

void BallEntity::updateRenderPos() {
    setRenderX( (int) getPosX() );
    setRenderY( (int) ( getPosY() - getHeight() ));
}

float BallEntity::getHeight() {
    return height;
}

void BallEntity::setHeight(float v) {
    this->height = v;
    updateRenderPos();
}

void BallEntity::moveByHeight(float v) {
    this->height += v;
    updateRenderPos();
}

float BallEntity::getPosX() {
    return posX;
}

void BallEntity::setPosX(float v) {
    this->posX = v;
    updateRenderPos();
}

void BallEntity::moveByX(float v) {
    this->posX += v;
    updateRenderPos();
}

float BallEntity::getPosY() {
    return posY;
}

void BallEntity::setPosY(float v) {
    this->posY = v;
    updateRenderPos();
}

void BallEntity::moveByY(float v) {
    this->posY += v;

    if (posY < 440 && !renderBehind) {
		renderBehind = true;
        RenderManager::move(
            1, 3
        );
    } else if (posY >= 440 && renderBehind) {
		renderBehind = false;
		RenderManager::move(
			3, 1
		);
	}

    updateRenderPos();
}

void BallEntity::applyForce(const Vector3& force) {
    this->velocity += force;
}

void BallEntity::applyGravity() {
    this->velocity.y -= GRAVITY;
}

void BallEntity::applyFriction() {
    if (this->getHeight() > 0.0f) {
        return;
    }

    Vector3 vel = Vector3(velocity.x, 0.0f, velocity.z);
    MathUtil::moveTowardsZero(vel, FRICTION);
    velocity.x = vel.x;
    velocity.z = vel.z;
}

void BallEntity::applyVelocity() {
    this->moveByX( this->velocity.x );
    this->moveByHeight( this->velocity.y );
    this->moveByY( this->velocity.z );
}

void BallEntity::checkGround() {
    if (this->height < 0) {
        this->height = 0;
        this->velocity.y *= -0.8f;
    }
}
