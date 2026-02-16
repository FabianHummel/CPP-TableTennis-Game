#include "textinput.h"
#include "../managers/cursormanager.h"
#include "../managers/keyboardmanager.h"

TextInput::TextInput(char *text, const size_t max_length, const std::function<void(char *text)> &on_input_changed)
{
    this->name = "Text Input";
    this->text = text;
    this->max_length = max_length;
    this->on_input_changed = on_input_changed;
}

void TextInput::on_initialize()
{
    this->transform = parent->transform;
}

void TextInput::on_update(double delta_time)
{
    if (!parent->is_visible())
        return;

    float x, y;
    SDL_GetMouseState(&x, &y);
    x *= 2;
    y *= 2;

    if (transform->in_transform_bounds(x, y))
    {
        CursorManager::request_cursor(CursorManager::input_cursor);
    }
    else
    {
        CursorManager::request_cursor(CursorManager::arrow_cursor);
    }
}

void TextInput::on_event(const SDL_Event *event)
{
    if (!parent->is_visible())
        return;

    float x, y;
    SDL_GetMouseState(&x, &y);
    x *= 2;
    y *= 2;

    switch (event->type)
    {
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        this->is_focused = false;
        if (transform->in_transform_bounds(x, y))
        {
            KeyboardManager::is_text_input_requested = true;
            this->is_focused = true;
        }
        break;
    case SDL_EVENT_TEXT_INPUT:
        if (this->is_focused && strlen(this->text) < this->max_length)
        {
            static auto alphanum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            int i = 0;
            while (event->text.text[i])
            {
                char ch = (char)toupper(event->text.text[i]);
                if (strchr(alphanum, ch))
                {
                    strcat(this->text, &ch);
                }
                i++;
            }

            this->on_input_changed(this->text);
        }
        break;
    case SDL_EVENT_KEY_DOWN:
        if (event->key.key == SDLK_BACKSPACE)
        {
            if (this->is_focused && strlen(this->text) > 0)
            {
                this->text[strlen(this->text) - 1] = '\0';
            }
            this->on_input_changed(this->text);
        }
    default:
        break;
    }
}