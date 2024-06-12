#pragma once
#include "pch.h"

namespace rt
{
    struct Point
    {
        int x, y;
        Point() : x(0), y(0) {}
        Point(const Point &point) : x(point.x), y(point.y) {}
        Point(int x, int y) : x(x), y(y)
        {
        }

        bool operator<(const Point &p) const
        {
            if (x == p.x)
                return y < p.y;
            return x < p.x;
        }

        bool operator==(const Point &p) const
        {
            return x == p.x && y == p.y;
        }
        Point operator+(const Point &p) const
        {
            return {x + p.x, y + p.y};
        }
        Point operator-(const Point &p) const
        {
            return {x - p.x, y - p.y};
        }
        Point &operator-=(const Point &p)
        {
            *this = *this - p;
            return *this;
        }
        Point &operator*=(const float &f)
        {
            x = (int)(x * f);
            y = (int)(y * f);
            return *this;
        }

        static Point lerp(const Point &a, const Point &b, float t)
        {
            float xDiff = static_cast<float>(b.x - a.x);
            float yDiff = static_cast<float>(b.y - a.y);
            int newX = std::round(static_cast<float>(a.x) + t * xDiff);
            int newY = std::round(static_cast<float>(a.y) + t * yDiff);
            return Point(newX, newY);
        }
    };
}