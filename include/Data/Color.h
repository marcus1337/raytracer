#pragma once
#include "pch.h"

namespace rt
{
    struct Color
    {
        uint8_t r, g, b;
        Color() : Color(0, 0, 0) {}
        Color(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue) {}
        Color(glm::vec3 scalarValues)
        {
            scalarValues = glm::clamp(scalarValues, 0.0f, 1.0f);
            r = toUint8(scalarValues.r);
            g = toUint8(scalarValues.g);
            b = toUint8(scalarValues.b);
        }

        uint8_t toUint8(float scalar) const
        {
            return static_cast<uint8_t>(scalar * 255.9999f);
        }
    };
}