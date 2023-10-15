#include "lobby.h"
#include "../ecs/presets/index.h"
#include "../ecsmanager.h"
#include "../gamemanager.h"
#include "../netmanager.h"
#include "../utility/renderindexes.h"
#include "home.h"

LobbyPane::LobbyPane(RenderWindow *window, const char *match_code) : Pane(window)
{
	NetManager::on_punch_fail = [this]() {
		// Display error
	};
	NetManager::on_punched = [this](ENetPeer *enemy) {
		this->enemy = enemy;
	};
	NetManager::on_peer_ping = [this](double rtt) {
		//	printf("Round trip time: %f\n", rtt);
	};

	versus = EcsManager::addEntity(new Entity("Versus"))
		->addComponent(new SpriteRenderer("res/versus.png", window->renderer))
	    ->addComponent(new MenuTitle())
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 200}, {RenderWindow::SCREEN_WIDTH, 314}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::TITLE)
	 	->addChild((new Entity("Versus.Player1"))
	    	->addComponent(new TextRenderer(window->renderer, "You", FontManager::DEFAULT, {255, 255, 255}))
			->transform->apply({-180, 0, 73}, {0, 0}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI))
		->addChild((new Entity("Versus.Player2"))
	        ->addComponent(new TextRenderer(window->renderer, "Enemy", FontManager::DEFAULT, {255, 255, 255}))
			->transform->apply({180, 0, -93}, {0, 0}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI));

	matchCodeButton = EcsManager::addEntity(new Entity("Invite-Code"))
		->usePreset(Presets::button(window->renderer, match_code, FontManager::BIG, [match_code] { SDL_SetClipboardText(match_code); }))
	    ->addComponent(new Button(nullptr, nullptr, [this] {
				matchCodeButton->getChild("Invite-Code.Hint")->visible = true;
			}, [this] {
				matchCodeButton->getChild("Invite-Code.Hint")->visible = false;
			}))
		->transform
	    ->apply({RenderWindow::SCREEN_CENTER_X, 0, 550}, { 370, 150 }, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI)
		->addChild((new Entity("Invite-Code.Hint"))
			->addComponent(new SpriteRenderer("res/copyarrow.png", window->renderer))
			->transform
	        ->apply({-150, 0, 80}, {-370+300, -150+105}, {0.0f, 0.0f}, 0.0f, RenderIndexes::Menu::UI)
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

void LobbyPane::back()
{
	EcsManager::clear();
	Pane *pane = new HomePane(window);
	GameManager::switchScene(this, pane);
}