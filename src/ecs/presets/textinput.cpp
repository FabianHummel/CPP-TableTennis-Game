#include "index.h"

Preset Presets::textinput(SDL_Renderer *renderer, char* text, int ptSize, size_t max_length)
{
	return [=](Entity *target) {
		TextRenderer *textRenderer = new TextRenderer(renderer, text, ptSize, {64, 64, 64});

		target
			->addComponent(new TextInput(text, max_length, [=](char* text) {
				textRenderer->setText(text);
			}))
			->addComponent(new NineSlice("res/textinput.png", { 32, 32, 48, 32 }, renderer))
			->addChild((new Entity("Textinput.Text"))
			   ->addComponent(textRenderer)
			   ->transform
			   ->apply({0, 0, -10}, {0, 0}, {0.5f, 0.5f}, 0.0f, 0));
	};
}