#pragma once

#include "Renderer.h"
#include "Surface.h"

#include <SDL.h>
#include <memory>

class Renderer;

class Texture
{
public:
    Texture();
    Texture(SDL_Texture* inTexture);
    ~Texture();
    int SetColorMod(Uint8 r, Uint8 g, Uint8 b);
    static Texture CreateTextureFromSurface(Renderer &ren, Surface &bmp);
    SDL_Texture* get() { return texture.get()->tex; }
    int getW() const { return texture.get()->rect->w; }
    int getH() const { return texture.get()->rect->h; }
    SDL_Rect* getRect() { return texture.get()->rect; }
    void SetAlpha(Uint8 alpha);
    void SetBlendMode(SDL_BlendMode blendMode);
private:
    struct TextureWrapper
    {
        SDL_Texture* tex;
        SDL_Rect* rect;
        TextureWrapper(SDL_Texture* inTex, SDL_Rect* inRect) : tex(inTex), rect(inRect) {}
        ~TextureWrapper() { SDL_DestroyTexture(tex); delete rect; };
    };
    std::shared_ptr<TextureWrapper> texture;
};
