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
            r = static_cast<uint8_t>(scalarValues.r * 255.0f);
            g = static_cast<uint8_t>(scalarValues.g * 255.0f);
            b = static_cast<uint8_t>(scalarValues.b * 255.0f);
        }
    };
}