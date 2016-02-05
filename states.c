#include "constantes.h"
#include "fonction.h"
#include "structures.h"

int actualState = -1;

int STATES_getState()
{
    return actualState;
}

void STATES_handleEvent(SDL_Event event, Context* context)
{
    switch (actualState)
    {
        /*case STATE_MENU: MENU_handleEvent(event,context); break;
        case STATE_GAME: GAME_handleEvent(event,context); break;
        case STATE_ALGO_1: ALGO1_handleEvent(event,context); break;
        case STATE_ALGO_2: ALGO2_handleEvent(event,context); break;
        default: break;*/
    }
}

void STATES_update()
{
    switch (actualState)
    {
        /*case STATE_MENU: MENU_update(); break;
        case STATE_GAME: GAME_update(); break;
        case STATE_ALGO_1: ALGO1_update(); break;
        case STATE_ALGO_2: ALGO2_update(); break;
        default: break;*/
    }
}

void STATES_render(SDL_Renderer* renderer)
{
    switch (actualState)
    {
        /*
        case STATE_MENU: MENU_render(renderer); break;
        case STATE_GAME: GAME_render(renderer); break;
        case STATE_ALGO_1: ALGO1_render(renderer); break;
        case STATE_ALGO_2: ALGO2_render(renderer); break;
        default: break;
        */
    }
}

int STATES_switch(int newState, Context* context)
{
    int success = 1;

    switch (actualState)
    {
        /*
        case STATE_MENU: MENU_destroy(); break;
        case STATE_GAME: GAME_destroy(); break;
        case STATE_ALGO_1: ALGO1_destroy(); break;
        case STATE_ALGO_2: ALGO2_destroy(); break;
        default: break;*/
    }

    switch (newState)
    {
            /*
        case STATE_MENU:
            {
                Image menu;
                menu=bo_img(context->render,"menu.bmp",0,0);
                afficher(context->render, menu);
            }
            break;
            /*
        case STATE_GAME: success = GAME_create(context->renderer); break;
        case STATE_ALGO_1: success = ALGO1_create(context->renderer); break;
        case STATE_ALGO_2: success = ALGO2_create(context->renderer); break;*/
        default: success = 0; break;
    }

    if (success == 0)
    {
        context->open = 0;
    }
    else
    {
        actualState = newState;
    }

    return success;
}
