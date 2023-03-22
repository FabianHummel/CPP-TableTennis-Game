#include <SDL_ttf.h>

class FontManager
{
   public:
      static void init();
      static void close();
      static TTF_Font *main;
};
