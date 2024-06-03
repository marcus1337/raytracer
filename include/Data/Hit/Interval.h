#pragma once
#include "pch.h"

namespace rt
{
    class Interval
    {
    public:
        Interval() : min(std::numeric_limits<float>::min()), max(std::numeric_limits<float>::max())
        {
        }

        Interval(float min, float max) : min(min), max(max)
        {
        }

        bool isEmpty() const
        {
            return max < min;
        }

        bool isFullRange() const
        {
            return min == std::numeric_limits<float>::min() && max == std::numeric_limits<float>::max();
        }

        float getSize() const
        {
            return max - min;
        }

        bool contains(float x) const
        {
            return min <= x && x <= max;
        }

        bool surrounds(float x) const
        {
            return min < x && x < max;
        }

        float getMin() const
        {
            return min;
        }

        float getMax() const
        {
            return max;
        }

    private:
        float min, max;
    };
}