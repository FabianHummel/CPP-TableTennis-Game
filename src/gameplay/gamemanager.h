#pragma once

#include "../components/ballmovement.h"
#include "../menu/pane.h"
#include "gamemode.h"

class GameManager
{
  private:
  public:
	static Pane *currentPane;
	static void nextRound();
	static void switchScene(Pane *from, Pane *to);
};
