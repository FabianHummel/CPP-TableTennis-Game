#include "lobby.h"
#include "home.h"
#include "../presets/index.h"
#include "../ecsmanager.h"
#include "../errormanager.h"
#include "../gamemanager.h"
#include "../netmanager.h"
#include "../fontmanager.h"
#include "../components/bubbledrawer.h"
#include "../components/button.h"
#include "../components/menutitle.h"
#include "../components/spriterenderer.h"
#include "../utility/renderindexes.h"
#include "../shared/packets.h"
#include "../utility/renderwindow.h"

LobbyPane::LobbyPane(SDL_Renderer *renderer, const std::string &match_code, const std::string &player_name) : Pane(renderer)
{
	this->matchCode = match_code;
	this->playerName = player_name;
	this->isReady = false;
	this->isEnemyReady = false;

	NetManager::on_punch_fail = []
	{
		// Display error
	};

	NetManager::on_punched = [this](ENetPeer *enemy)
	{
		this->enemy = enemy;

		TextRenderer *pTextRenderer = versusEnemyName->getChild("Text")->getComponent<TextRenderer>();
		pTextRenderer->setText("Enemy");

		Buffer b(128);
		b.Write(PEER_ENEMY_DATA);
		b.Write(playerName);
		b.Write(isReady);
		ENetPacket *packet = enet_packet_create(b.GetBuffer(), b.GetSize(), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(enemy, 0, packet);
	};

	NetManager::on_peer_ping = [](const double rtt)
	{
		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "\rRound trip time: %f", rtt);
		fflush(stdout);
	};

	NetManager::on_enemy_data_received = [this](const std::string &enemyName, const bool readyStatus)
	{
		this->enemyName = enemyName;
		this->isEnemyReady = readyStatus;
		TextRenderer *pTextRenderer = versusEnemyName->getChild("Text")->getComponent<TextRenderer>();
		pTextRenderer->setText(this->enemyName.c_str());
		versusEnemyName->getChild("Ready-Image")->getComponent<SpriteRenderer>()->visible = this->isEnemyReady;
	};

	NetManager::on_enemy_ready_status_received = [this](const bool readyStatus)
	{
		this->isEnemyReady = readyStatus;
		versusEnemyName->getChild("Ready-Image")->getComponent<SpriteRenderer>()->visible = this->isEnemyReady;
	};

	versusTitle = EcsManager::addEntity(new Entity("Versus-Title"))
		->addComponent(new SpriteRenderer("res/versus.png", renderer))
		->addComponent(new MenuTitle())
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 160}, {500, 138}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::TITLE);

	versusEnemyName = EcsManager::addEntity(new Entity("Versus-Enemy-Name"))
		->usePreset(Presets::readonlyTextinput(renderer, "Waiting...", FontManager::DEFAULT))
	    ->addComponent(new MenuTitle(0.5))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X + 100, 0, 300}, {300, 100}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI)
		->addChild((new Entity("Ready-Image"))
			->addComponent(new SpriteRenderer("res/ready.png", renderer))
			->transform
			->apply({ 90, 0, -10 }, { 42, 42 }, { 0.5f, 0.5f }, 0.0f, RenderIndexes::Menu::UI));

	matchCodeButton = EcsManager::addEntity(new Entity("Invite-Code"))
		->usePreset(Presets::button(renderer, matchCode.c_str(), FontManager::BIG, [this] {
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
			->addComponent(new SpriteRenderer("res/copyarrow.png", renderer))
			->transform
	        ->apply({-150, 0, 80}, {300, 105}, {0.0f, 0.0f}, 0.0f, RenderIndexes::Menu::UI)
	        ->apply(false));

	background = EcsManager::addEntity(new Entity("Background"))
		->addComponent(new BubbleDrawer(renderer))
		->transform
		->apply({RenderWindow::SCREEN_HEIGHT, 0, 0}, {RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT}, {0.5f, 0.5f}, -3.8, RenderIndexes::Menu::BACKGROUND);

	backButton = EcsManager::addEntity(new Entity("Back-Button"))
		->addComponent(new SpriteRenderer("res/menuarrow.png", renderer))
		->addComponent(new Button(nullptr, [this] { this->back(); }))
		->transform
		->apply({40, 0, 40}, {50, 50}, {0.5f, 0.5f}, 180.0f, RenderIndexes::Menu::UI);

	readyButton = EcsManager::addEntity(new Entity("Ready-Button"))
		->usePreset(Presets::button(renderer, NOT_READY_TEXT, FontManager::DEFAULT, [this]
		{
			this->isReady = !this->isReady;
			readyButton->getChild("Text")->getComponent<TextRenderer>()->setText(this->isReady ? READY_TEXT : NOT_READY_TEXT);
			readyButton->getChild("Ready-Image")->getComponent<SpriteRenderer>()->visible = this->isReady;

			if (enemy == nullptr) return;
			Buffer b(128);
			b.Write(PEER_ENEMY_READY_STATUS);
			b.Write(this->isReady);
			ENetPacket *packet = enet_packet_create(b.GetBuffer(), b.GetSize(), ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(enemy, 0, packet);
		}))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 1000}, { 300, 100 }, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI)
		->addChild((new Entity("Ready-Image"))
			->addComponent(new SpriteRenderer("res/ready.png", renderer))
			->transform
			->apply({ 90, 0, -10 }, { 42, 42 }, { 0.5f, 0.5f }, 0.0f, RenderIndexes::Menu::UI));
}

LobbyPane::~LobbyPane()
{
	delete versusTitle;
	delete versusEnemyName;
	delete matchCodeButton;
	delete background;
	delete backButton;
	delete readyButton;
}

void LobbyPane::onStart()
{
	readyButton->getChild("Ready-Image")->getComponent<SpriteRenderer>()->visible = false;
	versusEnemyName->getChild("Ready-Image")->getComponent<SpriteRenderer>()->visible = false;
}

void LobbyPane::onEvent(const SDL_Event *event)
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

void LobbyPane::onGui(double deltaTime)
{
	ErrorManager::showErrors(renderer);
}

void LobbyPane::back() const
{
	EcsManager::clear();
	Pane *pane = new HomePane(renderer);
	GameManager::switchScene(this, pane);
}
