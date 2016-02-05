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

void charger( int lab[][nb_blc_ht])
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

Image bo_img ( SDL_Renderer *ren, char path[], int x,int y )
{
    SDL_Surface *surf=NULL;
    Image img;

    surf=SDL_LoadBMP( path );
    if (surf==NULL)
    {
        printf(" Erreur de chargement de l'image\n");
    }

    img.text=SDL_CreateTextureFromSurface( ren, surf );

    if(img.text==NULL)
    {
        printf(" Erreur dans la fonction afficher \n");
    }

//  img.recta.h = surf.h;
//  img.recta.w=surf.w;
    img.recta.y=y;
    img.recta.x=x;

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
    //SDL_RenderClear(ren);
    SDL_RenderCopy(ren,img.text, img.recta.x, img.recta.y);
    //SDL_RenderPresent(ren);
}



void affiche_lab( int lab[][nb_blc_ht], SDL_Renderer *ren )
{
    int i=0,j=0;

    Image niv[nb_blc_ht][nb_blc_lg];

    charger(lab);

    for(i=0;i<nb_blc_ht;i++)
    {
        for(j=0;j<nb_blc_lg;j++)
        {
            switch(lab[i][j])
            {
            case MUR:
                {
                    niv[i][j]=bo_img(ren, "mur.bmp", (i*tle_blc), (j*tle_blc) );
                }
                break;
            case VIDE:
                {
                    niv[i][j]=bo_img(ren, "vide.bmp", (i*tle_blc), (j*tle_blc) );
                }
                break;
            default:
                {
                    ;
                }
            }

        }
    }

    SDL_RenderClear(ren);
  for(i=0;i<nb_blc_ht;i++)
    {
        for(j=0;j<nb_blc_lg;j++)
        {
            afficher( ren, niv[i][j]);
        }
    }

    SDL_RenderPresent(ren);

}
