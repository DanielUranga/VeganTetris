#pragma once

#include <SDL.h>

#include "Window.h"
#include "Texture.h"

class Texture;

class Renderer
{
public:
    Renderer(SDL_Renderer* inRenderer);
    ~Renderer();
    void Clear();
    void Copy(Texture &t, SDL_Rect* src = nullptr, SDL_Rect* dst = nullptr);
    void Present();
    SDL_Renderer* get() { return renderer; }
    static Renderer CreateRenderer(Window &window);
private:
    SDL_Renderer* renderer;
};
