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
	printf("Initializing Ball Movement Behavior on %s\n", parent->getName());
	transform = parent->getComponent<Transform>();
	sprite = parent->getComponent<SpriteRenderer>();
}

void BallMovement::onStart() {
	this->setIdle();
	transform->setPosition(
		{ RenderWindow::SCREEN_CENTER_X, 100, 650 }
	);

	SoundManager::addSound("res/sounds/ball-bounce-1.wav", "bounce 1");
	SoundManager::addSound("res/sounds/ball-bounce-2.wav", "bounce 2");
	SoundManager::addSound("res/sounds/ball-bounce-3.wav", "bounce 3");
}

void BallMovement::onUpdate(double deltaTime) {
	this->checkGround(deltaTime);
	this->checkNet(deltaTime);
	this->checkIdle(deltaTime);
	this->checkFellOff();

	this->applyGravity(deltaTime);
	this->applyFriction(deltaTime);
	this->applyVelocity(deltaTime);
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

void BallMovement::applyGravity(double deltaTime) {
	this->velocity.y -= GRAVITY * deltaTime;
}

void BallMovement::applyFriction(double deltaTime) {
	if (transform->getY() <= 0) {
		auto vel = Vector3(velocity.x, 0.0f, velocity.z);
		MathUtil::moveTowardsZero(vel, FRICTION * deltaTime);
		velocity.x = vel.x;
		velocity.z = vel.z;
	}
}

void BallMovement::applyVelocity(double deltaTime) {
	transform->mvByX(  this->velocity.x * deltaTime );
	transform->mvByY(  this->velocity.y * deltaTime );
	transform->mvByZ(  this->velocity.z * deltaTime );
}

void BallMovement::checkGround(double deltaTime) {
	if (transform->getY() < 0) {

		// Bounce off the table
		if (transform->inTableBounds()) {
			transform->setY(0);

			velocity.y *= isIdle() ? -1.0f : -0.8f;
			if (velocity.y < 0.5f) {
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

void BallMovement::checkNet(double deltaTime) {
	if (transform->getY() >= 0) {

		if (transform->getZ() < 460 && !renderBehind) {
			renderBehind = true;
			EntityManager::renderBelow(parent, EntityManager::findEntity("Net"));
			EntityManager::renderBelow(EntityManager::findEntity("Shadow"), parent);
		} else if (transform->getZ() > 460 && renderBehind) {
			renderBehind = false;
			EntityManager::renderAbove(parent, EntityManager::findEntity("Net"));
			EntityManager::renderBelow(EntityManager::findEntity("Shadow"), parent);
		}

		if (transform->getY() < 60) {
			// if (( transform->getZ() > 465 && transform->getZ() + velocity.z * deltaTime <= 465 ) ||
			// 	( transform->getZ() < 465 && transform->getZ() + velocity.z * deltaTime >= 465 )) {
			// 	// Ball is going to be in the net
			// 	transform->setZ(465);
			// 	this->velocity.z *= -0.2f;
			// 	this->velocity.x *= 0.5f;
			// }

			if ( transform->getZ() > 460 && transform->getZ() + velocity.z * deltaTime < 480 ) {
				// Ball is going to be in the net
				transform->setZ(480);
				this->velocity.z *= -0.2f;
				this->velocity.x *= 0.5f;
			} else if ( transform->getZ() < 460 && transform->getZ() + velocity.z * deltaTime > 440 ) {
				// Ball is going to be in the net
				transform->setZ(440);
				this->velocity.z *= -0.2f;
				this->velocity.x *= 0.5f;
			}
		}
	}
}

void BallMovement::checkIdle(double deltaTime) {
	if (MathUtil::closeToPoint(velocity.magnitude(), 0.3f)) {
		idleTime += deltaTime * 0.01;
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