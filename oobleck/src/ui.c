#include "../include/ui.h"

static void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

UI* CreateUI(void) {
  // InitializeSDL();
  InitializeOpenGL();
  UI* ui = (UI*)malloc(sizeof(UI));

  ui->window =
      glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "oobleck", NULL, NULL);
  if (ui->window == NULL) {
    printf("ERROR: failed to create window\n");
    exit(1);
  }

  glfwMakeContextCurrent(ui->window);
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    printf("ERROR: failed to initialize glew\n");
    exit(1);
  }

  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(ui->window, FramebufferSizeCallback);
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

void InitializeOpenGL(void) {
  int ok = glfwInit();
  if (!ok) {
    printf("ERROR: failed to initialize glfw\n");
    exit(1);
  }
  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void CloseOpenGL(void) {
  glfwTerminate();
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

  SDL_SetRenderDrawColor(ui->renderer, 255, 255, 255, 255);

  bool ok = SDL_RenderFillRect(ui->renderer, &textRect);

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
      ui->font, text, textLength, color, WINDOW_WIDTH);

  if (textSurface == NULL) {
    printf("PANIC: failure creating text surface\n");
    return;
  }

  SDL_Texture* textImage =
      SDL_CreateTextureFromSurface(ui->renderer, textSurface);

  SDL_FRect textRect = {
      .h = textSurface->h * 5,
      .w = textSurface->w * 5,
      .x = 0,
      .y = 0,
  };

  bool ok = SDL_RenderTexture(ui->renderer, textImage, NULL, &textRect);

  if (!ok) {
    printf("PANIC: failed to render texture\n");
    return;
  }

  SDL_DestroySurface(textSurface);
  SDL_DestroyTexture(textImage);
}

void DestroyUI(UI* ui) {
  TTF_CloseFont(ui->font);
  SDL_DestroyRenderer(ui->renderer);
  SDL_DestroyWindow(ui->window);
  free(ui);
  TTF_Quit();
  SDL_Quit();
}
