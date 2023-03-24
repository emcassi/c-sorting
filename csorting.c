#include <stdio.h>
#include "csorting.h"

int main(int argc, char ** argv){

    if(initSDL() != 1){
        printf("Initialization failed");
    } else {
        int quit = 0;
        SDL_Event event;

        SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));

        SDL_UpdateWindowSurface(window);
        initArray();

        while (!quit)
        {
            double dt = getDeltaTime();
            
            while(SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_QUIT:
                        quit = 1;
                        break;
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym){
                            case SDLK_ESCAPE:
                                quit = 1;
                                break;
                        }
                        break;
                }
            }

            update(dt);

            render();
        }

        SDL_DestroyWindow(window);
    }
    
    SDL_Quit();

    return 0;
}

int initSDL(){
    int success = 1;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize SDL: %s\n", SDL_GetError());
        success = 0;
    } else {
        window = SDL_CreateWindow("My SDL Window", SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

        if(window == NULL){
            printf("Window could not be created. Error: %s\n", SDL_GetError());
            success = 0;
        } else {
            surface = SDL_GetWindowSurface(window);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        }
    }
    return success;
}

void initArray(){
    srand(time(NULL));

    for(int i = 0; i < NUM_SIZE; i++){

        int height = rand() % RECT_MAX_HEIGHT;
        SDL_Rect rect = { 
            .x = 5 * i + RECT_X_OFFSET, 
            .y = RECT_MAX_HEIGHT - height + RECT_Y_OFFSET, 
            .w = 2, 
            .h = height
        };
        rects[i] = rect;
    }
}

void drawRects(){

    SDL_SetRenderDrawColor(renderer, orange.r, orange.g, orange.b, orange.a);

    for(int i = 0; i < NUM_SIZE; i++){

        SDL_RenderDrawRect(renderer, &rects[i]);
    }
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
}

void render(){
    SDL_RenderClear(renderer);

    drawRects();

    SDL_RenderPresent(renderer);
}

void update(double deltaTime){

}

double getDeltaTime(){
    lastTime = currentTime;
    currentTime = SDL_GetPerformanceCounter();
    return (double)((currentTime - lastTime)*1000 / (double)SDL_GetPerformanceFrequency() );
}