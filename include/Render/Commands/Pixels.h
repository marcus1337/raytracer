#pragma once
#include "pch.h"
#include "Render/RenderCommand.h"
#include "Data/Tracing/Canvas.h"
#include "Data/Geometry/Point.h"

namespace rt
{
    namespace cmd
    {

        struct Pixel
        {
            Point position;
            Color color;
        };

        class Pixels : public RenderCommand
        {
        public:
            Pixels(const Canvas &canvas, rt::Point position) : canvas(canvas), position(position)
            {
            }
            virtual void render(SDL_Renderer *renderer)
            {
                renderPixels(renderer);
            }

        private:
            const Canvas canvas;
            const rt::Point position;

            std::vector<Pixel> getPixels() const
            {
                std::vector<Pixel> pixels;
                for (const auto &index : canvas.getIndices())
                {
                    pixels.push_back(Pixel{.position = index, .color = canvas.at(index)});
                }
                return pixels;
            }

            void renderPixel(SDL_Renderer *renderer, const Pixel &pixel) const
            {
                const auto &color = pixel.color;
                const std::size_t x = pixel.position.x;
                const std::size_t y = pixel.position.y;
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
                SDL_RenderDrawPoint(renderer, position.x + x, position.y + y);
            }

            void renderPixels(SDL_Renderer *renderer) const
            {
                for (const auto &pixel : getPixels())
                {
                    renderPixel(renderer, pixel);
                }
            }
        };
    }
}