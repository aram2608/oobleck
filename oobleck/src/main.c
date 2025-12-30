#include "../include/umkaPlugin.h"
#include "../include/gapBuffer.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

void initializeSDL(void) {
    bool ok = SDL_Init(SDL_INIT_VIDEO);

    if (!ok) {
        printf("PANIC: failed to initialize SDL\n");
        exit(1);
    }

    ok = TTF_Init();

    if (!ok) {
        printf("PANIC: failed to initialize SDL TTF\n");
        exit(1);
    }
}

void closeSDL(SDL_Window* window) {
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char** argv) {
    GapBuffer* buff = newBuffer(BUFFER_SIZE);
    Umka* umka = loadUmka("plugin.um", argc, argv);
    umkaRun(umka);

    insertString(buff, "Hello world!");

    printf("Buffer: %s\n", buff->data);

    initializeSDL();

    SDL_Window* window = SDL_CreateWindow("oobleck", 600, 600, SDL_WINDOW_RESIZABLE);

    bool run = true;
    SDL_Event event;

    while(run) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                run = false;
            }
        }
    }

    umkaFree(umka);
    destroyBuffer(buff);
    closeSDL(window);
    return 0;
}
