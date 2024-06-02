#pragma once
#include "pch.h"
#include "Data/Transform.h"
#include "Data/Tracing/Ray.h"
#include "Data/Geometry/Size.h"
#include "Data/Tracing/Camera.h"

namespace rt
{
    class RaySpawn
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
        std::vector<glm::vec2> getUVPoints(const Size &canvasSize) const
        {
            std::vector<glm::vec2> points;
            const auto w = canvasSize.width;
            const auto h = canvasSize.height;
            for (int x = 0; x < w; x++)
            {
                for (int y = 0; y < h; y++)
                {
                    float u = static_cast<float>(x) / (w - 1);
                    float v = static_cast<float>(y) / (h - 1);
                    points.push_back(glm::vec2(u, v));
                }
            }

            return points;
        }
    };
}