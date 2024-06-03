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
            for (const auto &pixelRay : raySpawner.getPixelRays(*camera.get()))
            {
                auto color = Color(getRayColorScalar(pixelRay.second));
                canvas.set(pixelRay.first, color);
            }
            return canvas;
        }

    private:
        RaySpawner raySpawner;
        std::unique_ptr<Camera> camera;
        World world;
        Background background;

        glm::vec3 getRayColorScalar(const Ray &r) const
        {
            auto rec = world.hit(r, getStartInterval());
            if (rec.has_value())
            {
                return getNormalColorScalar(rec.value().normal);
            }
            return background.getColorScalar(r);
        }

        glm::vec3 getNormalColorScalar(const glm::vec3 &normal) const
        {
            return 0.5f * (normal + glm::vec3(1.0f));
        }

        Interval getStartInterval() const
        {
            return Interval(0, std::numeric_limits<float>::max());
        }
    };
}