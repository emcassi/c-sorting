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

            bubbleSort();
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
            .x = (BAR_WIDTH + 2) * i + RECT_X_OFFSET, 
            .y = RECT_MAX_HEIGHT - height + RECT_Y_OFFSET, 
            .w = BAR_WIDTH, 
            .h = height
        };
        rects[i].rect = rect;
        rects[i].color = orange;
    }
}

void drawRects(){

    for(int i = 0; i < NUM_SIZE; i++){
        SDL_SetRenderDrawColor(renderer, rects[i].color.r, rects[i].color.g, rects[i].color.b, rects[i].color.a);
        SDL_RenderDrawRect(renderer, &rects[i].rect);
        // SDL_FillRect(surface, &rects[i].rect, SDLColorToUint32(rects[i].color));
        SDL_RenderFillRect(render, &rects[i].rect);
    }
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
}

void render(){
    SDL_RenderClear(renderer);

    drawRects();

    SDL_RenderPresent(renderer);
}

void update(double deltaTime){
    bubbleSort();
}
 int i = 0, j = 0;

void bubbleSort(){
    if(i < NUM_SIZE - 1) {
        if(j < NUM_SIZE - i - 1){

            rects[j].color = green;
            rects[j+1].color = purple;

            if(j > 0){
                rects[j-1].color = orange;
            }

            if(rects[j].rect.h > rects[j + 1].rect.h){
                struct Bar temp = rects[j];

                rects[j].rect.h = rects[j + 1].rect.h;
                rects[j + 1].rect.h = temp.rect.h;

                rects[j].rect.y = rects[j + 1].rect.y;
                rects[j + 1].rect.y = temp.rect.y;

                rects[j].color = rects[j + 1].color;
                rects[j + 1].color = temp.color;
            }

            SDL_Delay(20);
            j++;
        } else {
            i++;
            j = 0;
        }
    }

}

void discoBars(){
    if(i < NUM_SIZE){
        rects[i].color = getRandomColor();
        i++;
    } else {
        i = 0;
    }
}

double getDeltaTime(){
    lastTime = currentTime;
    currentTime = SDL_GetPerformanceCounter();
    return (double)((currentTime - lastTime)*1000 / (double)SDL_GetPerformanceFrequency() );
}

SDL_Color getRandomColor(){
    SDL_Color color;
    color.r = rand() % 255;
    color.g = rand() % 255;
    color.b = rand() % 255;
    color.a = rand() % 255;
    return color;
}

Uint32 SDLColorToUint32(SDL_Color color){
    return (Uint32)((color.r << 16) + (color.g << 8) + (color.b << 0));
}
