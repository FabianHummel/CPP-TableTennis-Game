#pragma once

#include "../components/componentsystem.h"
#include "../shared/enet.h"
#include "pane.h"

class LobbyPane : public Pane
{
  private:
    const char READY_TEXT[12] = "Ready!     ";
    const char NOT_READY_TEXT[10] = "Not ready";

  protected:
    Entity *versus_title;
    Entity *versus_enemy_name;
    Entity *background;
    Entity *backButton;
    Entity *match_code_button;
    Entity *readyButton;

    ENetPeer *enemy;

    std::string match_code;
    std::string player_name;
    std::string enemy_name;
    bool is_ready;
    bool is_enemy_ready;

    void back() const;
    void handle_match_code_button_click() const;
    void set_match_code_hint_visibility(bool is_visible) const;

  public:
    explicit LobbyPane(SDL_Renderer *renderer, const std::string &match_code, const std::string &player_name);
    ~LobbyPane() override;

    void on_start() override;
    void on_event(const SDL_Event *event) override;
    void on_gui(double deltaTime) override;
};