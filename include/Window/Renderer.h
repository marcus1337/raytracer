#pragma once
#include "pch.h"
#include "RenderCommand.h"

namespace rt
{
    class Renderer
    {
    public:
        Renderer(SDL_Window *window) : renderer(nullptr, SDL_DestroyRenderer)
        {
            SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
            renderer.reset(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
            if (renderer)
            {
                SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_BLEND);
            }
            if (SDL_GL_SetSwapInterval(-1) < 0)
            {
                spdlog::log(spdlog::level::warn, "Failed Activating Adaptive Vsync {}", SDL_GetError());
                if (SDL_GL_SetSwapInterval(1) < 0)
                {
                    spdlog::log(spdlog::level::warn, "Failed Activating Vsync {}", SDL_GetError());
                }
            }
        }

    private:
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
    };

}