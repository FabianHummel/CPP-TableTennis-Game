#include "home.h"
#include "game.h"
#include "lobby.h"

#include "../managers/animationmanager.h"
#include "../managers/ecsmanager.h"
#include "../managers/errormanager.h"
#include "../managers/fontmanager.h"
#include "../managers/gamemanager.h"
#include "../managers/netmanager.h"

#include "../components/bubbledrawer.h"
#include "../components/button.h"
#include "../components/menuballbehaviour.h"
#include "../components/menutitle.h"
#include "../components/spriterenderer.h"

#include "../presets/index.h"

#include "../utility/renderindexes.h"
#include "../utility/renderwindow.h"

#include <functional>

HomePane::HomePane(SDL_Renderer *renderer) : Pane(renderer)
{
    set_entity(title, new Entity("Title"))
        ->add_component(new SpriteRenderer("res/title.png", renderer))
        ->add_component(new MenuTitle())
        ->transform->apply({RenderWindow::SCREEN_CENTER_X, 0, 0}, {RenderWindow::SCREEN_WIDTH, 425}, {0.5f, 0.0f}, 0.0f,
                           RenderIndexes::Menu::TITLE);

    set_entity(background, new Entity("Background"))
        ->add_component(new BubbleDrawer(renderer))
        ->transform->apply({RenderWindow::SCREEN_HEIGHT, 0, 0},
                           {RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT}, {0.5f, 0.5f}, -3.8,
                           RenderIndexes::Menu::BACKGROUND);

    set_entity(gamemode, new Entity("Gamemode"))
        ->add_component(new TextRenderer(renderer, magic_enum::enum_name(GameMode::SINGLEPLAYER).data(),
                                         FontManager::DEFAULT, {40, 40, 40}))
        ->transform->apply({RenderWindow::SCREEN_CENTER_X, 0, 700}, {300, 100}, {0.5f, 0.5f}, 0.0f,
                           RenderIndexes::Menu::UI);

    set_entity(previous, new Entity("Previous"))
        ->add_component(new Button(std::bind(&HomePane::previous_game_mode, this)))
        ->add_component(new SpriteRenderer("res/menuarrow.png", renderer))
        ->transform->apply({RenderWindow::SCREEN_CENTER_X - 200, 0, 700}, {40, 40}, {0.5f, 0.5f}, 180.0f,
                           RenderIndexes::Menu::UI);

    set_entity(next, new Entity("Next"))
        ->add_component(new Button(std::bind(&HomePane::next_game_mode, this)))
        ->add_component(new SpriteRenderer("res/menuarrow.png", renderer))
        ->transform->apply({RenderWindow::SCREEN_CENTER_X + 200, 0, 700}, {40, 40}, {0.5f, 0.5f}, 0.0f,
                           RenderIndexes::Menu::UI);

    set_entity(ball, new Entity("Ball"))
        ->add_component(new SpriteRenderer("res/ball.png", renderer))
        ->add_component(new MenuBallBehaviour())
        ->transform->apply({RenderWindow::SCREEN_CENTER_X, 0, 220}, {40, 40}, {0.5f, 0.5f}, 0.0f,
                           RenderIndexes::Menu::BALL);

    set_entity(menuline, new Entity("Menuline"))
        ->add_component(new SpriteRenderer("res/menuline.png", renderer))
        ->transform->apply({RenderWindow::SCREEN_CENTER_X, 0, 650}, {300, 6}, {0.5f, 0.5f}, 0.0f,
                           RenderIndexes::Menu::UI);

    set_entity(start, new Entity("Play-Button"))
        ->use_preset(
            Presets::button(renderer, "Play", FontManager::DEFAULT, std::bind(&HomePane::start_single_player, this)))
        ->transform->apply({RenderWindow::SCREEN_CENTER_X, 0, 1000}, {300, 100}, {0.5f, 0.5f}, 0.0f,
                           RenderIndexes::Menu::UI);

    set_entity(player_name_input, new Entity("Player-Name-Input"))
        ->transform
        ->apply({RenderWindow::SCREEN_CENTER_X, 0, 870}, {300, 120}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI)
        ->apply(false)
        ->use_preset(Presets::text_input(renderer, player_name, sizeof(player_name) - 1, "Name", FontManager::DEFAULT));

    set_entity(match_code_input, new Entity("Match-Code-Input"))
        ->transform
        ->apply({RenderWindow::SCREEN_CENTER_X, 0, 1000}, {300, 120}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI)
        ->apply(false)
        ->use_preset(Presets::text_input(renderer, match_code, sizeof(match_code) - 1, "Code", FontManager::DEFAULT))
        ->add_child((new Entity("Continue"))
                        ->add_component(new Button(std::bind(&HomePane::start_or_join_server, this)))
                        ->add_component(new SpriteRenderer("res/menuarrow.png", renderer))
                        ->transform->apply({110, 0, -10}, {40, 40}, {0.5f, 0.5f}, 0.0f, 0));
}

