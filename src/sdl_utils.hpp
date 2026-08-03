#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

struct WindowContext {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};

bool initializeSdl(WindowContext& context, int width, int height, const char* title);
void cleanupSdl(WindowContext& context);
SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path);
