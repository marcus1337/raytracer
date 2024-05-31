#pragma once
#include "pch.h"
#include "Color.h"
#include "Data/Geometry/Size.h"

namespace rt
{
    class Canvas
    {
    public:
        Canvas(std::size_t width, std::size_t height) : width(width), height(height)
        {
            data.resize(width * height);
            clear(Color());
        }
        Canvas(const rt::Size &size) : Canvas(size.width, size.height)
        {
        }

        void clear(const Color &value)
        {
            for (std::size_t i = 0; i < data.size(); i++)
            {
                data[i] = value;
            }
        }

        std::size_t getWidth() const
        {
            return width;
        }

        std::size_t getHeight() const
        {
            return height;
        }

        Color at(std::size_t x, std::size_t y) const
        {
            return data.at(getIndex(x, y));
        }

        void set(std::size_t x, std::size_t y, Color value)
        {
            data[getIndex(x, y)] = value;
        }

    private:
        std::size_t width;
        std::size_t height;
        std::vector<Color> data;

        std::size_t getIndex(std::size_t x, std::size_t y) const
        {
            return y * width + x;
        }
    };

}