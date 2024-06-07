#pragma once
#include "pch.h"
#include "Color.h"
#include "Data/Canvas.h"
#include "Data/Geometry/Point.h"

namespace rt
{
    class CanvasScalar
    {
    public:
        CanvasScalar() = default;
        CanvasScalar(std::size_t width, std::size_t height) : width(width), height(height)
        {
            numSamples.resize(width * height, 0);
            values.resize(width * height, glm::vec3(0.0f));
        }
        CanvasScalar(const rt::Size &size) : CanvasScalar(size.width, size.height)
        {
        }

        void clear()
        {
            for (std::size_t i = 0; i < values.size(); i++)
            {
                values[i] = glm::vec3(0.0f);
                numSamples[i] = 0;
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
            return Color(values.at(getIndex(x, y)));
        }

        Color at(const rt::Point &point) const
        {
            return at(point.x, point.y);
        }

        void add(std::size_t x, std::size_t y, const glm::vec3 &scalar)
        {
            const auto index = getIndex(x, y);
            numSamples[index] += 1;
            values[index] = (values[index] * (numSamples[index] - 1) + scalar) / numSamples[index];
        }

        void add(const Point &p, const glm::vec3 &scalar)
        {
            add(p.x, p.y, scalar);
        }

        Canvas getCanvas() const
        {
            Canvas canvas(width, height);
            for (const auto &p : getIndices())
            {
                canvas.set(p, at(p));
            }
            return canvas;
        }

        std::vector<Point> getIndices() const
        {
            std::vector<Point> indices;
            for (std::size_t x = 0; x < getWidth(); x++)
            {
                for (std::size_t y = 0; y < getHeight(); y++)
                {
                    indices.push_back(Point(x, y));
                }
            }
            return indices;
        }

    private:
        std::size_t width;
        std::size_t height;
        std::vector<glm::vec3> values;
        std::vector<unsigned int> numSamples;

        std::size_t getIndex(std::size_t x, std::size_t y) const
        {
            return y * width + x;
        }
    };

}