HomePane::~HomePane()
{
    delete title;
    delete background;
    delete gamemode;
    delete previous;
    delete next;
    delete ball;
    delete menuline;
    delete start;
    delete player_name_input;
    delete match_code_input;
}

void HomePane::on_start()
{
    this->gamemode_text = gamemode->get_component<TextRenderer>();
}

void HomePane::on_event(const SDL_Event *event)
{
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        if (event->key.key == SDLK_LEFT)
        {
            previous_game_mode();
        }
        else if (event->key.key == SDLK_RIGHT)
        {
            next_game_mode();
        }
        else if (event->key.key == SDLK_RETURN)
        {
            if (this->current_game_mode == GameMode::SINGLEPLAYER)
            {
                start_single_player();
            }
            else if (this->current_game_mode == GameMode::MULTIPLAYER)
            {
                start_or_join_server();
            }
        }
    }
}

void HomePane::on_gui(double delta_time)
{
    ErrorManager::show_errors(renderer);
}

void HomePane::change_game_mode() const
{
    const auto text = magic_enum::enum_name(current_game_mode).data();
    this->gamemode_text->set_text(text);

    if (this->current_game_mode == GameMode::SINGLEPLAYER)
    {
        AnimationManager::play(Animations::swipe_in(start, false), Easings::ease_out, 0.4);
        AnimationManager::play(Animations::fade_in(start), Easings::linear, 0.2);

        AnimationManager::play(Animations::swipe_out(player_name_input, true), Easings::ease_out, 0.4);
        AnimationManager::play(Animations::fade_out(player_name_input), Easings::ease_out, 0.2);

        AnimationManager::play(Animations::swipe_out(match_code_input, true), Easings::ease_out, 0.4);
        AnimationManager::play(Animations::fade_out(match_code_input), Easings::ease_out, 0.2);
    }

    if (this->current_game_mode == GameMode::MULTIPLAYER)
    {
        AnimationManager::play(Animations::swipe_out(start, false), Easings::ease_out, 0.4);
        AnimationManager::play(Animations::fade_out(start), Easings::ease_out, 0.2);

        AnimationManager::play(Animations::swipe_in(player_name_input, true), Easings::ease_out, 0.4);
        AnimationManager::play(Animations::fade_in(player_name_input), Easings::linear, 0.2);

        AnimationManager::play(Animations::swipe_in(match_code_input, true), Easings::ease_out, 0.4);
        AnimationManager::play(Animations::fade_in(match_code_input), Easings::linear, 0.2);
    }
}

void HomePane::previous_game_mode()
{
    this->current_game_mode--;
    this->change_game_mode();
}

void HomePane::next_game_mode()
{
    this->current_game_mode++;
    this->change_game_mode();
}

void HomePane::start_server() const
{
    NetManager::on_match_found = [this](const char *match_code)
    {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Match found: %s\n", match_code);
        EcsManager::clear();
        Pane *lobby = new LobbyPane(renderer, match_code, player_name);
        GameManager::switch_scene(this, lobby);
    };

    NetManager::on_match_not_found = []
    {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Match not found\n");
    };

    if (!NetManager::start(nullptr))
    {
        ErrorManager::queue_error("Could not create an online match.\nCheck logs for further details.");
    }
}

void HomePane::join_server() const
{
    EcsManager::clear();
    Pane *lobby = new LobbyPane(renderer, this->match_code, this->player_name);
    NetManager::start(this->match_code);
    GameManager::switch_scene(this, lobby);
}

void HomePane::start_single_player() const
{
    EcsManager::clear();
    Pane *pane = new GamePane(renderer);
    GameManager::switch_scene(this, pane);
}

void HomePane::start_or_join_server() const
{
    if (this->match_code[0] == '\0')
    {
        start_server();
    }
    else
    {
        join_server();
    }
}