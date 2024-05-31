#pragma once
#include "pch.h"
#include "Data/Canvas.h"
#include "Window/Window.h"
#include "Render/Commands/Clear.h"
#include "Render/Commands/Border.h"
#include "Window/TargetTexture.h"
#include "EventHandler.h"

namespace rt
{
    class Loop
    {
    public:
        Loop()
        {
        }

        void run()
        {
            Window window;
            window.renderer.addCommands(getRenderCommands());
            auto targetTexture = window.renderer.makeTargetTexture(rt::Size{500, 300});
            while (!eventHandler.hasQuit())
            {
                eventHandler.processEvents();
                spdlog::log(spdlog::level::info, "WINDOW: {} {}", window.getWidth(), window.getHeight());
                window.renderer.render(targetTexture, window.getSize());
                sleep(1);
            }
        }

    private:
        EventHandler eventHandler;

        bool handleEvents()
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    return false;
                }
            }
            return true;
        }

        std::vector<std::unique_ptr<rt::RenderCommand>> getRenderCommands()
        {
            std::vector<std::unique_ptr<rt::RenderCommand>> commands;
            commands.push_back(std::make_unique<rt::cmd::Clear>(SDL_Color{100, 25, 25, 255}));
            commands.push_back(std::make_unique<rt::cmd::Border>(SDL_Rect{0, 0, 100, 50}, 10, SDL_Color{125, 125, 125, 255}));
            return commands;
        }
    };
}