#include "index.h"
#include "../components/button.h"
#include "../animationmanager.h"
#include "../components/nineslice.h"
#include "../components/textrenderer.h"

Preset Presets::button(SDL_Renderer *renderer, const char *text, const int ptSize, const std::function<void()> &onClick)
{
	return [=](Entity *target) {
		const auto normal = new NineSlice("res/button.png", { 32, 32, 48, 32 }, renderer);
		const auto hover = new NineSlice("res/buttonhover.png", { 32, 32, 40, 32 }, renderer);
		hover->visible = false;

		const std::function onMouseEnter = [=] {
			normal->visible = false;
			hover->visible = true;
			target->transform->position.z += 4;
			target->transform->scale.y += -8;
			const float randomRotation = SDL_randf() * 6 - 3;

			AnimationManager::play([=](double t) {
				target->animation->rotation = (float)(t * randomRotation);
				target->animation->scale.x = t * 15;
				target->animation->scale.y = t * 20;
			}, Easings::easeOutElastic, 0.5);
		};

		const std::function onMouseExit = [=] {
			normal->visible = true;
			hover->visible = false;
			target->transform->position.z += -4;
			target->transform->scale.y += 8;
			const float initialRotation = target->animation->rotation;

			AnimationManager::play([=](double t) {
				target->animation->rotation = (float)((1-t) * initialRotation);
				target->animation->scale.x = (1-t) * 15;
				target->animation->scale.y = (1-t) * 20;
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
