#include "Texture.h"

Texture::Texture() : texture(nullptr)
{
}

Texture::Texture(SDL_Texture* inTexture)
{
    SDL_Rect* r = new SDL_Rect();
    texture = std::make_shared<TextureWrapper>(inTexture, r);
    SDL_QueryTexture(inTexture, NULL, NULL, &(r->w), &(r->h));
}

Texture::~Texture()
{
}

int Texture::SetColorMod(Uint8 r, Uint8 g, Uint8 b)
{
    return SDL_SetTextureColorMod(get(), r, g, b);
}

Texture Texture::CreateTextureFromSurface(Renderer &ren, Surface &bmp)
{
    return SDL_CreateTextureFromSurface(ren.get(), bmp.get());
}

void Texture::SetAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(texture->tex, alpha);
}

void Texture::SetBlendMode(SDL_BlendMode blendMode)
{
    SDL_SetTextureBlendMode(texture->tex, blendMode);
}