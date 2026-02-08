#include "index.h"
#include "../fontmanager.h"
#include "../components/cursor.h"

Preset Presets::textinput(SDL_Renderer *renderer, char* text, int ptSize, size_t max_length)
{
	return [=](Entity *target) {
		TextRenderer *textRenderer = new TextRenderer(renderer, text, ptSize, {64, 64, 64});

		target
			->addComponent(new TextInput(text, max_length, [=](const char *newText) {
				textRenderer->setText(newText);
			}))

			->addComponent(new NineSlice("res/textinput.png", { 32, 32, 48, 32 }, renderer))

			->addChild((new Entity("Text"))
				->transform
				->apply({-120, 0, -10}, {0, 0}, {0.0f, 0.5f}, 0.0f, 0)
				->addComponent(textRenderer))

			->addChild((new Entity("Cursor"))
				->transform
				->apply({0, 0, -10}, {5, FontManager::DEFAULT}, {0.0f, 0.5f}, 0.0f, 0)
				->addComponent(new Cursor(ptSize))
				->addComponent(new SpriteRenderer("res/cursor.png", renderer)));
	};
}
