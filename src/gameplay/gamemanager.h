#pragma once

#include "../panes/pane.h"
#include "gamemode.h"

namespace GameManager
{
 	static Pane *currentPane;
	void nextRound();
	void switchScene(Pane *from, Pane *to);
};
