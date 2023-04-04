#include "home.h"
#include "../components/bubbledrawer.h"
#include "../components/button.h"
#include "../components/debugger.h"
#include "../components/menutitle.h"
#include "../components/spriterenderer.h"
#include "../entity/entitymanager.h"
#include "../gameplay/gamemanager.h"
#include "../render/renderindexes.h"
#include "../utility/magic_enum.hpp"
#include "game.h"
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <cstdio>
#include <functional>

HomePane::HomePane(RenderWindow *window) : Pane(window) {
  title =
      (new Entity("Title"))
          ->addComponent(new SpriteRenderer("res/title.png", window->renderer))
          ->addComponent(new MenuTitle())
          ->getTransform()
          ->apply({RenderWindow::SCREEN_CENTER_X, 0, 425 / 2.0},
                  {RenderWindow::SCREEN_WIDTH, 425}, {0.5f, 0.5f}, 0.0f,
                  RenderIndexes::MENUTITLE);

  background =
      (new Entity("Background"))
          ->addComponent(new BubbleDrawer(window->renderer))
          ->getTransform()
          ->apply({RenderWindow::SCREEN_HEIGHT, 0, 0},
                  {RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT},
                  {0.5f, 0.5f}, -3.8, RenderIndexes::MENUBACKGROUND);

  gamemode = (new Entity("Gamemode"))
                 ->addComponent(new TextRenderer(
                     window->renderer,
                     magic_enum::enum_name(GameMode::SINGLEPLAYER).data(),
                     {40, 40, 40}))
                 ->getTransform()
                 ->apply({RenderWindow::SCREEN_CENTER_X, 0, 800}, {0, 0},
                         {0.5f, 0.5f}, 0.0f, RenderIndexes::UI);

  previous = (new Entity("Previous"))
                 ->addComponent(new Button(
                     nullptr, std::bind(&HomePane::previousGameMode, this)))
                 ->addComponent(
                     new SpriteRenderer("res/arrowleft.png", window->renderer))
                 ->getTransform()
                 ->apply({RenderWindow::SCREEN_CENTER_X - 200, 0, 800},
                         {40, 40}, {0.5f, 0.5f}, 0.0f, RenderIndexes::UI);

  next = (new Entity("Next"))
             ->addComponent(
                 new Button(nullptr, std::bind(&HomePane::nextGameMode, this)))
             ->addComponent(
                 new SpriteRenderer("res/arrowright.png", window->renderer))
             ->getTransform()
             ->apply({RenderWindow::SCREEN_CENTER_X + 200, 0, 800}, {40, 40},
                     {0.5f, 0.5f}, 0.0f, RenderIndexes::UI);
}

void HomePane::onStart() {
  this->gamemodeText = gamemode->getComponent<TextRenderer>();
}

void HomePane::onEvent(SDL_Event event) {
  switch (event.type) {
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_LEFT:
      previousGameMode();
      break;
    case SDLK_RIGHT:
      nextGameMode();
      break;
    case SDLK_RETURN:
      startGame();
      break;
    }
  }
}

void HomePane::dispose() {
  delete title;
  delete background;
  delete gamemode;
  delete previous;
  delete next;
}

void HomePane::previousGameMode() {
  this->currentGameMode--;
  auto text = magic_enum::enum_name(currentGameMode).data();
  this->gamemodeText->setText(text);
}

void HomePane::nextGameMode() {
  this->currentGameMode++;
  auto text = magic_enum::enum_name(currentGameMode).data();
  this->gamemodeText->setText(text);
}

void HomePane::startGame() {
  EntityManager::clear();
  Pane *pane;
  switch (currentGameMode) {
  case GameMode::SINGLEPLAYER:
    pane = new GamePane(window);
    break;
  case GameMode::MULTIPLAYER:
    pane = new GamePane(window);
    break;
  }

  GameManager::switchScene(this, pane);
}
