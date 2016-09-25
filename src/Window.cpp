#include "Window.h"

#include <iostream>
using namespace std;

Window::Window(SDL_Window* inWindow) : window(inWindow)
{
    SDL_GetWindowSize(inWindow, &w, &h);
}

Window::~Window()
{
    SDL_DestroyWindow(window);
}

Window Window::CreateWindow(const char* name, int x, int y, int w, int h, Uint32 flags)
{
    return SDL_CreateWindow(name, x, y, w, h, flags);
}
