#pragma once
#include "pch.h"
#include "Data/Transform.h"
#include "Data/Tracing/Ray.h"
#include "Data/Geometry/Size.h"
#include "Data/Geometry/Point.h"
#include "Data/Tracing/Camera.h"
#include "Tracer/RaySpawner.h"
#include "Data/Canvas.h"
#include "Tracer/World.h"
#include "Tracer/Background.h"
#include "Data/CanvasScalar.h"
#include "Tracer/Tracer.h"
#include "Tracer/WorldMaker.h"

namespace rt
{
    class CanvasMaker
    {
    public:
        CanvasMaker(const Size &canvasSize)
        {
            camera = std::make_unique<PerspectiveCamera>(canvasSize, 90.0f);
        }

        Canvas makeCanvas(const World &world) const
        {
            return makeCanvas(world, raySpawner.getPixelRays(*camera));
        }

        Canvas makeCanvasAntialiased(const World &world) const
        {
            return makeCanvas(world, raySpawner.getPixelSampleRays(*camera));
        }

    private:
        std::unique_ptr<Camera> camera;
        RaySpawner raySpawner;
        Tracer tracer;

        Canvas makeCanvas(const World &world, const std::vector<std::pair<Point, Ray>> &pixelRayPairs) const
        {
            CanvasScalar canvasScalar(camera->getViewSize());
            for (const auto &pair : pixelRayPairs)
            {
                auto colorScalar = tracer.getRayColorScalar(pair.second, world);
                canvasScalar.add(pair.first, colorScalar);
            }
            return canvasScalar.getCanvas();
        }
    };
}