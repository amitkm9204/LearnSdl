
#include<SDL2/SDL.h>
#include<stdio.h>

typedef struct
{

    int x,y;
    short life;
    char *name;
}Man;
void do_render(SDL_Renderer *renderer,Man *man)
{
     SDL_SetRenderDrawColor(renderer,0,0,255,255);

    //clear the screen (to blue)
    SDL_RenderClear(renderer);

    //set the drawing color to white...
    SDL_SetRenderDrawColor(renderer,255,255,255,255);

    SDL_Rect rect = {man->x,man->y,20,20};
    SDL_RenderFillRect(renderer,&rect);

    //We are done drawing "present" or slow
    SDL_RenderPresent(renderer);
}
int eventProcess(SDL_Window *window,Man *man)
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
                case SDLK_RIGHT:
                    man->x+=10;
                    break;
                case SDLK_LEFT:
                    man->x -= 10;
                    break;
                case SDLK_DOWN:
                    man->y+=10;
                    break;
                case SDLK_UP:
                    man->y-=10;
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
    /*const Unit8 *state =  SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_RETURN])
    {
        printf("<RETURN> is pressed .\n");
    }*/
     return done;
}
int main(int argc,char *argv[])
{

    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Init(SDL_INIT_VIDEO);


    Man man;
    man.x = 220;
    man.y = 140;


window = SDL_CreateWindow("Test Demo",100,100,640,480,0);
/*renderer = SDL_CreateRewnderer(window,-1,SDL_RENDERER_ACCELERATED);*/
renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);


// The window is open : enter program loop(see SDL_PollEvent)
int done = 0;

 // Event loop
 while(!done)
 {

    done = eventProcess(window,&man);
     //check for events

    do_render(renderer,&man);

    //wait a few seconds before quiting
    SDL_Delay(10);
 }

// close and destroy the window
SDL_DestroyWindow(window);
SDL_DestroyRenderer(renderer);
return 0;
}
