#pragma once
#include "pch.h"
#include "Render/RenderCommand.h"
#include "Data/Tracing/Canvas.h"
#include "Data/Geometry/Point.h"

namespace rt
{
    namespace cmd
    {
        class Pixels : public RenderCommand
        {
        public:
            Pixels(const Canvas &canvas, rt::Point position) : canvas(canvas), position(position)
            {
            }
            virtual void render(SDL_Renderer *renderer)
            {
                for (int x = 0; x < canvas.getWidth(); x++)
                {
                    for (int y = 0; y < canvas.getHeight(); y++)
                    {
                        const auto color = canvas.at(x, y);
                        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
                        SDL_RenderDrawPoint(renderer, position.x + x, position.y + y);
                    }
                }
            }

        private:
            const Canvas canvas;
            const rt::Point position;
        };
    }
}