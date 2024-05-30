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

        void addCommand(std::unique_ptr<RenderCommand> command)
        {
            renderCommands.push_back(std::move(command));
        }

        void addCommands(std::vector<std::unique_ptr<RenderCommand>> &&commands)
        {
            for (auto &command : commands)
            {
                addCommand(std::move(command));
            }
        }

        void clearCommands()
        {
            renderCommands.clear();
        }

        void render()
        {
            for (const auto &command : renderCommands)
            {
                command->render(renderer.get());
            }
            SDL_RenderPresent(renderer.get());
        }

    private:
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
        std::vector<std::unique_ptr<RenderCommand>> renderCommands;
    };

}