#pragma once

#include "game/gamemode.h"
#include "panes/pane.h"

namespace GameManager
{
	extern Pane *currentPane;
	void nextRound();
	void switchScene(Pane *from, Pane *to);
};
