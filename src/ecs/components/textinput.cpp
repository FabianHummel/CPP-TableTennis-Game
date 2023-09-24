#include "textinput.h"
#include "../../cursormanager.h"

TextInput::TextInput(char *text, size_t max_length, const std::function<void(char*text)> &onInputChanged)
{
	this->text = text;
	this->max_length = max_length;
	this->onInputChanged = onInputChanged;
}

void TextInput::onInitialize()
{
	this->transform = parent->transform;
}

void TextInput::onUpdate(double deltaTime)
{
	if (!parent->isVisible()) return;

	int x, y;
	SDL_GetMouseState(&x, &y);
	x *= 2;
	y *= 2;

	if (transform->inTransformBounds(x, y))
		CursorManager::requestCursor(CursorManager::inputCursor);
	else
		CursorManager::requestCursor(CursorManager::arrowCursor);
}

void TextInput::onEvent(SDL_Event event)
{
	if (!parent->isVisible()) return;

	int x, y;
	SDL_GetMouseState(&x, &y);
	x *= 2;
	y *= 2;

	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (transform->inTransformBounds(x, y))
		{
			SDL_StartTextInput();
			this->isFocused = true;
		}
		else
		{
			SDL_StopTextInput();
			this->isFocused = false;
		}
		break;
	case SDL_TEXTINPUT:
		if (this->isFocused && strlen(this->text) < this->max_length)
		{
			static const char* alphanum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			int i = 0;
			while(event.text.text[i]) {
				char ch = (char)toupper(event.text.text[i]);
				if (strchr(alphanum, ch)) {
					strcat(this->text, &ch);
				}
				i++;
			}

			this->onInputChanged(this->text);
		}
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_BACKSPACE)
		{
			if (this->isFocused && strlen(this->text) > 0)
			{
				this->text[strlen(this->text) - 1] = '\0';
			}
			this->onInputChanged(this->text);
		}
	}
}