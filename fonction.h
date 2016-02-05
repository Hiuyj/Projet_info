#include "structures.h"

void errorSDL(const char *msg);

void error( const char *msg);

Context* createContext(const char* title, int sizeX, int sizeY);

void destroyContext( Context* context);

void pause();

Image bo_img ( SDL_Renderer* ren, char path[], int x,int y );

void charger( int lab[][nb_blc_ht]);

void afficher(SDL_Renderer *ren, Image img);

void affiche_lab( int lab[][nb_blc_ht], SDL_Renderer *ren );


//void jeu( int lab[][nb_blc_ht]);

#endif // FONCTION_H_INCLUDED
