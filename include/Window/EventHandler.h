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

                processMoveEvent(event);
            }
        }

        bool hasQuit() const
        {
            return quit;
        }

        std::vector<glm::vec3> moves;

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

        void processMoveEvent(const SDL_Event &event)
        {
            static constexpr float v = 0.02f;
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_a:
                    spdlog::info("A key pressed.");
                    moves.push_back(glm::vec3(-v, 0, 0));
                    break;
                case SDLK_s:
                    spdlog::info("S key pressed.");
                    moves.push_back(glm::vec3(0, 0, -v));
                    break;
                case SDLK_w:
                    spdlog::info("W key pressed.");
                    moves.push_back(glm::vec3(0, 0, v));
                    break;
                case SDLK_d:
                    spdlog::info("D key pressed.");
                    moves.push_back(glm::vec3(v, 0, 0));
                    break;
                }
            }
        }
    };
}