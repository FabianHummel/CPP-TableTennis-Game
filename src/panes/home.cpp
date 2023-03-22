#include "home.h"
#include "../entity/entitymanager.h"
#include "../render/renderindexes.h"
#include "../components/spriterenderer.h"
#include "../components/menutitle.h"
#include "../components/bubbledrawer.h"
#include "../components/textrenderer.h"
#include "../components/button.h"
#include "../components/debugger.h"
#include <cstdio>
#include <functional>

HomePane::HomePane(RenderWindow *window) : Pane(window)
{
   title = ( new Entity("Title") )
      ->addComponent(new SpriteRenderer("res/title.png", window->renderer))
      ->addComponent(new MenuTitle())
      ->getTransform()->apply(
	 { RenderWindow::SCREEN_CENTER_X, 0, 425/2.0 },
	 { RenderWindow::SCREEN_WIDTH, 425 },
	 { 0.5f, 0.5f }, 0.0f, RenderIndexes::MENUTITLE);

   background = ( new Entity("Background") )
      ->addComponent(new BubbleDrawer(window->renderer))
      ->getTransform()->apply(
	 { RenderWindow::SCREEN_HEIGHT, 0, 0 },
	 { RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT },
	 { 0.5f, 0.5f }, -3.8, RenderIndexes::MENUBACKGROUND);

   gamemode = ( new Entity("Gamemode") )
      ->addComponent(new TextRenderer(window->renderer, "MULTIPLAYER", {40, 40, 40}))
      ->getTransform()->apply(
	 { RenderWindow::SCREEN_CENTER_X, 0, 800},
	 { 0, 0 }, { 0.5f, 0.5f }, 0.0f, RenderIndexes::UI);

   previous = ( new Entity("Previous") )
      ->addComponent(new Button(nullptr, std::bind(&HomePane::previousGameMode, this)))
      ->addComponent(new SpriteRenderer("res/arrowleft.png", window->renderer))
      ->getTransform()->apply(
	 { RenderWindow::SCREEN_CENTER_X - 200, 0, 800 },
	 { 40, 40 }, { 0.5f, 0.5f }, 0.0f, RenderIndexes::UI);

   next = ( new Entity("Next") )
      ->addComponent(new Button(nullptr, std::bind(&HomePane::nextGameMode, this)))
      ->addComponent(new SpriteRenderer("res/arrowright.png", window->renderer))
      ->getTransform()->apply(
	 { RenderWindow::SCREEN_CENTER_X + 200, 0, 800 },
	 { 40, 40 }, { 0.5f, 0.5f }, 0.0f, RenderIndexes::UI);

   EntityManager::initialize();
}

void HomePane::onStart()
{     
   EntityManager::start();
}

void HomePane::onGui(double deltaTime)
{
   EntityManager::sort();
   EntityManager::update(deltaTime);
}

void HomePane::dispose()
{
   delete title;
   EntityManager::clear();
}

void HomePane::previousGameMode() const
{
   printf("Previous");
}

void HomePane::nextGameMode() const
{
   printf("Next");
}
