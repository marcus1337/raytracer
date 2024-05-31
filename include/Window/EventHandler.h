#pragma once
#include "pch.h"

namespace rt
{
    class EventHandler
    {
    public:
        EventHandler()
        {
        }

        void processEvents()
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (isQuitEvent(event))
                {
                    quit = true;
                }
                if (isWindowResizeEvent(event))
                {
                    spdlog::log(spdlog::level::info, "Window size: {} {}", event.window.data1, event.window.data2);
                }
            }
        }

        bool hasQuit() const
        {
            return quit;
        }

    private:
        bool quit = false;

        bool isWindowResizeEvent(const SDL_Event &event) const
        {
            return event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED;
        }

        bool isQuitEvent(const SDL_Event &event) const
        {
            if (event.type == SDL_QUIT)
            {
                return true;
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                return true;
            }
            return false;
        }
    };
}