#include "lobby.h"
#include "../presets/index.h"
#include "../ecsmanager.h"
#include "../gamemanager.h"
#include "../netmanager.h"
#include "../fontmanager.h"
#include "../utility/renderindexes.h"
#include "home.h"

LobbyPane::LobbyPane(RenderWindow *window, const char *match_code, const char *player_name, ENetPeer *enemy) : LobbyPane(window, match_code, player_name) {
	this->enemy = enemy;

	Buffer b;
	b.Write(PEER_ENEMY_DATA);
	b.Write(player_name);
	ENetPacket *packet = enet_packet_create(b.GetBuffer(), b.GetSize(), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(enemy, 0, packet);
}

LobbyPane::LobbyPane(RenderWindow *window, const char *match_code, const char *player_name) : Pane(window)
{
	this->playerName = player_name;

	NetManager::on_punch_fail = [] {
		// Display error
	};
	NetManager::on_punched = [this](ENetPeer *enemy) {
		this->enemy = enemy;

		TextRenderer *pTextRenderer = versus->getChild("Opponent")->getComponent<TextRenderer>();
		pTextRenderer->setText("Enemy");
	};
	NetManager::on_peer_ping = [](double rtt) {
		//	printf("Round trip time: %f\n", rtt);
	};

	NetManager::on_enemy_data_received = [this](const char *enemyName) {
		TextRenderer *pTextRenderer = versus->getChild("Opponent")->getComponent<TextRenderer>();
		pTextRenderer->setText(enemyName);
	};

	versus = EcsManager::addEntity(new Entity("Versus"))
		->addComponent(new SpriteRenderer("res/versus.png", window->renderer))
	    ->addComponent(new MenuTitle())
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 230}, {700, 348}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::TITLE)
		->addChild((new Entity("Opponent"))
			->addComponent(new TextRenderer(window->renderer, "Waiting...", FontManager::BIG, {64, 64, 64}))
			->transform
			->apply({0, 0, 30}, {0, 0}, {0.5f, 0.5f}, 0.0f, 0));

	matchCodeButton = EcsManager::addEntity(new Entity("Invite-Code"))
		->usePreset(Presets::button(window->renderer, match_code, FontManager::BIG, [match_code] { SDL_SetClipboardText(match_code); }))
	    ->addComponent(new Button(nullptr, nullptr, [this] {
				matchCodeButton->getChild("Hint")->visible = true;
			}, [this] {
				matchCodeButton->getChild("Hint")->visible = false;
			}))
		->transform
	    ->apply({RenderWindow::SCREEN_CENTER_X, 0, 550}, { 370, 150 }, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI)
		->addChild((new Entity("Hint"))
			->addComponent(new SpriteRenderer("res/copyarrow.png", window->renderer))
			->transform
	        ->apply({-150, 0, 80}, {300, 105}, {0.0f, 0.0f}, 0.0f, RenderIndexes::Menu::UI)
	        ->apply(false));

	background = EcsManager::addEntity(new Entity("Background"))
		->addComponent(new BubbleDrawer(window->renderer))
		->transform
		->apply({RenderWindow::SCREEN_HEIGHT, 0, 0}, {RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT}, {0.5f, 0.5f}, -3.8, RenderIndexes::Menu::BACKGROUND);

	backButton = EcsManager::addEntity(new Entity("Back-Button"))
		->addComponent(new SpriteRenderer("res/menuarrow.png", window->renderer))
		->addComponent(new Button(nullptr, [this] { this->back(); }))
		->transform
		->apply({40, 0, 40}, {50, 50}, {0.5f, 0.5f}, 180.0f, RenderIndexes::Menu::UI);
}

LobbyPane::~LobbyPane()
{
	delete versus;
	delete matchCodeButton;
	delete background;
	delete backButton;
}

void LobbyPane::onEvent(SDL_Event event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			this->back();
			break;
		}
	}
}

void LobbyPane::back()
{
	EcsManager::clear();
	Pane *pane = new HomePane(window);
	GameManager::switchScene(this, pane);
}