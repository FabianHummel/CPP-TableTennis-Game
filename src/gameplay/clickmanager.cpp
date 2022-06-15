//
// Created by Fabian Hummel on 28.05.22.
//

#include <cstdio>
#include "clickmanager.h"
#include "../entity/entitymanager.h"
#include "components/ballmovement.h"

void ClickManager::onClick(int x, int y) {
      printf("clicked at: %d, %d\n", x, y);

	  BallMovement *ball = EntityManager::findEntity("Ball")->getComponent<BallMovement>();
	  ball->setActive();
}
