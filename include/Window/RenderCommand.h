#pragma once
#include "pch.h"

namespace rt
{

    class RenderCommand
    {
    public:
        virtual ~RenderCommand() = default;
        virtual void render(SDL_Renderer *renderer) = 0;
    };

}