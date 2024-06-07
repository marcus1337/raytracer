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

        void handleMoves()
        {
            float xMov = eventHandler.getXMov();
            float zMov = eventHandler.getZMov();
            if (xMov != 0 || zMov != 0)
            {
                auto tmp = frame.getCameraTransform();
                tmp.move(xMov, zMov);
                frame.setCameraTransform(tmp);
            }
            float yaw = eventHandler.getYawMove();
            float pitch = eventHandler.getPitchMove();
            if (yaw != 0 || pitch != 0)
            {
                auto tmp = frame.getCameraTransform();
                tmp.addRotation(yaw, pitch);
                frame.setCameraTransform(tmp);
            }
        }

        void handleEvents()
        {
            if (eventTimeController.shouldUpdate())
            {
                eventTimeController.beforeFrame();
                handleMoves();
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