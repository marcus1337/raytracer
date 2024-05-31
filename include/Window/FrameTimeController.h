#pragma once
#include "pch.h"

namespace rt
{
    class FrameTimeController
    {
    public:
        explicit FrameTimeController(int targetFPS)
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
        }

        bool shouldUpdate() const
        {
            auto now = std::chrono::high_resolution_clock::now();
            return now - frameEndTime >= frameDuration;
        }

        void delay() const
        {
            std::chrono::duration<double> elapsedTime = frameEndTime - frameStartTime;
            if (elapsedTime < frameDuration)
            {
                std::this_thread::sleep_for(frameDuration - elapsedTime);
            }
        }

    private:
        std::chrono::duration<double> frameDuration;
        std::chrono::_V2::system_clock::time_point frameStartTime, frameEndTime;
    };
}