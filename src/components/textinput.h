#pragma once

#include "textrenderer.h"
#include "../componentsystem.h"

class TextInput : public Component
{
private:
	Transform *transform{};
	std::function<void(char*text)> onInputChanged;
	size_t max_length;

public:
	char *text;
  	bool isFocused{};

	TextInput(char *text, size_t max_length, const std::function<void(char *text)> &onInputChanged);

	void onInitialize() override;
	void onUpdate(double deltaTime) override;
	void onEvent(const SDL_Event *event) override;
};