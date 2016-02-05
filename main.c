#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include "constantes.h"
#include "fonction.h"
#include "states.h"

int main(int argc, char** argv)
{
    SDL_Event event;
    int niveau[nb_blc_ht][nb_blc_lg], open=1;

    SDL_Init(SDL_INIT_EVERYTHING);

    //Initialisation simple
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        errorSDL("Init");
        SDL_Quit();
        return -1;
    }

    // Variables
    Context* mContext = NULL;

    // Chargement Context
   /* mContext = createContext("Labyrinthe",lg_fnt,ht_fnt);
    if (mContext == NULL)
    {
        // error
    }*/

    // Chargement Menu
    //STATES_switch(STATE_MENU,mContext);

    SDL_Renderer *ren=NULL;
    SDL_Window *win=NULL;


    win = SDL_CreateWindow("Labyrinthe",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,lg_fnt,ht_fnt,SDL_WINDOW_SHOWN);

    ren= SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


    Image menu;
    menu=bo_img(ren,"menu.bmp",0,0);

    SDL_RenderClear(ren);
    afficher(ren, menu);
    SDL_RenderPresent(ren);

    while(open)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            {
                open=0;
            }
            break;
        case SDL_KEYDOWN:
            {
                switch( event.key.keysym.scancode )
                {
                case SDL_SCANCODE_KP_1:
                    {
                        affiche_lab( niveau, ren);
                    }
                    break;
                default:
                    {
                        ;
                    }
                }
            }
            break;
        default:
            {
                ;
            }
        }
    }



    pause();
    printf("fin pause\n");



/*
    while (mContext->open == 1)
    {
        // Evenements
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                mContext->open = 0;
            }

            STATES_handleEvent(event,mContext);
        }

        // Mise a jour
        STATES_update();

        // Rendu
        SDL_RenderClear(mContext->render);
        //STATES_render(mContext->render);
        SDL_RenderCopy(mContext->render, menu.text, NULL, NULL);
        SDL_RenderPresent(mContext->render);

        // 60 FPS
        SDL_Delay(20);
    }*/

    // Quitter proprement
    //STATES_switch(-1,mContext);
    //destroyContext(mContext);


    SDL_Quit();

    return 0;
}


