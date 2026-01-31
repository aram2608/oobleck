#include "../include/ui.h"

static void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

UI* CreateUI(void) {
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
  LoadFont(ui);
  ui->shader = CompileShader();
  return ui;
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

void LoadFont(UI* ui) {
  FT_Library ft = {0};
  FT_Error error = FT_Init_FreeType(&ft);
  if (error) {
    printf("ERROR: failed to init free type library\n");
    exit(1);
  }

  FT_Face face;
  const char* font_path = "font/Fira_Code/static/FiraCode-Regular.ttf";
  error = FT_New_Face(ft, font_path, 0, &face);
  if (error) {
    printf("ERROR: failed to init free type face for %s\n", font_path);
    exit(1);
  }
  FT_Set_Pixel_Sizes(face, 0, 48);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  for (unsigned char c = 32; c <= 126; ++c) {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      printf("ERROR: failed to load glyph %c", c);
      continue;
    }
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
                 face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                 face->glyph->bitmap.buffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Character glyph = {
        .texture_id = texture,
        .size = {face->glyph->bitmap.width, face->glyph->bitmap.rows},
        .bearing = {face->glyph->bitmap_left, face->glyph->bitmap_top},
        .advance = face->glyph->advance.x,
    };
    ui->glyphs[c] = glyph;
  }
  FT_Done_Face(face);
  FT_Done_FreeType(ft);
}

void CloseOpenGL(void) {
  glfwTerminate();
}

void RenderCursor(UI* ui, size_t cursor_pos, size_t line_index) {}

void RenderText(UI* ui, const char* text, float x, float y, float scale) {
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  mat4 projection;
  int width, height;
  glfwGetFramebufferSize(ui->window, &width, &height);
  glm_ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f, projection);
  glUseProgram(ui->shader.ID);
  glUniformMatrix4fv(glGetUniformLocation(ui->shader.ID, "projection"), 1,
                     GL_FALSE, (float*)projection);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glUniform3f(glGetUniformLocation(ui->shader.ID, "textColor"), 0.3f, 0.7f,
              0.9f);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(ui->VAO);

  size_t len = strlen(text);
  for (size_t it = 0; it < len; ++it) {
    int index = (int)text[it] - 32;
    if (index < 0) {
      continue;
    }
    unsigned char ch = text[it];
    Character* c = &ui->glyphs[ch];

    float x_pos = x + c->bearing.x * scale;
    float y_pos = y - (c->size.y - c->bearing.y) * scale;
    float w = c->size.x * scale;
    float h = c->size.y * scale;

    float vertices[6][4] = {
        {x_pos, y_pos + h, 0.0f, 0.0f},    {x_pos, y_pos, 0.0f, 1.0f},
        {x_pos + w, y_pos, 1.0f, 1.0f},

        {x_pos, y_pos + h, 0.0f, 0.0f},    {x_pos + w, y_pos, 1.0f, 1.0f},
        {x_pos + w, y_pos + h, 1.0f, 0.0f}};

    glBindTexture(GL_TEXTURE_2D, c->texture_id);

    glBindBuffer(GL_ARRAY_BUFFER, ui->VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    x += (c->advance / 64.0f) * scale;
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_BLEND);
}

void DestroyUI(UI* ui) {
  (void*)ui;
}
