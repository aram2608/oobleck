#include "../include/editor.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char** argv) {
    Editor* editor = newEditor(argc, argv);

    bool run = true;
    SDL_Event event;
    while(run) {
        char textBuffer[256] = "";
        bool ok = SDL_StartTextInput((editor)->ui->window);
        if (!ok) {
            printf("PANIC: failed to start capturing text input");
            abort();
        }

        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    run = false;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    if (event.key.key == SDLK_BACKSPACE) {
                        backspace(editor);
                    } else if (event.key.key == SDLK_LEFT) {
                        moveLeft(editor);
                    } else if (event.key.key == SDLK_RIGHT) {
                        moveRight(editor);
                    } else if (event.key.key == SDLK_ESCAPE) {
                        run = false;
                        break;
                    }
                    break;
                case SDL_EVENT_TEXT_INPUT:
                    strcat(textBuffer, event.text.text);
                    insertString(editor, textBuffer);
                    break;
            }
        }
        SDL_StopTextInput((editor)->ui->window);
        SDL_SetRenderDrawColor((editor)->ui->renderer, 0, 0, 0, 0);
        SDL_RenderClear((editor)->ui->renderer);
        renderText((editor)->ui, (editor)->buffer->data, (editor)->buffer->gapStart);
        SDL_RenderPresent((editor)->ui->renderer);
    }

    destroyEditor(editor);
    return 0;
}
