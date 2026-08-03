#include "sdl_utils.hpp"

#include <iostream>

bool initializeSdl(WindowContext& context, int width, int height, const char* title) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    std::cout << "SDL Initialized Successfully!" << std::endl;

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Error initializing SDL_image: " << IMG_GetError() << std::endl;
        cleanupSdl(context);
        return false;
    }
    std::cout << "SDL_image(PNG) Initialized Successfully!" << std::endl;

    if (TTF_Init() != 0) {
        std::cerr << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
        cleanupSdl(context);
        return false;
    }
    std::cout << "SDL_ttf Initialized Successfully!" << std::endl;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
        std::cerr << "Error initializing SDL_mixer: " << Mix_GetError() << std::endl;
        cleanupSdl(context);
        return false;
    }
    std::cout << "SDL_mixer Initialized Successfully!" << std::endl;

    context.window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (!context.window) {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        cleanupSdl(context);
        return false;
    }

    context.renderer = SDL_CreateRenderer(
        context.window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!context.renderer) {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        cleanupSdl(context);
        return false;
    }

    return true;
}

void cleanupSdl(WindowContext& context) {
    if (context.renderer) {
        SDL_DestroyRenderer(context.renderer);
        context.renderer = nullptr;
    }

    if (context.window) {
        SDL_DestroyWindow(context.window);
        context.window = nullptr;
    }

    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path) {
    SDL_Surface* surface = IMG_Load(path);

    if (!surface) {
        std::cerr << "Error Loading Image from: " << path << ":" << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Error Creating Texture from: " << path << ":" << SDL_GetError() << std::endl;
        return nullptr;
    }

    return texture;
}
