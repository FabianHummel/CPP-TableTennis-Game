#include "lobby.h"

#include "../presets/index.h"
#include "../ecsmanager.h"
#include "../gamemanager.h"
#include "../netmanager.h"
#include "../fontmanager.h"
#include "../utility/renderindexes.h"
#include "../shared/packets.h"
#include "home.h"

LobbyPane::LobbyPane(RenderWindow *window, const std::string &match_code, const std::string &player_name) : Pane(window)
{
	this->matchCode = match_code;
	this->playerName = player_name;

	NetManager::on_punch_fail = [] {
		// Display error
	};

	NetManager::on_punched = [this](ENetPeer *enemy) {
		this->enemy = enemy;

		TextRenderer *pTextRenderer = versus->getChild("Opponent")->getComponent<TextRenderer>();
		pTextRenderer->setText("Enemy");

		Buffer b(128);
		b.Write(PEER_ENEMY_DATA);
		b.Write(playerName);
		ENetPacket *packet = enet_packet_create(b.GetBuffer(), b.GetSize(), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(enemy, 0, packet);
	};

	NetManager::on_peer_ping = [](const double rtt) {
		printf("\rRound trip time: %f", rtt);
		fflush(stdout);
	};

	NetManager::on_enemy_data_received = [this](const std::string &enemyName) {
		this->enemyName = enemyName;
		TextRenderer *pTextRenderer = versus->getChild("Opponent")->getComponent<TextRenderer>();
		pTextRenderer->setText(this->enemyName.c_str());
	};

	versus = EcsManager::addEntity(new Entity("Versus"))
		->addComponent(new SpriteRenderer("res/versus.png", window->renderer))
	    ->addComponent(new MenuTitle())
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 230}, {700, 348}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::TITLE)
		->addChild((new Entity("Opponent"))
			->transform
			->apply({-120, 0, 0}, {0, 0}, {0.0f, 0.0f}, 0.0f, 0)
			->addComponent(new TextRenderer(window->renderer, "Waiting...", FontManager::BIG, {64, 64, 64})));

	matchCodeButton = EcsManager::addEntity(new Entity("Invite-Code"))
		->usePreset(Presets::button(window->renderer, matchCode.c_str(), FontManager::BIG, [this] {
			SDL_SetClipboardText(this->matchCode.c_str());
		}))
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