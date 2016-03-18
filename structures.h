/*Fichier des structures*/
#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
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

struct Graphe
{
    int tab;
    int ok;
};
typedef struct Graphe Graphe;


struct Coordonees
{
    int x;
    int y;
};
typedef struct Coordonees Coordonees;

#endif // STRUCTURES_H_INCLUDED

