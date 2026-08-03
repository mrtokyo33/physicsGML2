#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

#include "constants.hpp"
#include "drawing.hpp"
#include "math/quaternion.hpp"
#include "math/vector.hpp"
#include "sdl_utils.hpp"

struct Particle {
    Vector3D position;
    Vector3D velocity;
    int radius = 10;
};

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    WindowContext context;

    if (!initializeSdl(context, WindowWidth, WindowHeight, "Physics")) {
        return -1;
    }

    int BigRadius = 100;
    Vector3D Center{WindowWidth / 2.0, WindowHeight / 2.0, 0.0};
    Vector3D ParticleVelocity{50.0, 0.0, 0.0};

    const double tangential_speed = ParticleVelocity.magnitude();
    const double angular_speed = tangential_speed / static_cast<double>(BigRadius);
    double orbit_angle = 0.0;

    Particle particle{
        Center + Vector3D{static_cast<double>(BigRadius), 0.0, 0.0},
        Vector3D{0.0, tangential_speed, 0.0},
        25
    };

    bool running = true;
    SDL_Event event;

    Uint32 previous_tick = SDL_GetTicks();
    float delta_time = 0.0f;

    while (running) {
        const Uint32 current_tick = SDL_GetTicks();
        delta_time = (current_tick - previous_tick) / 1000.0f;
        previous_tick = current_tick;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
            }
        }

        orbit_angle += angular_speed * delta_time;

        const Vector3D orbital_offset{
            static_cast<double>(BigRadius) * std::cos(orbit_angle),
            static_cast<double>(BigRadius) * std::sin(orbit_angle),
            0.0
        };

        particle.position = Center + orbital_offset;

        particle.velocity = Vector3D{
            -tangential_speed * std::sin(orbit_angle),
            tangential_speed * std::cos(orbit_angle),
            0.0
        };

        SDL_SetRenderDrawColor(context.renderer, 12, 12, 12, 255);
        SDL_RenderClear(context.renderer);

        const SDL_Color red = {66, 33, 67, 255};
        drawFilledCircle(
            context.renderer,
            static_cast<int>(std::lround(particle.position.x)),
            static_cast<int>(std::lround(particle.position.y)),
            particle.radius,
            red
        );

        SDL_RenderPresent(context.renderer);

        const Uint32 frame_time = SDL_GetTicks() - current_tick;
        if (frame_time < FrameDurationMs) {
            SDL_Delay(FrameDurationMs - frame_time);
        }
    }

    cleanupSdl(context);

    std::cout << "Application exited successfully!" << std::endl;
    return 0;
}