#pragma once
#include "pch.h"
#include "Data/Canvas.h"
#include "Window/Window.h"
#include "Window/TargetTexture.h"
#include "Window/EventHandler.h"
#include "Window/Frame.h"

namespace rt
{
    class Loop
    {
    public:
        Loop() : frame(window)
        {
        }

        void run()
        {
            while (!eventHandler.hasQuit())
            {
                eventHandler.processEvents();
                frame.render(window.renderer, window.getSize());
                spdlog::log(spdlog::level::info, "WINDOW: {} {}", window.getWidth(), window.getHeight());
                sleep(1);
            }
        }

    private:
        rt::Window window;
        EventHandler eventHandler;
        Frame frame;
    };
}