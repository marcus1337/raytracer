#pragma once
#include "pch.h"

namespace rt
{
    struct Color
    {
        uint8_t r, g, b;
        Color() : Color(0, 0, 0) {}
        Color(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue) {}
        std::string toString() const
        {
            std::ostringstream oss;
            oss << "(" << static_cast<int>(r) << ", "
                << static_cast<int>(g) << ", "
                << static_cast<int>(b) << ")";
            return oss.str();
        }
    };
}