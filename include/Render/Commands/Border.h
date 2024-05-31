#pragma once
#include "pch.h"
#include "Render/RenderCommand.h"
#include "Data/Geometry/Point.h"
#include "Data/Geometry/Size.h"

namespace rt
{
    namespace cmd
    {
        class Border : public RenderCommand
        {
        public:
            Border(SDL_Rect rect, int thickness, SDL_Color color) : color(color), rect(rect), thickness(thickness)
            {
            }
            virtual void render(SDL_Renderer *renderer)
            {
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                for (const auto &border : getBorders())
                {
                    SDL_RenderFillRect(renderer, &border);
                }
            }

        private:
            SDL_Color color;
            SDL_Rect rect;
            int thickness;

            std::vector<SDL_Rect> getBorders() const
            {
                std::vector<SDL_Rect> pieces;
                pieces.push_back({rect.x, rect.y, rect.w, thickness});
                pieces.push_back({rect.x, rect.y + rect.h - thickness, rect.w, thickness});
                pieces.push_back({rect.x, rect.y, thickness, rect.h});
                pieces.push_back({rect.x + rect.w - thickness, rect.y, thickness, rect.h});
                return pieces;
            }
        };
    }
}