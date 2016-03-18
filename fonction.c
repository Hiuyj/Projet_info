#include "structures.h"


void error(const char* msg)
{
    printf("Error : %s\n");
}

void errorSDL(const char* msg)
{
    printf("Error : %s : %s\n", msg, SDL_GetError());
}

Context* createContext(const char* title, int sizeX, int sizeY)
{
    Context* context = NULL;
    context = malloc(sizeof(Context));
    if (context == NULL)
    {
        error("Mauvaise alloc");
        return NULL;
    }

    context->window = NULL;
    context->render = NULL;
    context->open = 0;

    context->window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,sizeX,sizeY,SDL_WINDOW_SHOWN);
    if (context->window == NULL)
    {
        errorSDL("Window");
        return NULL;
    }
    else
    {
        context->open = 1;
    }

    context->render = SDL_CreateRenderer(context->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (context->render == NULL)
    {
        errorSDL("Renderer");
        return NULL;
    }

    return context;
}

void destroyContext(Context* context)
{
    if (context != NULL)
    {
        SDL_DestroyRenderer(context->render);
        SDL_DestroyWindow(context->window);
        context->open = 0;
    }
    free(context);
}

/*void afficher_tab ( int lab[][nb_blc_lg] )
{
    Image sprites[nb_blc_ht][nb_blc_lg];
    charger(lab);
}*/

void charger( int lab[][nb_blc_lg])
{
    FILE* fich=NULL;
    int i=0, j=0;

    fich = fopen("niveau.txt", "r");

    if(fich!=NULL)
    {
        for(i=0;i<nb_blc_ht;i++)
        {
            for(j=0;j<nb_blc_lg;j++)
            {
                fscanf(fich, "%d", &lab[i][j]);
                printf("%d ",lab[i][j]);
            }
            printf("\n");
        }
        fclose(fich);
    }
    else
    {
        printf("\n Erreur lors de l'ouverture du fichier.\n");
    }

}

Image bo_img ( SDL_Renderer *ren, char path[], int x,int y ,int h,int w)
{
    SDL_Surface *surf=NULL;
    Image img;

    surf=SDL_LoadBMP(path);
    if (surf==NULL)
    {
        printf(" Erreur de chargement de l'image\n");
    }

    img.recta.h=h;
    img.recta.w=w;
    img.recta.y=y;
    img.recta.x=x;

    img.text=SDL_CreateTextureFromSurface( ren, surf);

    if(img.text==NULL)
    {
        printf(" Erreur dans la fonction afficher \n");
    }

    SDL_FreeSurface(surf);
    return img;
}

void pause()
{
    SDL_Event event ;
    int boo=1 ;

    while(boo)
        {
        SDL_WaitEvent(&event);

        if(event.window.event == SDL_WINDOWEVENT_CLOSE)
            boo=0;
        }
}


void afficher(SDL_Renderer *ren, Image img)
{
    SDL_RenderCopy( ren, img.text, NULL, &img.recta);
}



void affiche_lab( int lab[][nb_blc_lg], SDL_Renderer *ren )
{
    int i=0,j=0, d=0;

    srand(time(NULL));

    Image niv[nb_blc_ht][nb_blc_lg];

    //Affecter les images correspondantes aux chiffres du tableau
    for(i=0;i<nb_blc_ht;i++)
    {
        for(j=0;j<nb_blc_lg;j++)
        {
            switch(lab[i][j])
            {
            case MUR:
                {
                    d=rand()%25;
                    if(d==1)
                    {
                        niv[i][j]=bo_img(ren, "fromage2.bmp", (j*tle_blc), (i*tle_blc), tle_blc, tle_blc );
                    }
                    else
                    {
                        niv[i][j]=bo_img(ren, "mur.bmp", (j*tle_blc), (i*tle_blc), tle_blc, tle_blc );
                    }
                }
                break;
            case VIDE:
                {
                    niv[i][j]=bo_img(ren, "vide2.bmp", (j*tle_blc), (i*tle_blc), tle_blc, tle_blc );
                }
                break;
            case 6:
                {
                    niv[i][j]=bo_img(ren, "vide2.bmp", (j*tle_blc), (i*tle_blc), tle_blc, tle_blc );
                }
                break;
            case SOURIS:
                {
                    niv[i][j]=bo_img(ren, "souris.bmp", (j*tle_blc), (i*tle_blc), tle_blc, tle_blc );
                }
                break;
            case SOURIS_GAUCHE:
                {
                    niv[i][j]=bo_img(ren, "sourisg.bmp", (j*tle_blc), (i*tle_blc), tle_blc, tle_blc );
                }
                break;
            case OBJECTIF:
                {
                    niv[i][j]=bo_img(ren, "fromage.bmp", (j*tle_blc), (i*tle_blc), tle_blc, tle_blc );
                }
                break;
            default:
                {
                    ;
                }
            }

        }
    }

    //Affichage du labyrinthe

  for(i=0;i<nb_blc_ht;i++)
    {
        for(j=0;j<nb_blc_lg;j++)
        {
            afficher( ren, niv[i][j]);
        }
    }

    SDL_RenderPresent(ren);

}

void deplacer_haut( int lab[][nb_blc_lg], int i, int j, Image* mouse )
{
    if(i>0)
    {
        lab[i-1][j]=lab[i][j];
        lab[i][j]=VIDE;
        mouse->recta.y=mouse->recta.y-14;
    }
}

