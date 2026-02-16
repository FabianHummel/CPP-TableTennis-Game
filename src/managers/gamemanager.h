#pragma once

#include "../panes/pane.h"

namespace GameManager
{
    extern Pane* current_pane;
    void next_round();
    void switch_scene(const Pane* from, Pane* to);
};