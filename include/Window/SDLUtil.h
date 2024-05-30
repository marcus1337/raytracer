#pragma once
#include "pch.h"

namespace rt
{
    bool initSDL()
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            spdlog::log(spdlog::level::err, "Failed to init SDL_INIT_VIDEO");
            return false;
        }
        else if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
        {
            spdlog::log(spdlog::level::err, "Failed to init IMG_INIT_PNG");
            return false;
        }
        return true;
    }

}