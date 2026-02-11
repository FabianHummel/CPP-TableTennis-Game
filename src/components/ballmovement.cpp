#include "ballmovement.h"
#include "../gamemanager.h"
#include "../soundmanager.h"
#include "../utility/mathutil.h"
#include "../utility/renderindexes.h"
#include "../utility/renderwindow.h"

BallMovement::BallMovement()
{
	this->name = "Ball Movement";
}

void BallMovement::onInitialize()
{
	this->transform = parent->getComponent<Transform>();
	this->ballTrack = MIX_CreateTrack(SoundManager::mixer);

	SoundManager::addSound("res/sounds/ball-bounce-1.wav", "bounce 1");
	SoundManager::addSound("res/sounds/ball-bounce-2.wav", "bounce 2");
	SoundManager::addSound("res/sounds/ball-bounce-3.wav", "bounce 3");
}

void BallMovement::onStart()
{
	this->idle = true;
	this->transform->position = { RenderWindow::SCREEN_CENTER_X, 100, 650 };
}

void BallMovement::onUpdate(const double deltaTime)
{
	this->checkGround(deltaTime);
	this->checkNet(deltaTime);
	this->checkIdle(deltaTime);
	this->checkFellOff();

	this->applyZIndex();
	this->applyGravity(deltaTime);
	this->applyFriction(deltaTime);
	this->applyVelocity(deltaTime);
}

void BallMovement::applyGravity(const double deltaTime)
{
	this->velocity.y -= GRAVITY * deltaTime * 100.0;
}

void BallMovement::applyFriction(const double deltaTime)
{
	if (MathUtil::closeToPoint(transform->position.y, 0.1))
	{
		auto vel = Vector3(velocity.x, 0.0f, velocity.z);
		MathUtil::moveTowardsZero(vel, FRICTION * deltaTime);
		velocity.x = vel.x;
		velocity.z = vel.z;
	}
}

void BallMovement::applyVelocity(const double deltaTime) const
{
	transform->position.x += this->velocity.x * deltaTime * 100.0;
	transform->position.y += this->velocity.y * deltaTime * 100.0;
	transform->position.z += this->velocity.z * deltaTime * 100.0;
}

void BallMovement::applyZIndex() const
{
	// Move ball behind when it falls off at the top
	if (transform->position.y < 0 /* && transform->getZ() < 470 */)
	{
		transform->zIndex = RenderIndexes::Game::TABLE - 1;
		return;
	}

	if (transform->position.z > 470)
	{
		transform->zIndex = RenderIndexes::Game::NET + 2;
	}
	else
	{
		transform->zIndex = RenderIndexes::Game::NET - 2;
	}
}

void BallMovement::checkGround(double deltaTime)
{
	if (transform->position.y >= 0)
	{
		parent->opacity = SDL_ALPHA_OPAQUE;
		return;
	}

	// Bounce off the table
	if (transform->inTableBounds())
	{
		transform->position.y = 0;
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
		const float gain = (float) std::clamp(velocity.y * 0.5, 0.0, 1.0);
		SoundManager::playRndSound(ballTrack, {"bounce 1", "bounce 2", "bounce 3"}, gain);
	}
	else
	{
		// Otherwise, fall off the table and fade away
		parent->opacity = std::clamp(SDL_ALPHA_OPAQUE - (int)abs(transform->position.y), 0, 255);
	}
}

void BallMovement::checkNet(const double deltaTime)
{
	if (transform->position.y > 70)
	{
		return;
	}

	if (const double newZ = transform->position.z + velocity.z * deltaTime * 100.0;
		transform->position.z > 470 && newZ < 470 || transform->position.z < 470 && newZ > 470)
	{
		// Ball is going to be in the net
		transform->position.z = 470;
		this->velocity.z *= -0.2f;
		this->velocity.x *= 0.5f;
	}
}

void BallMovement::checkIdle(const double deltaTime)
{
	if (!MathUtil::closeToPoint(velocity.magnitude(), 0.3f))
	{
		idleTime = 0.0;
		return;
	}

	idleTime += deltaTime;
	if (idleTime > IDLE_TIME)
	{
		GameManager::nextRound();
		idleTime = 0;
	}
}

void BallMovement::checkFellOff() const
{
	if (transform->position.y < 0)
	{
		// setIdle();
	}

	if (transform->position.y < -1000)
	{
		GameManager::nextRound();
	}
}

TableSideX BallMovement::getSideX() const
{
	return transform->position.x < RenderWindow::SCREEN_CENTER_X ? TableSideX::LEFT : TableSideX::RIGHT;
}

TableSideY BallMovement::getSideY() const
{
	return transform->position.y < RenderWindow::SCREEN_CENTER_Y ? TableSideY::BOTTOM : TableSideY::TOP;
}
