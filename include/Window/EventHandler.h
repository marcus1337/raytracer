#pragma once
#include "pch.h"
#include "Data/Canvas.h"

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
            }
        }

        bool hasQuit() const
        {
            return quit;
        }

    private:
        bool quit = false;

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