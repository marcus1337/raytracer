#pragma once
#include "pch.h"
#include "Data/Canvas.h"
#include "Render/Renderer.h"
#include "Render/Commands/Clear.h"
#include "Render/Commands/Border.h"
#include "Window/Window.h"

namespace rt
{
    class Frame
    {
    public:
        Frame(const rt::Window &window) : targetTexture(window.renderer.makeTargetTexture(rt::Size{500, 300}))
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

        std::vector<std::unique_ptr<rt::RenderCommand>> getRenderCommands() const
        {
            std::vector<std::unique_ptr<rt::RenderCommand>> commands;
            commands.push_back(std::make_unique<rt::cmd::Clear>(SDL_Color{100, 25, 25, 255}));
            commands.push_back(std::make_unique<rt::cmd::Border>(SDL_Rect{0, 0, 100, 50}, 10, SDL_Color{125, 125, 125, 255}));
            return commands;
        }
    };
}