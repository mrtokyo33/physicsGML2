#include "drawing.hpp"

#include <cmath>

void drawFilledCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius, const SDL_Color& color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int dy = -radius; dy <= radius; ++dy) {
        const int halfWidth = static_cast<int>(std::sqrt(radius * radius - dy * dy));

        SDL_RenderDrawLine(
            renderer,
            centerX - halfWidth,
            centerY + dy,
            centerX + halfWidth,
            centerY + dy
        );
    }
}
