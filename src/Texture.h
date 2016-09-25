#pragma once

#include "Renderer.h"
#include "Surface.h"

#include <SDL.h>
#include <memory>

class Renderer;

class Texture
{
public:
	explicit Texture();
	explicit Texture(Renderer &ren, Surface &bmp);
	Texture(Texture const&) = delete;
	Texture& operator=(Texture const&) = delete;
	Texture(Texture&&) = default;
    ~Texture();
    int SetColorMod(Uint8 r, Uint8 g, Uint8 b);
    static Texture* CreateTextureFromSurface(Renderer &ren, Surface &bmp);
    SDL_Texture* get() { return texture; }
    int getW() const { return rect->w; }
    int getH() const { return rect->h; }
    SDL_Rect* getRect() { return rect; }
    void SetAlpha(Uint8 alpha);
    void SetBlendMode(SDL_BlendMode blendMode);
private:
    SDL_Texture* texture;
	SDL_Rect* rect;
};
