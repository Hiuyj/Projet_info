#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#include "structures.h"

void errorSDL(const char *msg);

void error( const char *msg);

Context* createContext(const char* title, int sizeX, int sizeY);

void destroyContext( Context* context);

void pause();

Image bo_img ( SDL_Renderer *ren, char path[], int x,int y ,int h,int w);

void charger( int lab[][nb_blc_ht]);

void afficher(SDL_Renderer *ren, Image img);

void affiche_lab( int lab[][nb_blc_ht], SDL_Renderer *ren );

void deplacer_haut( int lab[][nb_blc_lg], int i, int j, Image* mouse );

void deplacer_bas( int lab[][nb_blc_lg], int i, int j, Image* mouse);

void deplacer_gauche( int lab[][nb_blc_lg], int i, int j, Image* mouse );

void deplacer_droite( int lab[][nb_blc_lg], int i, int j, Image* mouse );

void reperer( int lab[][nb_blc_lg], int* x, int* y, int o, Image* mouse);

void test ( int lab[][nb_blc_lg], int i, int j );

void deplacer_souris( int lab[][nb_blc_lg], int i, int j, Image* mouse );

//int new_test( int lab[][nb_blc_lg], int i, int j);


//void jeu( int lab[][nb_blc_ht]);

#endif // FONCTION_H_INCLUDED
