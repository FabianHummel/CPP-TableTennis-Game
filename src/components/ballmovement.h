#pragma once

#include "../game/tableside.h"
#include "../utility/vector3.h"
#include "../componentsystem.h"

class BallMovement : public Component
{
  private:
	Transform *transform;

	double idleTime = 0;
	constexpr static double IDLE_TIME = 1;

  public:
	constexpr static double GRAVITY = 0.2;
	constexpr static double FRICTION = 5.0;

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
