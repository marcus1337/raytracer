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

namespace rt
{
    class CanvasMaker
    {
    public:
        CanvasMaker(const Size &canvasSize)
        {
            camera = std::make_unique<PerspectiveCamera>(canvasSize, 90.0f);
            world.add(std::make_unique<Sphere>(glm::vec3(0, 0, -1.5f), 0.5f));
            world.add(std::make_unique<Sphere>(glm::vec3(0, -100.5, -1.5f), 100.0f));
        }

        Canvas makeCanvas() const
        {
            Canvas canvas(camera->getViewSize());
            for (const auto &pair : raySpawner.getPixelRays(*camera))
            {
                auto color = Color(tracer.getRayColorScalar(pair.second, world));
                canvas.set(pair.first, color);
            }
            return canvas;
        }

        Canvas makeCanvasAntialiased() const
        {
            CanvasScalar canvasScalar(camera->getViewSize());
            for (const auto &pair : raySpawner.getPixelSampleRays(*camera))
            {
                auto colorScalar = tracer.getRayColorScalar(pair.second, world);
                canvasScalar.add(pair.first, colorScalar);
            }
            return canvasScalar.getCanvas();
        }

    private:
        RaySpawner raySpawner;
        std::unique_ptr<Camera> camera;
        World world;
        Tracer tracer;
    };
}