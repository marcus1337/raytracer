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
            scalarArrays.resize(width * height);
            clear(Color());
        }
        CanvasScalar(const rt::Size &size) : CanvasScalar(size.width, size.height)
        {
        }

        void clear(const Color &value)
        {
            for (std::size_t i = 0; i < scalarArrays.size(); i++)
            {
                scalarArrays[i].clear();
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
            glm::vec3 accumulatedScalar(0.0f);
            const auto &scalars = scalarArrays.at(getIndex(x, y));
            if (scalars.empty())
            {
                return glm::vec3(0);
            }
            for (const auto &scalar : scalars)
            {
                accumulatedScalar += scalar;
            }
            return Color(accumulatedScalar / scalars.size());
        }

        Color at(const rt::Point &point) const
        {
            return at(point.x, point.y);
        }

        void add(std::size_t x, std::size_t y, const glm::vec3 &scalar)
        {
            scalarArrays[getIndex(x, y)].push_back(scalar);
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
        std::vector<std::vector<glm::vec3>> scalarArrays;

        std::size_t getIndex(std::size_t x, std::size_t y) const
        {
            return y * width + x;
        }
    };

}