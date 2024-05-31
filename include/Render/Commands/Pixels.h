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
                SDL_BlendMode oldBlendMode;
                SDL_GetRenderDrawBlendMode(renderer, &oldBlendMode);
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

                renderPixels(renderer);

                SDL_SetRenderDrawBlendMode(renderer, oldBlendMode);
            }

        private:
            const Canvas canvas;
            const rt::Point position;

            std::vector<Pixel> getPixels() const
            {
                std::vector<Pixel> pixels;
                for (int x = 0; x < canvas.getWidth(); x++)
                {
                    for (int y = 0; y < canvas.getHeight(); y++)
                    {
                        pixels.push_back(Pixel{.position = Point(x, y), .color = canvas.at(x, y)});
                    }
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