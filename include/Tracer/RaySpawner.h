#pragma once
#include "pch.h"
#include "Data/Transform.h"
#include "Data/Tracing/Ray.h"
#include "Data/Geometry/Size.h"
#include "Data/Geometry/Point.h"
#include "Data/Tracing/Camera.h"

namespace rt
{
    class RaySpawner
    {
    public:
        std::vector<Ray> spawnRays(const Camera &camera, const Size &canvasSize) const
        {
            assert(canvasSize.width > 1);
            assert(canvasSize.height > 1);
            std::vector<Ray> rays;
            for (const auto &uv : getUVPoints(canvasSize))
            {
                rays.push_back(camera.spawnRay(uv.x, uv.y));
            }
            return rays;
        }

    private:
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

        std::vector<glm::vec2> getUVPoints(const Size &canvasSize) const
        {
            std::vector<glm::vec2> uvPoints;
            for (const auto &p : getPixelIndices(canvasSize))
                uvPoints.push_back(getUVPoint(p, canvasSize));
            return uvPoints;
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