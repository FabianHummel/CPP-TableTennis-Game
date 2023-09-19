#pragma once

#include "../../game/tableside.h"
#include "../../soundmanager.h"
#include "../../utility/vector3.h"
#include "../ecs.h"
#include "spriterenderer.h"

class BallMovement : public Component
{
  private:
	Transform *transform;

	double idleTime = 0;
	constexpr static double IDLE_TIME = 1;

  public:
	constexpr static float GRAVITY = 0.2f;
	constexpr static float FRICTION = 5.0f;

	bool fellOff = false;
	bool idle = false;
	Vector3 velocity = {0.0f, 0.0f, 0.0f};

	void onInitialize() override;
	void onStart() override;
	void onUpdate(double deltaTime) override;

	void applyForce(const Vector3 &force);
	void setForce(const Vector3 &force);
	Vector3 getForce() const;

	void applyGravity(double deltaTime);
	void applyFriction(double deltaTime);
	void applyVelocity(double deltaTime);
	void applyZIndex(double deltaTime);

	void checkGround(double deltaTime);
	void checkNet(double deltaTime);
	void checkIdle(double deltaTime);
	void checkFellOff();

	TableSideX getSideX();
	TableSideY getSideY();
};
