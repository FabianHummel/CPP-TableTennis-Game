#include "ballmovement.h"
#include "../gamemanager.h"
#include "../soundmanager.h"
#include "../utility/mathutil.h"
#include "../utility/renderindexes.h"
#include "../utility/renderwindow.h"

void BallMovement::onInitialize()
{
	printf("Initializing Ball Movement Behavior on %s\n", parent->name);
	transform = parent->getComponent<Transform>();

	SoundManager::addSound("res/sounds/ball-bounce-1.wav", "bounce 1");
	SoundManager::addSound("res/sounds/ball-bounce-2.wav", "bounce 2");
	SoundManager::addSound("res/sounds/ball-bounce-3.wav", "bounce 3");
}

void BallMovement::onStart()
{
	this->idle = true;
	transform->setPosition({RenderWindow::SCREEN_CENTER_X, 100, 650});
}

void BallMovement::onUpdate(double deltaTime)
{
	this->checkGround(deltaTime);
	this->checkNet(deltaTime);
	this->checkIdle(deltaTime);
	this->checkFellOff();

	this->applyZIndex(deltaTime);
	this->applyGravity(deltaTime);
	this->applyFriction(deltaTime);
	this->applyVelocity(deltaTime);
}

void BallMovement::applyForce(const Vector3 &force)
{
	this->velocity += force;
}

void BallMovement::setForce(const Vector3 &force)
{
	this->velocity = force;
}

Vector3 BallMovement::getForce() const
{
	return this->velocity;
}

void BallMovement::applyGravity(double deltaTime)
{
	this->velocity.y -= GRAVITY * deltaTime * 100.0;
}

void BallMovement::applyFriction(double deltaTime)
{
	if (MathUtil::closeToPoint(transform->getY(), 0.1))
	{
		auto vel = Vector3(velocity.x, 0.0f, velocity.z);
		MathUtil::moveTowardsZero(vel, FRICTION * deltaTime);
		velocity.x = vel.x;
		velocity.z = vel.z;
	}
}

void BallMovement::applyVelocity(double deltaTime)
{
	transform->mvByX(this->velocity.x * deltaTime * 100.0);
	transform->mvByY(this->velocity.y * deltaTime * 100.0);
	transform->mvByZ(this->velocity.z * deltaTime * 100.0);
}

void BallMovement::applyZIndex(double deltaTime)
{
	// Move ball behind when it falls off at the top
	if (transform->getY() < 0 /* && transform->getZ() < 470 */)
	{
		transform->setI(RenderIndexes::Game::TABLE - 1);
		return;
	}

	if (transform->getZ() > 470)
	{
		transform->setI(RenderIndexes::Game::NET + 2);
	}
	else
	{
		transform->setI(RenderIndexes::Game::NET - 2);
	}
}

void BallMovement::checkGround(double deltaTime)
{
	if (transform->getY() >= 0)
	{
		parent->opacity = SDL_ALPHA_OPAQUE;
		return;
	}

	// Bounce off the table
	if (transform->inTableBounds())
	{
		transform->setY(0);
		velocity.y *= -0.8f;

		if (velocity.y < 1.0f)
		{
			velocity.y = 0.0f;
		}

		if (idle)
		{
			velocity.y = 8.0f;
		}

		parent->opacity = SDL_ALPHA_OPAQUE;
		SoundManager::playRndSound({"bounce 1", "bounce 2", "bounce 3"}, std::clamp(velocity.y * 50.0f, 0.0f, 100.0f));
	}
	else
	{
		// Otherwise, fall off the table and fade away
		parent->opacity = std::clamp(SDL_ALPHA_OPAQUE - (int)abs(transform->getY()), 0, 255);
	}
}

void BallMovement::checkNet(double deltaTime)
{
	if (transform->getY() > 70)
		return;

	double newZ = transform->getZ() + velocity.z * deltaTime * 100.0;
	if (transform->getZ() > 470 && newZ < 470)
	{
		// Ball is going to be in the net
		transform->setZ(470);
		this->velocity.z *= -0.2f;
		this->velocity.x *= 0.5f;
	}
	else if (transform->getZ() < 470 && newZ > 470)
	{
		// Ball is going to be in the net
		transform->setZ(470);
		this->velocity.z *= -0.2f;
		this->velocity.x *= 0.5f;
	}
}

void BallMovement::checkIdle(double deltaTime)
{
	if (MathUtil::closeToPoint(velocity.magnitude(), 0.3f))
	{
		idleTime += deltaTime;
		if (idleTime > IDLE_TIME)
		{
			GameManager::nextRound();
			idleTime = 0;
		}
	}
	else
	{
		idleTime = 0.0;
	}
}

void BallMovement::checkFellOff()
{
	if (transform->getY() < 0)
	{
		// setIdle();
	}

	if (transform->getY() < -1000)
	{
		GameManager::nextRound();
	}
}

TableSideX BallMovement::getSideX()
{
	return transform->getX() < RenderWindow::SCREEN_CENTER_X ? TableSideX::LEFT : TableSideX::RIGHT;
}

TableSideY BallMovement::getSideY()
{
	return transform->getY() < RenderWindow::SCREEN_CENTER_Y ? TableSideY::BOTTOM : TableSideY::TOP;
}
