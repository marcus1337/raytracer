#pragma once
#include "pch.h"
#include "Data/Transform.h"
#include "Data/Tracing/Ray.h"
#include "Data/Geometry/Size.h"
#include "Data/Geometry/Point.h"
#include "Data/Tracing/Camera.h"
#include "Tracer/Rand.h"

namespace rt
{
    class RaySpawner
    {
    public:
        RaySpawner()
        {
        }

        std::vector<std::pair<Point, Ray>> getPixelRays(const Camera &camera) const
        {
            const auto &viewSize = camera.getViewSize();
            std::vector<std::pair<Point, Ray>> pixelRays;
            for (const auto &p : getPixelIndices(viewSize))
            {
                const auto uv = getUVPoint(p, viewSize);
                const auto ray = camera.spawnRay(uv.x, uv.y);
                pixelRays.push_back({p, ray});
            }
            return pixelRays;
        }

        std::vector<std::pair<Point, Ray>> getPixelSampleRays(const Camera &camera) const
        {
            const auto &viewSize = camera.getViewSize();
            std::vector<std::pair<Point, Ray>> pixelRays;
            for (const auto &p : getPixelIndices(viewSize))
            {
                for (int i = 0; i < samplesPerPixel; i++)
                {
                    const auto uv = getUVPointSample(p, viewSize);
                    const auto ray = camera.spawnRay(uv.x, uv.y);
                    pixelRays.push_back({p, ray});
                }
            }
            return pixelRays;
        }

        void setSamplesPerPixel(int value)
        {
            samplesPerPixel = value;
        }

        int getSamplesPerPixel() const
        {
            return samplesPerPixel;
        }

    private:
        mutable Rand rand;
        int samplesPerPixel = 10;

        std::vector<Point> getPixelIndices(const Size &size) const
        {
            std::vector<Point> points;
            for (int x = 0; x < size.width; x++)
            {
                for (int y = 0; y < size.height; y++)
                {
                    points.push_back(Point(x, y));
                }
            }
            return points;
        }

        glm::vec2 getUVOffsetPointSample() const
        {
            float maxValue = 0.005f;
            return glm::vec2(rand.getFloat(0, maxValue) - maxValue, rand.getFloat(0, maxValue) - maxValue);
        }

        glm::vec2 getUVPointSample(const Point &p, const Size &size) const
        {
            return getUVPoint(p, size) + getUVOffsetPointSample();
        }

        glm::vec2 getUVPoint(const Point &p, const Size &size) const
        {
            const float pixelDeltaU = (1.0f / size.width);
            const float pixelDeltaV = (1.0f / size.height);
            float u = pixelDeltaU * p.x;
            float v = pixelDeltaV * p.y;
            return glm::vec2(u, v) + glm::vec2(pixelDeltaU, pixelDeltaV) / 2.0f;
        }
    };
}