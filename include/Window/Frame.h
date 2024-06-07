#pragma once
#include "pch.h"
#include "Render/Renderer.h"
#include "Render/Commands/Clear.h"
#include "Render/Commands/Border.h"
#include "Render/Commands/Pixels.h"
#include "Window/Window.h"

#include "Data/Tracing/Camera.h"
#include "Tracer/CanvasMaker.h"

namespace rt
{
    class Frame
    {
    public:
        Frame(const rt::Window &window) : targetTexture(window.renderer.makeTargetTexture(Size{420, 245})), canvasMaker(getCanvasSize())
        {
            canvasMaker.setWorld(WorldMaker().makeWorld());
        }

        void addSamples()
        {
            canvasMaker.sampleCanvas();
        }

        void render(Renderer &renderer, const rt::Size &windowSize) const
        {
            setCommands(renderer);
            renderer.render(targetTexture, windowSize);
        }

        Transform getCameraTransform() const
        {
            return canvasMaker.getCameraTransform();
        }

        void setCameraTransform(const Transform &transform)
        {
            canvasMaker.setCameraTransform(transform);
        }

    private:
        static constexpr int borderThickness = 10;
        TargetTexture targetTexture;
        CanvasMaker canvasMaker;

        Size getCanvasSize() const
        {
            Size canvasSize = targetTexture.getSize();
            canvasSize.width -= borderThickness * 2;
            canvasSize.height -= borderThickness * 2;
            return canvasSize;
        }

        void setCommands(Renderer &renderer) const
        {
            renderer.clearCommands();
            renderer.addCommands(getRenderCommands());
        }

        std::unique_ptr<rt::RenderCommand> makeBorderCommand() const
        {
            const auto color = SDL_Color{125, 125, 125, 255};
            const auto rect = SDL_Rect{0, 0, targetTexture.getWidth(), targetTexture.getHeight()};
            return std::make_unique<rt::cmd::Border>(rect, borderThickness, color);
        }

        std::unique_ptr<rt::RenderCommand> makeClearCommand() const
        {
            return std::make_unique<rt::cmd::Clear>(SDL_Color{100, 25, 25, 255});
        }

        std::unique_ptr<rt::RenderCommand> makePixelsCommand() const
        {
            return std::make_unique<rt::cmd::Pixels>(canvasMaker.makeCanvasAntialiased(), Point{10, 10});
        }

        std::vector<std::unique_ptr<rt::RenderCommand>> getRenderCommands() const
        {
            std::vector<std::unique_ptr<rt::RenderCommand>> commands;
            commands.push_back(makeClearCommand());
            commands.push_back(makeBorderCommand());
            commands.push_back(makePixelsCommand());
            return commands;
        }
    };
}