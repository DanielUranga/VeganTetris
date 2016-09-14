#include "CuadtritoTetris.h"

const int CuadtritoTetris::CuadtritoSize = 25;

CuadtritoTetris::CuadtritoTetris(Texture& inTex, SDL_Rect& inRect) : tex(inTex), rect(inRect)
{
}

void CuadtritoTetris::Copy(Renderer& ren)
{
    ren.Copy(tex, tex.getRect(), &rect);
}

CuadtritoTetris::~CuadtritoTetris()
{
}

CuadtritoTetris CuadtritoTetris::CreateCuadtritoTetris(Renderer& ren, Color color)
{
    SDL_Rect r;
    r.x = r.y = 0;
    r.w = r.h = CuadtritoSize;
    auto foundTexture = CuadtritoTetrisTextureCache::textureCache.find(color);
    if (foundTexture != CuadtritoTetrisTextureCache::textureCache.end())
    {
        return CuadtritoTetris(foundTexture->second, r);
    }
    else
    {
        Texture t = Texture::CreateTextureFromSurface(ren, Surface::LoadBMP("illuminati.bmp"));
        std::tuple<int, int, int> rgb = ColorUtil::getRGB(color);
        t.SetColorMod(std::get<0>(rgb), std::get<1>(rgb), std::get<2>(rgb));
        CuadtritoTetrisTextureCache::textureCache[color] = t;
        return CuadtritoTetris(t, r);
    }
}

bool CuadtritoTetris::collidesWith(const CuadtritoTetris& other) const
{
    return SDL_HasIntersection(&rect, &other.rect) == SDL_TRUE;
}
