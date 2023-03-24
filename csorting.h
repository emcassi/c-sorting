#include <SDL2/SDL.h>

// Macros 

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define NUM_SIZE 250
#define RECT_X_OFFSET 10
#define RECT_Y_OFFSET 100 
#define RECT_MAX_HEIGHT 500

// SDL Graphics
SDL_Window* window = NULL;
SDL_Surface* surface = NULL;
SDL_Renderer* renderer = NULL;

// The rects we'll put in order
SDL_Rect rects[NUM_SIZE];

// Colors
SDL_Color bgColor = { .r = 0, .g = 0, .b = 0, .a = 255 };
SDL_Color orange = { .r = 255, .g = 153, .b = 146, .a = 255 };

// Getting Delta Time
Uint64 currentTime;
Uint64 lastTime = 0;

void update(double deltaTime);
void render();

int initSDL();
void initArray();
void drawRects();
double getDeltaTime();