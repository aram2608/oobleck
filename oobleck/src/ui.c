#include "../include/ui.h"

UI* CreateUI(void) {
  InitializeSDL();
  UI* ui = (UI*)malloc(sizeof(UI));

  (ui)->font = TTF_OpenFont("./font/Fira_Code/static/FiraCode-Regular.ttf", 10);

  if ((ui)->font == NULL) {
    printf("PANIC: failed to load font\n");
    abort();
  }

  (ui)->window =
      SDL_CreateWindow("oobleck", WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_PARAMS);
  (ui)->renderer = SDL_CreateRenderer((ui)->window, NULL);
  return ui;
}

void InitializeSDL(void) {
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

void RenderCursor(UI* ui, size_t cursor_pos, size_t line_index) {
  SDL_FRect textRect = {0};

  // This is a bit of a hack but i dont know how else to calculate the
  // y position
  if (line_index > 0) {
    textRect.h = 50;
    textRect.w = 30;
    textRect.x = cursor_pos * 30;
    textRect.y = 75 * line_index;
  } else {
    textRect.h = 50;
    textRect.w = 30;
    textRect.x = cursor_pos * 30;
    textRect.y = 50 * line_index;
  }

  SDL_SetRenderDrawColor((ui)->renderer, 255, 255, 255, 255);

  bool ok = SDL_RenderFillRect((ui)->renderer, &textRect);

  if (!ok) {
    printf("PANIC: failed to render cursor");
    return;
  }
}

void RenderText(UI* ui, const char* text, size_t textLength) {
  if (strlen(text) == 0 || textLength == 0) {
    return;
  }

  SDL_Color color = {
      .r = 255,
      .g = 255,
      .b = 255,
      .a = 255,
  };

  SDL_Surface* textSurface = TTF_RenderText_Solid_Wrapped(
      (ui)->font, text, textLength, color, WINDOW_WIDTH);

  if (textSurface == NULL) {
    printf("PANIC: failure creating text surface\n");
    return;
  }

  SDL_Texture* textImage =
      SDL_CreateTextureFromSurface((ui)->renderer, textSurface);

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

  SDL_DestroySurface(textSurface);
  SDL_DestroyTexture(textImage);
}

void DestroyUI(UI* ui) {
  TTF_CloseFont((ui)->font);
  SDL_DestroyRenderer((ui)->renderer);
  SDL_DestroyWindow((ui)->window);
  free(ui);
  TTF_Quit();
  SDL_Quit();
}
