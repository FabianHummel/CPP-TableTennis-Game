//
// Created by Fabian Hummel on 12.06.22.
//

#include "ballmovement.h"
#include "../../utility/mathutil.h"
#include "gamemanager.h"
#include "../../entity/entitymanager.h"
#include <algorithm>
#include <SDL.h>

void BallMovement::onInitialize() {
	transform = parent->getComponent<Transform>();
	sprite = parent->getComponent<SpriteRenderer>();
}

void BallMovement::onStart() {
	this->applyForce({ 1.2, 3, -3 });
	transform->setPosition({ 400, 0, 600 });
}

void BallMovement::onUpdate() {
	this->applyGravity();
	this->applyFriction();
	this->applyVelocity();

	this->checkGround();
	this->checkNet();
	this->checkIdle();
	this->checkFellOff();
}

void BallMovement::checkNet() {
	if (transform->getY() >= 0) {

		if (transform->getZ() < 450 && !renderBehind) {
			renderBehind = true;
			EntityManager::renderBelow(parent, EntityManager::findEntity("Net"));
			EntityManager::renderBelow(EntityManager::findEntity("Shadow"), parent);
		} else if (transform->getZ() >= 450 && renderBehind) {
			renderBehind = false;
			EntityManager::renderAbove(parent, EntityManager::findEntity("Net"));
			EntityManager::renderBelow(EntityManager::findEntity("Shadow"), parent);
		}

		if (transform->getY() < 60) {
			if (( transform->getZ() > 450 && transform->getZ() + velocity.z < 450 ) ||
				( transform->getZ() < 450 && transform->getZ() + velocity.z > 450 )) {
				// Ball is going to be in the net
				transform->setZ(450);
				this->velocity.z *= -0.2;
				this->velocity.x *= 0.5;
			}
		}
	}
}

void BallMovement::applyForce(const Vector3& force) {
	this->velocity += force;
}

void BallMovement::setForce(const Vector3 &force) {
	this->velocity = force;
}

void BallMovement::applyGravity() {
	this->velocity.y -= GRAVITY;
}

void BallMovement::applyFriction() {
	if (transform->getY() <= 0) {
		Vector3 vel = Vector3(velocity.x, 0.0f, velocity.z);
		MathUtil::moveTowardsZero(vel, FRICTION);
		velocity.x = vel.x;
		velocity.z = vel.z;
	}
}

void BallMovement::applyVelocity() {
	transform->mvByX(  this->velocity.x );
	transform->mvByY(  this->velocity.y );
	transform->mvByZ(  this->velocity.z );
}

void BallMovement::checkGround() {
	if (transform->getY() < 0) {
		if (inTableBounds()) {
			transform->setY(0);
			this->velocity.y *= isIdle() ? -1.0f : -0.8f;
			sprite->setOpacity(
				SDL_ALPHA_OPAQUE
			);
		} else {
			sprite->setOpacity(
				std::clamp(SDL_ALPHA_OPAQUE - (int) abs(transform->getY()), 0, 255)
			);
		}
	}

	if (transform->getY() < 0 && !fellOff) {
		fellOff = true;
		EntityManager::renderBelow(parent, EntityManager::findEntity("Table"));
		EntityManager::renderBelow(EntityManager::findEntity("Shadow"), parent);
	} else if (transform->getY() > 0 && fellOff) {
		fellOff = false;
		EntityManager::renderAbove(parent, EntityManager::findEntity("Net"));
		EntityManager::renderBelow(EntityManager::findEntity("Shadow"), parent);
		sprite->setOpacity(
			SDL_ALPHA_OPAQUE
		);
	}
}

void BallMovement::checkIdle() {
	if (MathUtil::closeToPoint(velocity.magnitude(), 0.3f)) {
		idleTime++;

		if (idleTime > IDLE_TIME) {
			GameManager::nextRound(renderBehind);
			idleTime = 0;
		}
	}
}

void BallMovement::checkFellOff() {
	if (transform->getY() < -1000) {
		GameManager::nextRound(
			!renderBehind
		);
	}
}

bool BallMovement::inTableBounds() {
	return transform->getX() > 35 && transform->getX() < 665 && transform->getZ() > 72 && transform->getZ() < 938;
}

void BallMovement::setIdle() {
	this->idle = true;
}

void BallMovement::setActive() {
	this->idle = false;
}

bool BallMovement::isIdle() const {
	return this->idle;
}