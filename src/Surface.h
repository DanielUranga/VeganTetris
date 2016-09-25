#pragma once

#include <SDL.h>
#include <memory>
#include <map>

class Surface
{
public:
    explicit Surface(const char* path);
	Surface(Surface const&) = delete;
	Surface& operator=(Surface const&) = delete;
	Surface(Surface&&) = default;
	virtual ~Surface();
	SDL_Surface* get() { return surface; }
    static Surface* LoadBMP(const char* path);
private:
    SDL_Surface* surface;
};

namespace SurfaceCache
{
    static std::map<std::string, Surface*> surfaceCache;
}
