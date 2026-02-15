#include "index.h"
#include "../fontmanager.h"
#include "../components/cursor.h"
#include "../components/nineslice.h"
#include "../components/onstart.h"

void setPlaceholder(TextRenderer *textRenderer, const char* text, const char* placeholder)
{
	if (placeholder != nullptr && strlen(text) == 0) {
		textRenderer->setText(placeholder);
		textRenderer->setColor({128, 138, 168});
	}
}

Preset Presets::textinput(SDL_Renderer *renderer, char* text, const size_t max_length, const char* placeholder, const int ptSize)
{
	return [=](Entity *target)
	{
		const auto textRenderer = new TextRenderer(renderer, text, ptSize, {64, 64, 64});

		target->addComponent(new TextInput(text, max_length, [=](const char *newText) {
			textRenderer->setText(newText);
			textRenderer->setColor({64, 64, 64});
			setPlaceholder(textRenderer, text, placeholder);
		}));

		target->addComponent(new OnStart([=]
		{
			setPlaceholder(textRenderer, text, placeholder);
		}));

		target->addComponent(new NineSlice("res/textinput.png", { 32, 32, 48, 32 }, renderer));

		target->addChild((new Entity("Text"))
			->transform
			->apply({-120, 0, -10}, {0, 0}, {0.0f, 0.5f}, 0.0f, 0)
			->addComponent(textRenderer));

		target->addChild((new Entity("Cursor"))
			->transform
			->apply({0, 0, -10}, {5, FontManager::DEFAULT}, {0.0f, 0.5f}, 0.0f, 0)
			->addComponent(new Cursor(ptSize))
			->addComponent(new SpriteRenderer("res/cursor.png", renderer)));
	};
}

Preset Presets::readonlyTextinput(SDL_Renderer *renderer, const char* text, int ptSize)
{
	return [=](Entity *target)
	{
		target
			->addComponent(new NineSlice("res/textinput.png", { 32, 32, 48, 32 }, renderer))

			->addChild((new Entity("Text"))
				->transform
				->apply({-120, 0, -10}, {0, 0}, {0.0f, 0.5f}, 0.0f, 0)
				->addComponent(new TextRenderer(renderer, text, ptSize, {64, 64, 64})));
	};
}