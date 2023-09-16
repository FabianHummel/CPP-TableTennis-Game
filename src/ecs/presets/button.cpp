#include "index.h"

Preset Presets::button(SDL_Renderer *renderer, const std::function<void()> &onClick)
{
	return [=](Entity *target) {
		NineSlice *normal = new NineSlice("res/button.png", { 32, 32, 48, 32 }, renderer);
		NineSlice *hover = new NineSlice("res/buttonhover.png", { 32, 32, 40, 32 }, renderer);
		hover->visible = false;

		std::function<void()> onMouseEnter = [=]() {
			normal->visible = false;
			hover->visible = true;
			target->transform->mvByZ(4);
			target->transform->mvByScaleY(-8);
		};

		std::function<void()> onMouseExit = [=]() {
			normal->visible = true;
			hover->visible = false;
			target->transform->mvByZ(-4);
			target->transform->mvByScaleY(8);
		};

		target
			->addComponent(new Button(nullptr, onClick, onMouseEnter, onMouseExit))
			->addComponent(normal)
			->addComponent(hover)
			->addChild((new Entity("Settings.Text"))
				->addComponent(new TextRenderer(renderer, "Settings", {255, 255, 255}))
				->transform
				->apply({0, 0, -10}, {0, 0}, {0.5f, 0.5f}, 0.0f, 0));
	};
}