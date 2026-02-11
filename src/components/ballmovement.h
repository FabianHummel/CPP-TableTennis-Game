#pragma once

#include <SDL3_mixer/SDL_mixer.h>

#include "../game/tableside.h"
#include "../utility/vector3.h"
#include "../componentsystem.h"

class BallMovement : public Component
{
  private:
	Transform *transform = nullptr;

	double idleTime = 0;
	constexpr static double IDLE_TIME = 1;
	MIX_Track *ballTrack = nullptr;

  public:
	BallMovement();

	constexpr static double GRAVITY = 0.2;
	constexpr static double FRICTION = 5.0;

	bool fellOff = false;
	bool idle = false;
	Vector3 velocity = {0.0f, 0.0f, 0.0f};

	void onInitialize() override;
	void onStart() override;
	void onUpdate(double deltaTime) override;

	void applyGravity(double deltaTime);
	void applyFriction(double deltaTime);
	void applyVelocity(double deltaTime) const;
	void applyZIndex() const;

	void checkGround(double deltaTime);
	void checkNet(double deltaTime);
	void checkIdle(double deltaTime);
	void checkFellOff() const;

	TableSideX getSideX() const;
	TableSideY getSideY() const;
};
