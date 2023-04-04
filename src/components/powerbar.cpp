#include "powerbar.h"
#include "../entity/entitymanager.h"
#include "ballmovement.h"
#include "prediction.h"
#include "transform.h"
#include <cstdio>

void Powerbar::onInitialize() {
  printf("Initializing Powerbar Behavior on %s\n", parent->getName());

  indicator = EntityManager::findEntity("Indicator")->getComponent<Transform>();
  indicatorSprite =
      EntityManager::findEntity("Indicator")->getComponent<SpriteRenderer>();
  ball = EntityManager::findEntity("Ball")->getComponent<BallMovement>();

  Entity *powerboxEntity = EntityManager::findEntity("Powerbox");
  powerbox = powerboxEntity->getComponent<Transform>();
  powerboxSprite = powerboxEntity->getComponent<SpriteRenderer>();

  Entity *powerbarEntity = EntityManager::findEntity("Powerbar");
  powerbar = powerbarEntity->getComponent<Transform>();
  powerbarSprite = powerbarEntity->getComponent<SpriteRenderer>();

  Entity *predictionEntity = EntityManager::findEntity("Prediction");
  prediction = predictionEntity->getComponent<Prediction>();
}

void Powerbar::onEvent(SDL_Event event) {
  switch (event.type) {
  case SDL_MOUSEBUTTONDOWN: {
    int x, y;
    SDL_GetMouseState(&x, &y);
    onClick(x * 2, y * 2);
    break;
  }

  case SDL_MOUSEBUTTONUP: {
    onRelease();
    break;
  }

  case SDL_MOUSEMOTION: {
    int x, y;
    SDL_GetMouseState(&x, &y);
    onDrag(x * 2, y * 2);
    break;
  }
  }
}

void Powerbar::setProgress(float v, float y) {
  this->size = v;

  int progress = size / 100.0f * 250;
  powerbarSprite->setSrcrect({0, 250 - progress, 250, progress});

  powerbar->setScaleY(size / 100.0f * 70);
}

void Powerbar::onStart() {
  indicatorSprite->setVisible(false);
  powerboxSprite->setVisible(false);
  powerbarSprite->setVisible(false);
}

void Powerbar::onClick(int x, int y) {
  isDragging = true;
  startX = x;
  startY = y;
  // printf("began mouse drag at: %d, %d\n", startX, startY);

  indicator->setPosition({(float)startX, 0.0f, (float)startY});
  powerbox->setPosition({startX - 100.0f, 0.0f, (float)startY});
  powerbar->setPosition(
      {startX - 100.0f, 0.0f, (float)startY + powerbox->getScaleY() / 2.0f});
}

void Powerbar::onRelease() {
  indicatorSprite->setVisible(false);
  powerboxSprite->setVisible(false);
  powerbarSprite->setVisible(false);

  isDragging = false;
  // printf("ended mouse drag at: %d, %d, ", currentX, currentY);
  // printf("with a delta of: %d, %d ", deltaX, deltaY);
  // printf("and an angle of: %d°\n", angle);

  if (strength > 0.1f && ball->parent->getTransform()->getY() > -10.0f) {
    ball->setActive();

    double length = sqrt(deltaX * deltaX + deltaY * deltaY);
    double forceX = -(double)deltaX / length * strength * 7.0;
    double forceY = -(double)deltaY / length * strength * 7.0;
    ball->setForce({(float)forceX, 7.f, (float)forceY});
  }

  strength = 0.0f;
}

void Powerbar::onDrag(int x, int y) {
  if (isDragging) {
    indicatorSprite->setVisible(true);
    powerboxSprite->setVisible(true);
    powerbarSprite->setVisible(true);

    int currentX = x;
    int currentY = y;

    deltaX = currentX - startX;
    deltaY = currentY - startY;

    float angle = 180.0f - atan2(deltaX, deltaY) * 180 / M_PI;
    indicator->setRotation(angle);

    strength = std::clamp(
        (float)sqrt(deltaX * deltaX + deltaY * deltaY) / 200.0f, 0.0f, 1.0f);
    setProgress(strength * 100.0f, startY);
    report();
  }
}

void Powerbar::report() {
  prediction->onMotion(startX, startY, deltaX, deltaY, strength);
}