#include "../include/editor.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char** argv) {
  Editor* editor = NewEditor(argc, argv);

  bool run = true;
  SDL_Event event;
  char c;
  while (run) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_EVENT_QUIT:
          run = false;
          break;
        case SDL_EVENT_KEY_DOWN:
          if (event.key.key == SDLK_BACKSPACE) {
            Backspace(editor);
          } else if (event.key.key == SDLK_LEFT) {
            MoveLeft(editor);
          } else if (event.key.key == SDLK_RIGHT) {
            MoveRight(editor);
          } else if (event.key.key == SDLK_RETURN ||
                     event.key.key == SDLK_RETURN2) {
            InsertChar(editor, '\n');
            IncrementLine(editor, (int)BufferGapStart(editor));
          } else if (event.key.key == SDLK_ESCAPE) {
            run = false;
            break;
          }
          break;
        case SDL_EVENT_TEXT_INPUT:
          c = *event.text.text;
          InsertChar(editor, c);
          break;
      }
    }
    RenderGUI(editor);
  }
  DestroyEditor(editor);
  return 0;
}
