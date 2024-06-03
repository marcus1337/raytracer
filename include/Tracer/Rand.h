#pragma once
#include "pch.h"

namespace rt
{
    class Rand
    {
    public:
        Rand() : gen(rd())
        {
        }

        float getFloat()
        {
            return getFloat(0.f, 1.0f);
        }

        float getFloat(float min, float max)
        {
            std::uniform_real_distribution<> dist(min, max);
            return dist(gen);
        }

    private:
        std::random_device rd;
        std::mt19937 gen;
    };
}