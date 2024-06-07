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

        std::vector<glm::vec3> getEventMoves()
        {
            std::vector<glm::vec3> moves;
            static constexpr float v = 0.02f;

            if (upPress)
            {
                moves.push_back(glm::vec3(0, 0, -v));
            }
            if (downPress)
            {
                moves.push_back(glm::vec3(0, 0, v));
            }
            if (leftPress)
            {
                moves.push_back(glm::vec3(-v, 0, 0));
            }
            if (rightPress)
            {
                moves.push_back(glm::vec3(v, 0, 0));
            }

            return moves;
        }

    private:
        bool quit = false;

        bool upPress = false;
        bool downPress = false;
        bool leftPress = false;
        bool rightPress = false;

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
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_a:
                    leftPress = true;
                    break;
                case SDLK_s:
                    downPress = true;
                    break;
                case SDLK_w:
                    upPress = true;
                    break;
                case SDLK_d:
                    rightPress = true;
                    break;
                }
            }
            if (event.type == SDL_KEYUP)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_a:
                    leftPress = false;
                    break;
                case SDLK_s:
                    downPress = false;
                    break;
                case SDLK_w:
                    upPress = false;
                    break;
                case SDLK_d:
                    rightPress = false;
                    break;
                }
            }
        }
    };
}