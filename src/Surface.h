#pragma once

#include <SDL.h>
#include <memory>
#include <map>

class Surface
{
public:
    Surface();
    Surface(SDL_Surface*);
    Surface(const char* path);
    SDL_Surface* get() { return surface.get()->surf; }
    static Surface LoadBMP(const char* path);
private:
    struct SurfaceWrapper
    {
        SDL_Surface* surf;
        SurfaceWrapper(const char* path) { surf = SDL_LoadBMP(path); };
        SurfaceWrapper(SDL_Surface* inSurf) : surf(inSurf) {}
        ~SurfaceWrapper() { SDL_FreeSurface(surf); }
    };
    std::shared_ptr<SurfaceWrapper> surface;
};

namespace SurfaceCache
{
    static std::map<std::string, Surface> surfaceCache;
}
