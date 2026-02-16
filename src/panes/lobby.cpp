#include "lobby.h"
#include "../components/bubbledrawer.h"
#include "../components/button.h"
#include "../components/menutitle.h"
#include "../components/spriterenderer.h"
#include "../managers/ecsmanager.h"
#include "../managers/errormanager.h"
#include "../managers/fontmanager.h"
#include "../managers/gamemanager.h"
#include "../managers/netmanager.h"
#include "../presets/index.h"
#include "../shared/packets.h"
#include "../utility/renderindexes.h"
#include "../utility/renderwindow.h"
#include "home.h"

LobbyPane::LobbyPane(SDL_Renderer *renderer, const std::string &match_code, const std::string &player_name)
    : Pane(renderer)
{
    this->match_code = match_code;
    this->player_name = player_name;
    this->is_ready = false;
    this->is_enemy_ready = false;

    NetManager::on_punch_fail = []
    {
        // Display error
    };

    NetManager::on_punched = [this](ENetPeer *enemy)
    {
        this->enemy = enemy;

        versus_enemy_name->get_child("Text")->get_component<TextRenderer>()->set_text("Enemy");

        Buffer b(128);
        b.write(PEER_ENEMY_DATA);
        b.write(this->player_name);
        b.write(this->is_ready);
        ENetPacket *packet = enet_packet_create(b.data(), b.size(), ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(enemy, 0, packet);
    };

    NetManager::on_peer_ping = [](const double rtt)
    {
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "\rRound trip time: %f", rtt);
        fflush(stdout);
    };

    NetManager::on_enemy_data_received = [this](const std::string &enemy_name, const bool ready_status)
    {
        this->enemy_name = enemy_name;
        this->is_enemy_ready = ready_status;
        versus_enemy_name->get_child("Text")->get_component<TextRenderer>()->set_text(this->enemy_name.c_str());
        versus_enemy_name->get_child("Ready-Image")->get_component<SpriteRenderer>()->visible = this->is_enemy_ready;
    };

    NetManager::on_enemy_ready_status_received = [this](const bool ready_status)
    {
        this->is_enemy_ready = ready_status;
        versus_enemy_name->get_child("Ready-Image")->get_component<SpriteRenderer>()->visible = this->is_enemy_ready;
    };

    set_entity(versus_title, new Entity("Versus-Title"))
        ->add_component(new SpriteRenderer("res/versus.png", renderer))
        ->add_component(new MenuTitle())
        ->transform->apply({RenderWindow::SCREEN_CENTER_X, 0, 160}, {500, 138}, {0.5f, 0.5f}, 0.0f,
                           RenderIndexes::Menu::TITLE);

    set_entity(versus_enemy_name, new Entity("Versus-Enemy-Name"))
        ->use_preset(Presets::readonly_text_input(renderer, "Waiting...", FontManager::DEFAULT))
        ->add_component(new MenuTitle(0.5))
        ->transform
        ->apply({RenderWindow::SCREEN_CENTER_X + 100, 0, 300}, {300, 100}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI)
        ->add_child((new Entity("Ready-Image"))
                        ->add_component(new SpriteRenderer("res/ready.png", renderer))
                        ->transform->apply({90, 0, -10}, {42, 42}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI));

    set_entity(match_code_button, new Entity("Invite-Code"))
        ->use_preset(Presets::button(renderer, match_code.c_str(), FontManager::BIG,
                                     std::bind(&LobbyPane::handle_match_code_button_click, this)))
        ->add_component(new Button({
            .on_mouse_over = std::bind(&LobbyPane::set_match_code_hint_visibility, this, true),
            .on_mouse_exit = std::bind(&LobbyPane::set_match_code_hint_visibility, this, false),
        }))
        ->transform
        ->apply({RenderWindow::SCREEN_CENTER_X, 0, 550}, {370, 150}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI)
        ->add_child((new Entity("Hint"))
                        ->add_component(new SpriteRenderer("res/copyarrow.png", renderer))
                        ->transform->apply({-150, 0, 80}, {300, 105}, {0.0f, 0.0f}, 0.0f, RenderIndexes::Menu::UI)
                        ->apply(false));

    set_entity(background, new Entity("Background"))
        ->add_component(new BubbleDrawer(renderer))
        ->transform->apply({RenderWindow::SCREEN_HEIGHT, 0, 0},
                           {RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT}, {0.5f, 0.5f}, -3.8,
                           RenderIndexes::Menu::BACKGROUND);

    set_entity(backButton, new Entity("Back-Button"))
        ->add_component(new SpriteRenderer("res/menuarrow.png", renderer))
        ->add_component(new Button(std::bind(&LobbyPane::back, this)))
        ->transform->apply({40, 0, 40}, {50, 50}, {0.5f, 0.5f}, 180.0f, RenderIndexes::Menu::UI);

    set_entity(readyButton, new Entity("Ready-Button"))
        ->use_preset(Presets::button(
            renderer, NOT_READY_TEXT, FontManager::DEFAULT,
            [this]
            {
                this->is_ready = !this->is_ready;
                readyButton->get_child("Text")->get_component<TextRenderer>()->set_text(this->is_ready ? READY_TEXT
                                                                                                      : NOT_READY_TEXT);
                readyButton->get_child("Ready-Image")->get_component<SpriteRenderer>()->visible = this->is_ready;

                if (enemy == nullptr)
                    return;
                Buffer b(128);
                b.write(PEER_ENEMY_READY_STATUS);
                b.write(this->is_ready);
                ENetPacket *packet = enet_packet_create(b.data(), b.size(), ENET_PACKET_FLAG_RELIABLE);
                enet_peer_send(enemy, 0, packet);
            }))
        ->transform
        ->apply({RenderWindow::SCREEN_CENTER_X, 0, 1000}, {300, 100}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI)
        ->add_child((new Entity("Ready-Image"))
                        ->add_component(new SpriteRenderer("res/ready.png", renderer))
                        ->transform->apply({90, 0, -10}, {42, 42}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI));
}

LobbyPane::~LobbyPane()
{
    delete versus_title;
    delete versus_enemy_name;
    delete match_code_button;
    delete background;
    delete backButton;
    delete readyButton;
}

void LobbyPane::on_start()
{
    readyButton->get_child("Ready-Image")->get_component<SpriteRenderer>()->visible = false;
    versus_enemy_name->get_child("Ready-Image")->get_component<SpriteRenderer>()->visible = false;
}

void LobbyPane::on_event(const SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_EVENT_KEY_DOWN:
        switch (event->key.key)
        {
        case SDLK_ESCAPE:
            this->back();
            break;
        default:
            break;
        }
    default:
        break;
    }
}

void LobbyPane::on_gui(double deltaTime)
{
    ErrorManager::show_errors(renderer);
}

void LobbyPane::back() const
{
    EcsManager::clear();
    Pane *pane = new HomePane(renderer);
    GameManager::switch_scene(this, pane);
}

void LobbyPane::handle_match_code_button_click() const
{
    SDL_SetClipboardText(this->match_code.c_str());
}

void LobbyPane::set_match_code_hint_visibility(const bool is_visible) const
{
    this->match_code_button->get_child("Hint")->visible = is_visible;
}