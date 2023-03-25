#include "bar.h"

// Macros

#define TITLE "C Sorting"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define NUM_SIZE 175
#define BAR_WIDTH 5
#define RECT_X_OFFSET 10
#define RECT_Y_OFFSET 100 
#define RECT_MAX_HEIGHT 500

#define FALSE 0
#define TRUE 1

// SDL Graphics
SDL_Window* window = NULL;
SDL_Surface* surface = NULL;
SDL_Renderer* renderer = NULL;

// The rects we'll put in order
struct Bar rects[NUM_SIZE];

// Colors
SDL_Color black = { .r = 0, .g = 0, .b = 0, .a = 255 };
SDL_Color white = { .r = 255, .g = 255, .b = 255, .a = 255 };
SDL_Color orange = { .r = 255, .g = 153, .b = 146, .a = 255 };
SDL_Color green = { .r = 0, .g = 255, .b = 100, .a = 255 };
SDL_Color purple = { .r = 163, .g = 48, .b = 255, .a = 255 };

// Sorting
int sorting = TRUE;
int finalizing = FALSE;

int sortDelay = 0;
int maxSortDelay = 350;
int sortDelayIncrement = 5;

void render();
void stop();

int initSDL();
void initArray();
void drawRects();
double getDeltaTime();

SDL_Color getRandomColor();

// Sorting Methods
void startSort();
void bubbleSort();
void bs();
void finishSort();

// Just a fun method that cycles through the bars changing colors
void discoBars();