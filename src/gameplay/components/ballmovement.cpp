//
// Created by Fabian Hummel on 12.06.22.
//

#include "ballmovement.h"
#include "../../utility/mathutil.h"
#include "gamemanager.h"
#include "../../entity/entitymanager.h"
#include "../../render/renderwindow.h"
#include <algorithm>
#include <SDL.h>

void BallMovement::onInitialize() {
	transform = parent->getComponent<Transform>();
	sprite = parent->getComponent<SpriteRenderer>();
}

void BallMovement::onStart() {
	this->setIdle();
	transform->setPosition({
		(float) RenderWindow::trueCenterX(transform->getScaleX()), 100, 650
	});

	SoundManager::addSound("res/sounds/ball-bounce-1.wav", "bounce 1");
	SoundManager::addSound("res/sounds/ball-bounce-2.wav", "bounce 2");
	SoundManager::addSound("res/sounds/ball-bounce-3.wav", "bounce 3");
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

Vector3 BallMovement::getForce() const {
	return this->velocity;
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

		// Bounce off the table
		if (transform->inTableBounds()) {
			transform->setY(0);

			velocity.y *= isIdle() ? -1.0f : -0.8f;
			if (velocity.y < 0.2f) {
				velocity.y = 0.0f;
			}

			sprite->setOpacity(SDL_ALPHA_OPAQUE);
			SoundManager::playRndSound(
				{ "bounce 1", "bounce 2", "bounce 3" },
				std::clamp(velocity.y * 50.0f, 0.0f, 100.0f)
			);
		} else {
			// Otherwise, fall off the table and fade away
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

void BallMovement::setIdle() {
	this->idle = true;
}

void BallMovement::setActive() {
	this->idle = false;
}

bool BallMovement::isIdle() const {
	return this->idle;
}