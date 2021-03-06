//
// Created by Fabian Hummel on 12.06.22.
//

#pragma once

#include "../component.h"
#include "../../entity/entity.h"
#include "transform.h"
#include "../../utility/vector3.h"
#include "spriterenderer.h"
#include "../../sound/soundmanager.h"

class BallMovement : public Component {
private:
	constexpr static float GRAVITY = 0.2f;
	constexpr static float FRICTION = 0.05f;

	Transform *transform;
	SpriteRenderer *sprite;
	Vector3 velocity = {0.0f, 0.0f, 0.0f};

	double idleTime = 0;
	constexpr static double IDLE_TIME = 1;

	bool renderBehind = false;
	bool fellOff = false;
	bool idle = false;

public:
	void onInitialize() override;
	void onStart() override;
	void onUpdate(double deltaTime) override;

	void applyForce(const Vector3& force);
	void setForce(const Vector3& force);
	Vector3 getForce() const;

	void setIdle();
	void setActive();
	bool isIdle() const;

	void applyGravity(double deltaTime);
	void applyFriction(double deltaTime);
	void applyVelocity(double deltaTime);

	void checkGround(double deltaTime);
	void checkNet(double deltaTime);
	void checkIdle(double deltaTime);
	void checkFellOff();
};