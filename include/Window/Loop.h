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

            const int targetFPS = 25;
            const std::chrono::duration<double> frameDuration(1.0 / targetFPS);

            while (!eventHandler.hasQuit())
            {

                auto frameStart = std::chrono::high_resolution_clock::now();

                loopStep();

                auto frameEnd = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsedTime = frameEnd - frameStart;
                if (elapsedTime < frameDuration)
                {
                    std::this_thread::sleep_for(frameDuration - elapsedTime);
                }
            }
        }

    private:
        rt::Window window;
        EventHandler eventHandler;
        Frame frame;

        void loopStep()
        {
            eventHandler.processEvents();
            frame.render(window.renderer, window.getSize());
        }
    };
}