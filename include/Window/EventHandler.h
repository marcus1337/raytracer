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
                processMouseEvent(event);
            }
        }

        bool hasQuit() const
        {
            return quit;
        }

        float getXMov()
        {
            if (leftPress)
            {
                return -v;
            }
            if (rightPress)
            {
                return v;
            }
            return 0;
        }

        float getZMov()
        {
            if (upPress)
            {
                return v;
            }
            if (downPress)
            {
                return -v;
            }
            return 0;
        }

        float getYawMove()
        {
            auto tmp = yaw;
            yaw = 0;
            return tmp;
        }
        float getPitchMove()
        {
            auto tmp = pitch;
            pitch = 0;
            return tmp;
        }

    private:
        bool quit = false;

        bool upPress = false;
        bool downPress = false;
        bool leftPress = false;
        bool rightPress = false;
        bool mouseLeftPress = false;

        int mx, my;
        float yaw = 0;
        float pitch = 0;

        static constexpr float v = 0.02f;

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

        void processMouseEvent(const SDL_Event &e)
        {
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                mouseLeftPress = true;
                SDL_GetMouseState(&mx, &my);
            }
            if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
            {
                mouseLeftPress = false;
            }
            if (e.type == SDL_MOUSEMOTION && mouseLeftPress)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                int xOffset = x - mx;
                int yOffset = my - y;
                mx = x;
                my = y;

                float sensitivity = 0.1f;
                xOffset *= sensitivity;
                yOffset *= sensitivity;

                yaw += xOffset;
                pitch += yOffset;

                if (pitch > 89.0f)
                {
                    pitch = 89.0f;
                }
                if (pitch < -89.0f)
                {
                    pitch = -89.0f;
                }

                spdlog::log(spdlog::level::info, "yaw pitch {} {} ", yaw, pitch);
            }
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