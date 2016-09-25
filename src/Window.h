#pragma once

#include <SDL.h>

class Window
{
public:
    Window(SDL_Window* inWindow);
	virtual ~Window();
    static Window CreateWindow(
        const char* name = "SDL",
        int x = SDL_WINDOWPOS_CENTERED,
        int y = SDL_WINDOWPOS_CENTERED,
        int w = 500,
        int h = 800,
        Uint32 flags = SDL_WINDOW_OPENGL
    );
    SDL_Window* get() { return window; }
    int getW() const { return w; }
    int getH() const { return h; }
private:
    int w, h;
    SDL_Window* window;
};
