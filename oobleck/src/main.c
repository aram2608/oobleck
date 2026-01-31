#include "../include/editor.h"

int main(int argc, char** argv) {
  // Editor* editor = NewEditor(argc, argv);
  UI* ui = CreateUI();
  glGenVertexArrays(1, &ui->VAO);
  glGenBuffers(1, &ui->VBO);
  glBindVertexArray(ui->VAO);
  glBindBuffer(GL_ARRAY_BUFFER, ui->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  while (!glfwWindowShouldClose(ui->window)) {
    // Input
    if (glfwGetKey(ui->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(ui->window, true);
    }

    // Render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    int width, height;
    glfwGetFramebufferSize(ui->window, &width, &height);
    RenderText(ui, "hello world", 10.0f, height - 50.0f, 1.0f);

    // Swap buffs and poll IO
    glfwSwapBuffers(ui->window);
    glfwPollEvents();
  }

  // bool run = true;
  // SDL_Event event;
  // char c;
  // while (run) {
  //   while (SDL_PollEvent(&event)) {
  //     switch (event.type) {
  //       case SDL_EVENT_QUIT:
  //         run = false;
  //         break;
  //       case SDL_EVENT_KEY_DOWN:
  //         if (event.key.key == SDLK_BACKSPACE) {
  //           Backspace(editor);
  //         } else if (event.key.key == SDLK_LEFT) {
  //           MoveLeft(editor);
  //         } else if (event.key.key == SDLK_RIGHT) {
  //           MoveRight(editor);
  //         } else if (event.key.key == SDLK_RETURN ||
  //                    event.key.key == SDLK_RETURN2) {
  //           InsertChar(editor, '\n');
  //           IncrementLine(editor, (int)BufferGapStart(editor));
  //         } else if (event.key.key == SDLK_ESCAPE) {
  //           run = false;
  //           break;
  //         }
  //         break;
  //       case SDL_EVENT_TEXT_INPUT:
  //         c = *event.text.text;
  //         InsertChar(editor, c);
  //         break;
  //     }
  //   }
  //   RenderGUI(editor);
  // }
  // DestroyEditor(editor);
  CloseOpenGL();
  return 0;
}
