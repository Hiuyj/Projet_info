#include "constantes.h"

struct Image
{
    SDL_Rect recta;
    SDL_Point pos;
    SDL_Texture *text;
};
typedef struct Image Image;

struct Context
{
    SDL_Window* window;
    SDL_Renderer* render;
    int open;
};
typedef struct Context Context;

#endif // STRUCTURES_H_INCLUDED

