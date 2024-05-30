#pragma once
#include "pch.h"
#include "Render/RenderCommand.h"

namespace rt
{
    namespace cmd
    {
        class Clear : public RenderCommand
        {
        public:
            Clear(SDL_Color color = {0, 0, 0, 255}) : clearColor(color)
            {
            }
            virtual void render(SDL_Renderer *renderer)
            {
                SDL_SetRenderDrawColor(renderer, clearColor.r, clearColor.g, clearColor.b, clearColor.a);
                SDL_RenderClear(renderer);
            }

        private:
            SDL_Color clearColor;
        };
    }
}