#include "Texture.h"

Texture::Texture() : texture(nullptr), rect(nullptr)
{

}

Texture::Texture(Renderer &ren, Surface &bmp)
	: texture(SDL_CreateTextureFromSurface(ren.get(), bmp.get()))
	, rect(new SDL_Rect())
{
    SDL_QueryTexture(texture, NULL, NULL, &(rect->w), &(rect->h));
}

Texture::~Texture()
{
	if (nullptr != rect)
	{
		delete rect;
	}
	if (nullptr != texture)
	{
		SDL_DestroyTexture(texture);
	}
}

int Texture::SetColorMod(Uint8 r, Uint8 g, Uint8 b)
{
    return SDL_SetTextureColorMod(get(), r, g, b);
}

Texture* Texture::CreateTextureFromSurface(Renderer& ren, Surface& bmp)
{
	return new Texture(ren, bmp);
}

void Texture::SetAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(texture, alpha);
}

void Texture::SetBlendMode(SDL_BlendMode blendMode)
{
    SDL_SetTextureBlendMode(texture, blendMode);
}