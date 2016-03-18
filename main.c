#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include "constantes.h"
#include "fonction.h"
#include "states.h"

int main(int argc, char** argv)
{
    SDL_Event event;
    int niveau[nb_blc_ht][nb_blc_lg];
    int open=1, i=0, j=0, play=0;
    int startMoveMouse = 0;
    int fps = 0;
    Coordonees position_souris, position_fromage;

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


    Image menu, mouse;
    menu=bo_img( ren, "menu.bmp", 0, 0, ht_fnt, lg_fnt);
    mouse=bo_img( ren, "souris.bmp", 0, 0, tle_blc, tle_blc);

    SDL_RenderClear(ren);
    afficher(ren, menu);
    SDL_RenderPresent(ren);

    while(open)
    {
        while(SDL_PollEvent(&event))
        {

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
                            charger(niveau);//Pour charger un niveau
                            affiche_lab( niveau, ren);

                            reperer( niveau, &position_souris.x, &position_souris.y, SOURIS, &mouse);
                            printf("\n %d et %d .\n", position_souris.x, position_souris.y);

                        }
                        break;
                        case SDL_SCANCODE_KP_5:
                        {
                            reperer( niveau, &position_fromage.x, &position_fromage.y, OBJECTIF, &mouse);//On repere le fromage

                            test( niveau, position_fromage.x, position_fromage.y);

                            startMoveMouse = (startMoveMouse == 1) ? 0:1;
                            /*
                            printf("\n\n");
                            for(i=0;i<nb_blc_ht;i++)
                            {
                                for(j=0;j<nb_blc_lg;j++)
                                {
                                    printf("%d ", niveau[i][j]);
                                }
                                printf("\n");
                            }*/

                            affiche_lab( niveau, ren);
                        }
                        break;
                        case SDL_SCANCODE_KP_6 :
                        {
                            play=(play==1)?0:1;
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

        /* Update */

        SDL_Delay(17); // Pause 17 millisec ~ 60 FPS

        fps++;
        if (fps >= 15)
        {
            if (play)
            {
                reperer( niveau, &position_fromage.x, &position_fromage.y, OBJECTIF, &mouse);//On repere le fromage

                test( niveau, position_fromage.x, position_fromage.y);

                reperer( niveau, &position_souris.x, &position_souris.y, SOURIS, &mouse);//On repère la souris

                printf("\n Oui\n");
                deplacer_souris(niveau, position_souris.x, position_souris.y, &mouse);


                /*afficher(ren, mouse);
                SDL_RenderPresent(ren);*/

                affiche_lab( niveau, ren);

                //Reinitialisation du tableau
                for(i=0;i<nb_blc_ht;i++)
                {
                    for(j=0;j<nb_blc_lg;j++)
                    {
                        if(niveau[i][j]==6)
                        {
                            niveau[i][j]=0;
                        }
                    }
                    printf("\n");
                }

            }
            fps = 0;
        }



        /* Render */


        //SDL_RenderClear(renderer);

        //afficherFond()

        /*
        if (state == game)
        {
            afficherSouris()
        }
        */



        //SDL_RenderPresent(renderer);

    }


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


