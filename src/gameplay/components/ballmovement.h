//
// Created by Fabian Hummel on 12.06.22.
//

#pragma once

#include "../component.h"
#include "../../entity/entity.h"
#include "transform.h"
#include "../../utility/vector3.h"
#include "spriterenderer.h"

class BallMovement : public Component {
private:
	constexpr static float GRAVITY = 0.2f;
	constexpr static float FRICTION = 0.05f;

	Transform *transform;
	SpriteRenderer *sprite;
	Vector3 velocity = {0.0f, 0.0f, 0.0f};

	int idleTime = 0;
	constexpr static int IDLE_TIME = 100;

	bool renderBehind = false;
	bool fellOff = false;
	bool idle = false;

public:
	void onInitialize() override;
	void onStart() override;
	void onUpdate() override;

	void applyForce(const Vector3& force);
	void setForce(const Vector3& force);

	void setIdle();
	void setActive();
	bool isIdle() const;

	void applyGravity();
	void applyFriction();
	void applyVelocity();

	void checkNet();
	void checkGround();
	void checkIdle();
	void checkFellOff();

	bool inTableBounds();
};