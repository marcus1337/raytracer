#pragma once
#include "pch.h"
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
                sleep(1);
            }
        }

    private:
        rt::Window window;
        EventHandler eventHandler;
        Frame frame;
    };
}