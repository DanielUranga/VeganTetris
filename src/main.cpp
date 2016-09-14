#include <SDL.h>
#include <stdio.h>

#include "Color.h"
#include "Surface.h"
#include "Window.h"
#include "Renderer.h"
#include "Texture.h"
#include "Tetrominio.h"
#include "Board.h"
#include "Random.h"

#include <iostream>
#include <vector>

extern "C" { FILE __iob_func[3] = { *stdin, *stdout, stderr }; }

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
    auto joy = SDL_JoystickOpen(0);
    SDL_JoystickEventState(SDL_ENABLE);
    {
        Window w = Window::CreateWindow("Vegan Tetris");
        Renderer r = Renderer::CreateRenderer(w);
        Board board(r, w.getW() / CuadtritoTetris::CuadtritoSize - 5, w.getH() / CuadtritoTetris::CuadtritoSize);

        Uint32 lastTicks = SDL_GetTicks();
        while (1) {

            Uint32 now = SDL_GetTicks();

            SDL_Event e;
            if (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    break;
                }
                else if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_LEFT:
                        board.tryMoveLeft();
                        break;
                    case SDLK_RIGHT:
                        board.tryMoveRight();
                        break;
                    case SDLK_DOWN:
                        board.startMoveDown();
                        break;
                    case SDLK_q:
                        board.tryRotateLeft();
                        break;
                    case SDLK_w:
                        board.tryRotateRight();
                        break;
                    default:
                        break;
                    }
                }
                else if (e.type == SDL_KEYUP)
                {
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_DOWN:
                        board.stopMoveDown();
                        break;
                    default:
                        break;
                    }
                }
                else if (e.type == SDL_JOYBUTTONDOWN) {
                    std::cout << "Btn: " << e.jbutton.button << std::endl;
                }
                else if (e.type == SDL_JOYAXISMOTION) {
                }
                else if (e.type == SDL_JOYHATMOTION) {
                    switch (e.jhat.value)
                    {
                    case SDL_HAT_LEFT:
                        board.tryMoveLeft();
                        break;
                    case SDL_HAT_RIGHT:
                        board.tryMoveRight();
                        break;
                    case SDL_HAT_DOWN:
                        board.startMoveDown();
                        break;
                    default:
                        board.stopMoveDown();
                        break;
                    }
                }
            }
            r.Clear();
            board.Update(now - lastTicks);
            board.Copy(r);
            r.Present();

            lastTicks = now;

        }
    }

    //SDL_Delay(2000);

    SDL_Quit();

    return 0;
}
