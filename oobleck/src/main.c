#include "../include/editor.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

int main(int argc, char** argv) {
    Editor* editor = newEditor(argc, argv);

    bool run = true;
    SDL_Event event;
    char c;

    while(run) {
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    run = false;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    if (event.key.key == SDLK_BACKSPACE) {
                        backspace(editor->buffer);
                    } else if (event.key.key == SDLK_ESCAPE) {
                        run = false;
                        break;
                    }
                    break;
                case SDL_EVENT_TEXT_INPUT:
                    c = *event.text.text;
                    insertChar(editor, c);
                    break;
            }
        }
        SDL_SetRenderDrawColor(editor->ui->renderer, 0, 0, 0, 0);
        SDL_RenderClear(editor->ui->renderer);
        renderText(editor->ui, editor->buffer->data, editor->buffer->gapStart);
        SDL_RenderPresent(editor->ui->renderer);
        SDL_Delay(20);
    }

    destroyEditor(editor);
    return 0;
}
