#include "Surface.h"

#include <iostream>
using namespace std;

Surface::Surface()
{
}

Surface::Surface(SDL_Surface* inSurface)
{
    surface = std::make_shared<SurfaceWrapper>(inSurface);
}

Surface::Surface(const char* path)
{
    surface = std::make_shared<SurfaceWrapper>(path);
}

Surface Surface::LoadBMP(const char* path)
{
    auto foundSurface = SurfaceCache::surfaceCache.find(path);
    if (foundSurface != SurfaceCache::surfaceCache.end())
    {
        return foundSurface->second;
    }
    else
    {
        Surface newSurface(path);
        SurfaceCache::surfaceCache[path] = newSurface;
        return newSurface;
    }
}
