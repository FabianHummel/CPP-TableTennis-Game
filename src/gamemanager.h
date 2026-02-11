#pragma once

#include "panes/pane.h"

namespace GameManager
{
	extern Pane *currentPane;
	void nextRound();
	void switchScene(const Pane *from, Pane *to);
};
