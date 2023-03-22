#pragma once

#include "../menu/pane.h"
#include "../entity/entity.h"

class HomePane : public Pane
{
	private:
		Entity *title;
		Entity *background;
		Entity *gamemode;
		Entity *previous;
		Entity *next;

	public:
		HomePane(RenderWindow *window);
		void onStart() override;
		void onGui(double deltaTime) override;
		void dispose() override;

		void previousGameMode() const;
		void nextGameMode() const;
};
