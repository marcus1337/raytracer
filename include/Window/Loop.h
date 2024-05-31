#pragma once
#include "pch.h"
#include "Window/Window.h"
#include "Window/TargetTexture.h"
#include "Window/EventHandler.h"
#include "Window/Frame.h"
#include "Window/FrameTimeController.h"

namespace rt
{
    class Loop
    {
    public:
        Loop() : frame(window), frameTimeController(25)
        {
        }

        void run()
        {
            while (!eventHandler.hasQuit())
            {
                frameTimeController.beforeFrame();
                loopStep();
                frameTimeController.afterFrame();
            }
        }

    private:
        rt::Window window;
        EventHandler eventHandler;
        Frame frame;
        FrameTimeController frameTimeController;

        void loopStep()
        {
            eventHandler.processEvents();
            frame.render(window.renderer, window.getSize());
        }
    };
}