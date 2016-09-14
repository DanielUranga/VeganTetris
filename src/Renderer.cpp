#include "Renderer.h"

#include <iostream>
using namespace std;

Renderer::Renderer(SDL_Renderer * inRenderer) : renderer(inRenderer)
{
}

Renderer::~Renderer()
{
    cout << "Destroy renderer" << endl;
    SDL_DestroyRenderer(renderer);
}

void Renderer::Clear()
{
    SDL_RenderClear(renderer);
}

void Renderer::Copy(Texture &t, SDL_Rect* src, SDL_Rect* dst)
{
    SDL_RenderCopy(renderer, t.get(), src != nullptr ? src : t.getRect(), dst != nullptr ? dst : t.getRect());
}

void Renderer::Present()
{
    SDL_RenderPresent(renderer);
}

Renderer Renderer::CreateRenderer(Window &window)
{
    return SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED);
}
