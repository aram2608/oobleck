#include "../include/ui.h"

UI* createUI(void) {
    initializeSDL();
    UI* ui = (UI*)malloc(sizeof(UI));

    (ui)->font = TTF_OpenFont("./font/Fira_Code/static/FiraCode-Regular.ttf", 10);

    if ((ui)->font == NULL) {
        printf("PANIC: failed to load font\n");
        abort();
    }

    (ui)->window = SDL_CreateWindow("oobleck", WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_PARAMS);
    (ui)->renderer = SDL_CreateRenderer((ui)->window, NULL);
    return ui;
}

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

void renderText(UI* ui, const char* text) {
    if (strlen(text) == 0) {
        return;
    }

    SDL_Color color = {
        .r = 255,
        .g = 255,
        .b = 255,
        .a = 255,
    };

    SDL_Surface* textSurface = textSurface = TTF_RenderText_Solid((ui)->font, text, 0, color);

    if (textSurface == NULL) {
        printf("PANIC: failure creating text surface\n");
        return;
    }

    SDL_Texture* textImage = textImage = SDL_CreateTextureFromSurface((ui)->renderer, textSurface);

    SDL_FRect textRect = {
        .h = textSurface->h * 5,
        .w = textSurface->w * 5,
        .x = 0,
        .y = 0,
    };

    bool ok = SDL_RenderTexture((ui)->renderer, textImage, NULL, &textRect);

    if (!ok) {
        printf("PANIC: failed to render texture\n");
        return;
    }
    free(text);
    SDL_DestroySurface(textSurface);
    SDL_DestroyTexture(textImage);
}

void destroyUI(UI *ui) {
    TTF_CloseFont((ui)->font);
    SDL_DestroyRenderer((ui)->renderer);
    SDL_DestroyWindow((ui)->window);
    free(ui);
    TTF_Quit();
    SDL_Quit();
}