void deplacer_bas( int lab[][nb_blc_lg], int i, int j, Image* mouse )
{
    if(i<nb_blc_ht-1)
    {
        lab[i+1][j]=lab[i][j];
        lab[i][j]=VIDE;
        mouse->recta.y=mouse->recta.y+14;
    }
}

void deplacer_gauche( int lab[][nb_blc_lg], int i, int j, Image* mouse )
{
    if(j>0)
    {
        lab[i][j]=SOURIS_GAUCHE;
        lab[i][j-1]=lab[i][j];
        lab[i][j]=VIDE;
        mouse->recta.x=mouse->recta.x-14;
    }
}

void deplacer_droite( int lab[][nb_blc_lg], int i, int j, Image* mouse )
{
    if(j<nb_blc_lg-1)
    {
        lab[i][j]=SOURIS;
        lab[i][j+1]=lab[i][j];
        lab[i][j]=VIDE;
        mouse->recta.x=mouse->recta.x+14;
    }
}


void reperer( int lab[][nb_blc_lg], int* x, int* y, int o, Image* mouse)
{
    int i=0, j=0;

    for(i=0;i<nb_blc_ht;i++)
    {
        for(j=0;j<nb_blc_lg;j++)
        {
            if( lab[i][j]==o )
            {
                *x = i;
                *y = j;
            }

            if( o==SOURIS )
            {
                if( lab[i][j]==o || lab[i][j]==SOURIS_GAUCHE )
                {
                    mouse->recta.x=i;
                    mouse->recta.y=j;
                    *x = i;
                    *y = j;
                }
            }
        }
    }
}


void test ( int lab[][nb_blc_lg], int i, int j )
{
    int done=0;

    printf("\n On teste la case %d %d\n", i, j);

    //printf("oui");

    if( lab[i][j]==SOURIS )//si on se trouve sur l'objectif
    {
        printf("\n OBJECTIF TROUVE !!! \n");
        return ;
    }

    if( i>0 && lab[i-1][j]==SOURIS )//Si au dessus il y a un objectif
    {
        printf("\n OBJECTIF TROUVE !!! \n");
        return ;
    }

    if( j<nb_blc_lg-1 && lab[i][j+1]==SOURIS )// si a droite il y a un objectif
    {
        printf("\n OBJECTIF TROUVE !!! \n");
        return ;
    }

    if( i<nb_blc_ht-1 && lab[i+1][j]==SOURIS )// si en dessous il y a un objectif
    {
        printf("\n OBJECTIF TROUVE !!! \n");
        return ;
    }

    if( j>0 && lab[i][j-1]==SOURIS ) //si à gauche il y a un objectif
    {
        printf("\n OBJECTIF TROUVE !!! \n");
        return ;
    }

    //sinon

    if( lab[i-1][j]==0 && i>0 )// on teste si on peut passer par le haut
    {
        printf("H");
        lab[i-1][j]=6;
        test( lab, i-1, j);
    }

    if( lab[i][j+1]==0 && j<nb_blc_lg-1 )// on teste si on peut passer par la droite
    {
        printf("D");
        lab[i][j+1]=6;
        test( lab, i, j+1);
    }

    if( lab[i+1][j]==0 && i<nb_blc_ht-1 )// on teste si on peut passer par le bas
    {
        printf("B");
        lab[i+1][j]=6;
        test( lab, i+1, j);
    }

    if( lab[i][j-1]==0 && j>0 )// on teste si on peut passer par la gauche
    {
        printf("G");
        lab[i][j-1]=6;
        test( lab, i, j-1);
    }


   /* if( done==0 )
    {
        printf("\n Il n'y a pas de solutions, on est foutu!!!\n");
    }*/

}

void deplacer_souris( int lab[][nb_blc_lg], int i, int j, Image* mouse )
{
    if( lab[i-1][j]==6 )//par le haut
    {
        deplacer_haut( lab, i, j, mouse);
    }
    else
    {
        if( lab[i][j+1]==6 )//par la droite
        {
            deplacer_droite( lab, i, j, mouse);
        }
        else
        {
            if( lab[i+1][j]==6 )//par le bas
            {
                deplacer_bas( lab , i, j, mouse);
            }
            else
            {
                if( lab[i][j-1]==6 )// par la gauche
                {
                    deplacer_gauche( lab, i, j, mouse);
                }
            }
        }
    }
}

/*
void deplacer_souris( lab[][nb_blc_lg] )
{

}*/

/*
int new_test( int lab[][nb_blc_lg], int i, int j)
{
    int done=0;

    switch( lab[i][j] )
    {
    case OBJECTIF:
        {
            printf("\n OBJECTIF TROUVE !!! \n");
            done=1;
        }
        break;
    case VIDE:
        {
            lab[i][j]=6;
            done=new_test( lab, i-1 ,j );// on teste si on peut passer par le haut
            if( !done )
            {
                done=new_test( lab, i, j+1 );// on teste si on peut passer par la droite
                if( !done )
                {
                    done=new_test( lab, i+1, j );// on teste si on peut passer par le bas
                    if( !done )
                    {
                        done=new_test( lab, i, j-1 );// on teste si on peut passer par la gauche
                        if (!done )
                        {
                            printf("\n Il y a pas de solutions on est foutu !!!! \n");
                        }
                    }
                }
            }
        }
        break;
    default:
        {
            done=0;
        }
        break;
    }

    return  done;

}*/


