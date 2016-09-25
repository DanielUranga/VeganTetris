#include "Surface.h"

#include <iostream>
using namespace std;

Surface::Surface(const char* path)
{
	surface = SDL_LoadBMP(path);
}

Surface::~Surface()
{
	SDL_FreeSurface(surface);
}

Surface* Surface::LoadBMP(const char* path)
{
    auto foundSurface = SurfaceCache::surfaceCache.find(path);
    if (foundSurface != SurfaceCache::surfaceCache.end())
    {
        return foundSurface->second;
    }
    else
    {
        Surface* newSurface = new Surface(path);
        SurfaceCache::surfaceCache[path] = newSurface;
        return newSurface;
    }
}
