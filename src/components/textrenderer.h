#include <SDL.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <SDL_events.h>
#include "component.h"
#include "transform.h"

class TextRenderer : public Component
{
	private:
		Transform *transform;
		SDL_Renderer *renderer;
		const char *text;
		SDL_Color color;
		TTF_Font *font;
		SDL_Texture *texture;

		void updateTexture();

	public:
		TextRenderer(SDL_Renderer *renderer, const char *text, SDL_Color color);
		void onInitialize() override;
		void onUpdate(double deltaTime) override;
		
		void setText(const char *text);
		void setColor(SDL_Color color);
};
