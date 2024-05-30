#include "pch.h"

namespace rt
{
    struct Pixel
    {
        uint8_t r, g, b;
        Pixel() : Pixel(0, 0, 0) {}
        Pixel(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue) {}
    };
}