#pragma once

#include "Texture.h"
#include "Color.h"
#include <memory>

class CuadtritoTetris
{
public:

	virtual ~CuadtritoTetris();
    int GetX() const { return rect.x; }
    int GetY() const { return rect.y; }
    void SetX(int x) { rect.x = x; }
    void SetY(int y) { rect.y = y; }
    void Copy(Renderer& ren);
    static CuadtritoTetris CreateCuadtritoTetris(Renderer& ren, Color color);
    bool collidesWith(const CuadtritoTetris& other) const;

    static const int CuadtritoSize;

private:

    CuadtritoTetris(Texture* inTex, SDL_Rect& inRect);
    Texture* tex;
    SDL_Rect rect;

};

namespace CuadtritoTetrisTextureCache
{
    static std::map<Color, Texture*> textureCache;
}
