#pragma once
#include "pch.h"
#include "Geometry/Size.h"
#include "Geometry/Point.h"

namespace rt
{
    class TargetTexture
    {
    public:
        TargetTexture(SDL_Renderer *renderer, const Size &size) : texture(nullptr, SDL_DestroyTexture), size(size)
        {
            texture.reset(SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size.width, size.height));
            SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND);
        }
        void setAsRenderTarget(SDL_Renderer *renderer) const
        {
            SDL_SetRenderTarget(renderer, texture.get());
        }

        void renderAsWindowFrame(SDL_Renderer *renderer, const Size &windowSize) const
        {
            render(renderer, getOffset(windowSize), getScaledSize(windowSize));
        }

        void render(SDL_Renderer *renderer, const Point &position, const SDL_Rect &dstRect) const
        {
            SDL_RenderCopy(renderer, texture.get(), NULL, &dstRect);
        }

    private:
        const Size size;
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture;
        TargetTexture(const TargetTexture &) = delete;
        TargetTexture &operator=(const TargetTexture &) = delete;

        SDL_Rect getScaledSize(const Size &frameSize) const
        {
            SDL_Rect scale;

            return scale;
        }

        Point getOffset(const Size &frameSize) const
        {
            Point offset;

            return offset;
        }
    };
}
