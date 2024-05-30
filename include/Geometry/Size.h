#pragma once
#include "pch.h"

namespace rt
{
    struct Size
    {
        int width;
        int height;
        Size() : width(0), height(0) {}
        Size(int width, int height) : width(width), height(height) {}
        Size(std::initializer_list<int> dimensions)
            : width(0), height(0)
        {
            auto it = dimensions.begin();
            if (it != dimensions.end())
            {
                width = *it++;
            }
            if (it != dimensions.end())
            {
                height = *it;
            }
        }

        double getRatio() const
        {
            return static_cast<double>(width) / static_cast<double>(height);
        }
    };
}