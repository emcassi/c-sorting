#include <stdio.h>
#include "../include/csorting.h"
#include <time.h>

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
                            case SDLK_SPACE:
                                if(sorting)
                                    sorting = 0;
                                else
                                    sorting = 1;
                                break;
                            case SDLK_UP:
                                sortDelay += sortDelayIncrement;
                                if(sortDelay > maxSortDelay)
                                    sortDelay = maxSortDelay;
                                break;
                            case SDLK_DOWN:
                                sortDelay -= sortDelayIncrement;
                                if(sortDelay <= 0)
                                    sortDelay = 0;
                                break;
                        }
                        break;
                }
            }

            printf("Current Delay: %d. Press UP or DOWN to change sorting speed\n", sortDelay);

            if(sorting) {
                bubbleSort();
            }else if(finalizing) {
                finishSort();
            } else {
                discoBars();
            }

            render();
        }

    }

    stop();    

    return 0;
}

int initSDL(){
    int success = 1;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize SDL: %s\n", SDL_GetError());
        success = 0;
    } else {
        window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED,
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
        rects[i].color = white;
    }
}

void drawRects(){

    for(int i = 0; i < NUM_SIZE; i++){
        SDL_SetRenderDrawColor(renderer, rects[i].color.r, rects[i].color.g, rects[i].color.b, rects[i].color.a);
        SDL_RenderDrawRect(renderer, &rects[i].rect);
        // SDL_FillRect(surface, &rects[i].rect, SDLColorToUint32(rects[i].color));
        SDL_RenderFillRect(render, &rects[i].rect);
    }
    SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
}

void render(){
    SDL_RenderClear(renderer);

    drawRects();

    SDL_RenderPresent(renderer);
}

void update(double deltaTime){
    bubbleSort();
}

void stop(){
    if(window != NULL)
        SDL_DestroyWindow(window);
    SDL_Quit();
}


int i = 0, j = 0;
struct Bar* lastCompared = NULL;

void bubbleSort(){

    if(i < NUM_SIZE - 1) {
        if(j < NUM_SIZE - i - 1){
            if(lastCompared != NULL){
                lastCompared->color = white;
            }
            rects[j].color = orange;
            rects[j + 1].color = purple;

            if(rects[j].rect.h > rects[j + 1].rect.h){
                struct Bar temp = rects[j];

                rects[j].rect.h = rects[j + 1].rect.h;
                rects[j + 1].rect.h = temp.rect.h;

                rects[j].rect.y = rects[j + 1].rect.y;
                rects[j + 1].rect.y = temp.rect.y;

                rects[j].color = rects[j + 1].color;
                rects[j + 1].color = temp.color;
            }

            lastCompared = &rects[j];

            SDL_Delay(sortDelay);
            j++;
        } else {
            i++;
            j = 0;
        }
    } else {
        i = 0;
        sorting = FALSE;
        finalizing = TRUE;
    }

}

void finishSort(){
    if(i < NUM_SIZE){
        rects[i].color = green;
        SDL_Delay(10);
        i++;
    } else {
        finalizing = FALSE;
    }
}

// Just a fun method to change the colors
void discoBars(){
    if(i < NUM_SIZE){
        rects[i].color = getRandomColor();
        i++;
    } else {
        i = 0;
    }
    SDL_Delay(2);
}


SDL_Color getRandomColor(){
    SDL_Color color;
    color.r = rand() % 255;
    color.g = rand() % 255;
    color.b = rand() % 255;
    color.a = rand() % 255;
    return color;
}
