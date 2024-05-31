#pragma once
#include "pch.h"

namespace rt
{
    class FrameTimeController
    {
    public:
        FrameTimeController(int targetFPS) : targetFPS(targetFPS)
        {
            frameDuration = std::chrono::duration<double>(1.0 / targetFPS);
        }

        void beforeFrame()
        {
            frameStartTime = std::chrono::high_resolution_clock::now();
        }

        void afterFrame()
        {
            frameEndTime = std::chrono::high_resolution_clock::now();
            delay();
        }

    private:
        int targetFPS;
        std::chrono::duration<double> frameDuration;
        std::chrono::_V2::system_clock::time_point frameStartTime, frameEndTime;

        void delay()
        {
            std::chrono::duration<double> elapsedTime = frameEndTime - frameStartTime;
            if (elapsedTime < frameDuration)
            {
                std::this_thread::sleep_for(frameDuration - elapsedTime);
            }
        }
    };
}