#pragma once
#include "pch.h"
#include "Data/Transform.h"
#include "Data/Tracing/Ray.h"
#include "Data/Geometry/Size.h"
#include "Data/Geometry/Point.h"
#include "Data/Tracing/Camera.h"
#include "Tracer/UV.h"

namespace rt
{
    class RaySpawner
    {
    public:
        RaySpawner()
        {
        }

        Ray getSampleRay(const Point &p, const Camera &camera) const
        {
            return camera.spawnRay(UV(camera.getViewSize()).getUVCenter(p));
        }

        std::vector<Ray> getRaysStratified(const Point &p, const Camera &camera, const Size &strataSize) const
        {
            std::vector<Ray> rays;
            UV uvHandler(camera.getViewSize());
            for (const auto &uv : uvHandler.getUVStratifiedCenters(p, strataSize))
            {
                rays.push_back(camera.spawnRay(uv));
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
    };
}