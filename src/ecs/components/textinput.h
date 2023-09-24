#pragma once

#include "../ecs.h"

class TextInput : public Component
{
private:
	Transform *transform{};
	std::function<void(char*text)> onInputChanged;
	char *text;
	size_t max_length;

public:
  	bool isFocused{};

	TextInput(char *text, size_t max_length, const std::function<void(char*text)> &onInputChanged);

	void onInitialize() override;
	void onUpdate(double deltaTime) override;
	void onEvent(SDL_Event event) override;
};