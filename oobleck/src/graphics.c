#include "../include/graphics.h"

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

void closeSDL(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font) {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void renderText(SDL_Renderer* renderer, const char* text, size_t textSize, TTF_Font* font) {
    if (strlen(text) == 0) {
        return;
    }

    SDL_Color color = {
        .r = 255,
        .g = 255,
        .b = 255,
        .a = 255,
    };

    SDL_Surface* textSurface = textSurface = TTF_RenderText_Solid(font, text, textSize, color);

    if (textSurface == NULL) {
        printf("PANIC: failure creating text surface");
        abort();
    }

    SDL_Texture* textImage = textImage = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_FRect textRect = {
        .h = textSurface->h * 3,
        .w = textSurface->w * 3,
        .x = 0,
        .y = 0,
    };

    bool ok = SDL_RenderTexture(renderer, textImage, NULL, &textRect);

    if (!ok) {
        printf("Failed to render texture\n");
        abort();
    }

    SDL_DestroySurface(textSurface);
    SDL_DestroyTexture(textImage);
}