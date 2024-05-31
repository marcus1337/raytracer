#pragma once
#include "pch.h"
#include "Render/Renderer.h"
#include "Render/Commands/Clear.h"
#include "Render/Commands/Border.h"
#include "Render/Commands/Pixels.h"
#include "Window/Window.h"

#include "Data/Tracing/Camera.h"

namespace rt
{
    class Frame
    {
    public:
        Frame(const rt::Window &window) : targetTexture(window.renderer.makeTargetTexture(rt::Size{200, 100}))
        {
        }

        void render(Renderer &renderer, const rt::Size &windowSize) const
        {
            setCommands(renderer);
            renderer.render(targetTexture, windowSize);
        }

    private:
        TargetTexture targetTexture;

        void setCommands(Renderer &renderer) const
        {
            renderer.clearCommands();
            renderer.addCommands(getRenderCommands());
        }

        Canvas makeCanvas() const
        {
            Canvas canvas(10, 5);
            for (int x = 0; x < canvas.getWidth(); x++)
            {
                const auto color = Color(200, 0, 0);
                canvas.set(x, 0, color);
                canvas.set(x, 4, color);
            }
            for (int y = 0; y < canvas.getHeight(); y++)
            {
                const auto color = Color(200, 100, 0);
                canvas.set(0, y, color);
                canvas.set(9, y, color);
            }
            return canvas;
        }

        std::unique_ptr<rt::RenderCommand> makeBorderCommand() const
        {
            const int thickness = 10;
            const auto color = SDL_Color{125, 125, 125, 255};
            const auto rect = SDL_Rect{0, 0, targetTexture.getWidth(), targetTexture.getHeight()};
            return std::make_unique<rt::cmd::Border>(rect, thickness, color);
        }

        std::unique_ptr<rt::RenderCommand> makeClearCommand() const
        {
            return std::make_unique<rt::cmd::Clear>(SDL_Color{100, 25, 25, 255});
        }

        std::unique_ptr<rt::RenderCommand> makePixelsCommand() const
        {
            return std::make_unique<rt::cmd::Pixels>(makeCanvas(), Point{10, 10});
        }

        std::vector<std::unique_ptr<rt::RenderCommand>> getRenderCommands() const
        {
            std::vector<std::unique_ptr<rt::RenderCommand>> commands;
            commands.push_back(makeClearCommand());
            commands.push_back(makePixelsCommand());
            commands.push_back(makeBorderCommand());
            return commands;
        }
    };
}