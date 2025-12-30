#include "../include/umkaPlugin.h"
#include "../include/gapBuffer.h"
#include "../include/graphics.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

int main(int argc, char** argv) {
    GapBuffer* buff = newBuffer(BUFFER_SIZE);
    Umka* umka = loadUmka("plugin.um", argc, argv);
    umkaRun(umka);

    initializeSDL();

    TTF_Font* font = TTF_OpenFont("./font/Fira_Code/static/FiraCode-Regular.ttf", 10);

    if (font == NULL) {
        printf("PANIC: error loading font\n");
        abort();
    }

    SDL_Window* window = SDL_CreateWindow("oobleck", 600, 600, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    bool ok = SDL_StartTextInput(window);

    if (!ok) {
        printf("PANIC: failed to start capturing text input");
        abort();
    }

    bool run = true;
    SDL_Event event;
    while(run) {
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    run = false;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    if (event.key.key == SDLK_BACKSPACE) {
                        backspace(buff);
                    }
                    break;
                case SDL_EVENT_TEXT_INPUT:
                    const char c = *event.text.text;
                    insertChar(buff, c);
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        renderText(renderer, buff->data, buff->gapStart, font);

        if (!ok) {
            printf("Failed to render texture\n");
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }

    SDL_StopTextInput(window);
    closeSDL(window, renderer, font);

    umkaFree(umka);
    destroyBuffer(buff);
    return 0;
}
