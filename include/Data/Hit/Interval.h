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

        static Interval fuse(const Interval &a, const Interval &b)
        {
            float maxValue = std::max(a.max, b.max);
            float minValue = std::min(a.min, b.min);
            return Interval(minValue, maxValue);
        }

        std::optional<float> getMinValidParameter(const std::vector<float> &parameters) const
        {
            // Assumes parameters are stored in ASCENDING order.
            for (const auto &param : parameters)
            {
                if (contains(param))
                {
                    return param;
                }
            }

            return std::nullopt;
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