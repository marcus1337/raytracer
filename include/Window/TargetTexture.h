#pragma once
#include "pch.h"
#include "Geometry/Size.h"
#include "Geometry/Point.h"

namespace rt
{
    class TargetTexture
    {
    public:
        TargetTexture(SDL_Renderer *renderer, const Size &size) : texture(nullptr, SDL_DestroyTexture)
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

        TargetTexture(TargetTexture &&other) noexcept
            : texture(std::move(other.texture))
        {
            other.texture = nullptr;
        }

        TargetTexture &operator=(TargetTexture &&other) noexcept
        {
            if (this != &other)
            {
                texture = std::move(other.texture);
                other.texture = nullptr;
            }
            return *this;
        }

        Size getSize() const
        {
            Size size;
            SDL_QueryTexture(texture.get(), nullptr, nullptr, &size.width, &size.height);
            return size;
        }

    private:
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture;
        TargetTexture(const TargetTexture &) = delete;
        TargetTexture &operator=(const TargetTexture &) = delete;

        Size getScaledSize(const Size &frameSize) const
        {
            const auto aspectRatio = getSize().getRatio();
            const auto frameAspectRatio = frameSize.getRatio();
            const bool biggerRatio = aspectRatio > frameAspectRatio;
            const auto width = biggerRatio ? frameSize.width : static_cast<int>(frameSize.height * aspectRatio);
            const auto height = biggerRatio ? static_cast<int>(frameSize.width / aspectRatio) : frameSize.height;
            return Size{width, height};
        }

        Point getOffset(const Size &frameSize) const
        {
            const auto scaledSize = getScaledSize(frameSize);
            const auto x = (frameSize.width - scaledSize.width) / 2;
            const auto y = (frameSize.height - scaledSize.height) / 2;
            return Point{x, y};
        }

        void render(SDL_Renderer *renderer, const Point &position, const Size &dstSize) const
        {
            const SDL_Rect dstRect{position.x, position.y, dstSize.width, dstSize.height};
            SDL_RenderCopy(renderer, texture.get(), NULL, &dstRect);
        }
    };
}
