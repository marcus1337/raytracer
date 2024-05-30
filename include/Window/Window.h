#include "pch.h"
#include "Render/Renderer.h"

namespace rt
{
    class Window
    {
    public:
        Window() : window(makeSDLWindow()), renderer(window.get())
        {
        }

    private:
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> makeSDLWindow()
        {
            std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window(nullptr, SDL_DestroyWindow);
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
            return std::move(window);
        }

    public:
        Renderer renderer;
    };
}