#include "index.h"
#include "random"
#include "../animationmanager.h"

Preset Presets::button(SDL_Renderer *renderer, const char *text, int ptSize, const std::function<void()> &onClick)
{
	return [=](Entity *target) {
		NineSlice *normal = new NineSlice("res/button.png", { 32, 32, 48, 32 }, renderer);
		NineSlice *hover = new NineSlice("res/buttonhover.png", { 32, 32, 40, 32 }, renderer);
		hover->visible = false;

		std::function onMouseEnter = [=] {
			normal->visible = false;
			hover->visible = true;
			target->transform->mvByZ(4);
			target->transform->mvByScaleY(-8);
			float randomRotation = random() % 6 - 3;

			AnimationManager::play([=](double t) {
				target->animation->setRotation(t * randomRotation);
				target->animation->setScaleX(t * 15);
				target->animation->setScaleY(t * 20);
			}, Easings::easeOutElastic, 0.5);
		};

		std::function onMouseExit = [=] {
			normal->visible = true;
			hover->visible = false;
			target->transform->mvByZ(-4);
			target->transform->mvByScaleY(8);
			float initialRotation = target->animation->getRotation();

			AnimationManager::play([=](double t) {
				target->animation->setRotation((1-t) * initialRotation);
				target->animation->setScaleX((1-t) * 15);
				target->animation->setScaleY((1-t) * 20);
			}, Easings::easeOutElastic, 0.5);
		};

		target
			->addComponent(new Button(nullptr, onClick, onMouseEnter, onMouseExit))
			->addComponent(normal)
			->addComponent(hover)
			->addChild((new Entity("Text"))
				->addComponent(new TextRenderer(renderer, text, ptSize, {255, 255, 255}))
				->transform
				->apply({0, 0, -10}, {0, 0}, {0.5f, 0.5f}, 0.0f, 0));
	};
}