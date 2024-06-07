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
        Loop() : frame(window), renderTimeController(25), eventTimeController(60)
        {
            Transform t;
            frame.setCameraTransform(t);
        }

        void run()
        {
            while (!eventHandler.hasQuit())
            {
                loopStep();
            }
        }

    private:
        rt::Window window;
        EventHandler eventHandler;
        Frame frame;
        FrameTimeController renderTimeController;
        FrameTimeController eventTimeController;

        void handleEvents()
        {
            if (eventTimeController.shouldUpdate())
            {
                eventTimeController.beforeFrame();
                eventHandler.processEvents();
                eventTimeController.afterFrame();
            }
        }

        void render()
        {
            if (renderTimeController.shouldUpdate())
            {
                renderTimeController.beforeFrame();
                frame.addSamples();
                frame.render(window.renderer, window.getSize());
                renderTimeController.afterFrame();
                renderTimeController.delay();
            }
        }

        void loopStep()
        {
            handleEvents();
            render();
        }
    };
}