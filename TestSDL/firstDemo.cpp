
#include<SDL2/SDL.h>
#include<stdio.h>

typedef struct
{

    int x,y;
    short life;
    char *name;
}Man;
typedef struct
{
    Man man;
}GameState;
void do_render(SDL_Renderer *renderer,GameState *game)
{
     SDL_SetRenderDrawColor(renderer,0,0,255,255);

    //clear the screen (to blue)
    SDL_RenderClear(renderer);

    //set the drawing color to white...
    SDL_SetRenderDrawColor(renderer,255,255,255,255);

    SDL_Rect rect = {game->man.x,game->man.y,20,20};
    SDL_RenderFillRect(renderer,&rect);

    //We are done drawing "present" or slow
    SDL_RenderPresent(renderer);
}
int eventProcess(SDL_Window *window,GameState *game)
{
    int done=0;
     SDL_Event event;
    while(SDL_PollEvent(&event))
     {
         switch(event.type)
         {
         case SDL_WINDOWEVENT_CLOSE:
             {
                if(window)
                {
                 SDL_DestroyWindow(window);
                 window = NULL;
                 done = 1;
                }
             }
             break;
         case SDL_KEYDOWN :
            {
                switch(event.key.keysym.sym)
                {
                case SDLK_ESCAPE :
                    done = 1;
                    break;
                }
            }
            break;
        case SDL_QUIT:
            //quit out of the game
            done = 1;
            break;

         }
     }

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if(state[SDL_SCANCODE_LEFT])
    {
        game->man.x -= 10;
    }
    if(state[SDL_SCANCODE_RIGHT])
    {
        game->man.x += 10;
    }
    if(state[SDL_SCANCODE_UP])
    {
        game->man.y -= 10;
    }
    if(state[SDL_SCANCODE_DOWN])
    {
        game->man.y += 10;
    }

     return done;
}
int main(int argc,char *argv[])
{

    GameState gameState;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);


    gameState.man.x = 320-40;
    gameState.man.y = 240-40;


window = SDL_CreateWindow("Test Demo",100,100,640,480,0);
/*renderer = SDL_CreateRewnderer(window,-1,SDL_RENDERER_ACCELERATED);*/
renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);


// The window is open : enter program loop(see SDL_PollEvent)
int done = 0;

 // Event loop
 while(!done)
 {

    done = eventProcess(window,&gameState);
     //check for events

    do_render(renderer,&gameState);

    //wait a few seconds before quiting
    SDL_Delay(10);
 }

// close and destroy the window
SDL_DestroyWindow(window);
SDL_DestroyRenderer(renderer);
return 0;
}
