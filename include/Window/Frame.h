#pragma once
#include "pch.h"
#include "Render/Renderer.h"
#include "Render/Commands/Clear.h"
#include "Render/Commands/Border.h"
#include "Window/Window.h"

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

        std::vector<std::unique_ptr<rt::RenderCommand>> getRenderCommands() const
        {
            std::vector<std::unique_ptr<rt::RenderCommand>> commands;
            commands.push_back(makeClearCommand());
            commands.push_back(makeBorderCommand());
            return commands;
        }
    };
}