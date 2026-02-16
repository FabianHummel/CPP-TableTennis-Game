#pragma once

#include "../components/componentsystem.h"
#include "../components/textrenderer.h"
#include "../game/gamemode.h"
#include "pane.h"

class HomePane : public Pane
{
  private:
    char match_code[6] = {""};
    char player_name[6] = {""};
    GameMode current_game_mode{};
    TextRenderer *gamemode_text{};

    Entity *title;
    Entity *background;
    Entity *gamemode;
    Entity *previous;
    Entity *next;
    Entity *ball;
    Entity *menuline;
    Entity *start;
    Entity *match_code_input;
    Entity *player_name_input;

  public:
    explicit HomePane(SDL_Renderer *renderer);
    ~HomePane() override;

    void on_start() override;
    void on_event(const SDL_Event *event) override;
    void on_gui(double delta_time) override;

    void change_game_mode() const;
    void previous_game_mode();
    void next_game_mode();
    void start_server() const;
    void join_server() const;
    void start_single_player() const;
    void start_or_join_server() const;
};