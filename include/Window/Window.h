#include "pch.h"

namespace rt
{
    class Window
    {
    public:
        Window() : window(nullptr, SDL_DestroyWindow), renderer(nullptr, SDL_DestroyRenderer)
        {
            initWindow();
            initRenderer();
        }

    private:
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
        std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;

        void initWindow()
        {
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
            SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
            window.reset(SDL_CreateWindow(
                "Ray-Tracer",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                720,
                480,
                SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL));
        }

        void initRenderer()
        {
            SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
            renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
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
    };
}