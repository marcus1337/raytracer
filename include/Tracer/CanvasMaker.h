#pragma once
#include "pch.h"
#include "Data/Transform.h"
#include "Data/Tracing/Ray.h"
#include "Data/Geometry/Size.h"
#include "Data/Geometry/Point.h"
#include "Data/Tracing/Camera.h"
#include "Tracer/RaySpawner.h"
#include "Data/Canvas.h"

namespace rt
{
    class CanvasMaker
    {
    public:
        CanvasMaker(const Size &canvasSize)
        {
            camera = std::make_unique<PerspectiveCamera>(canvasSize, 45.0f);
        }

        Canvas makeCanvas() const
        {
            Canvas canvas(camera->getViewSize());
            for (const auto &pixelRay : RaySpawner().getPixelRays(*camera.get()))
            {
                canvas.set(pixelRay.first, backgroundColor(pixelRay.second));
            }
            return canvas;
        }

    private:
        std::unique_ptr<Camera> camera;

        Color backgroundColor(const Ray &ray) const
        {
            const auto rayDir = glm::normalize(ray.direction());
            glm::vec3 c1(1.0f, 1.0f, 1.0f);
            glm::vec3 c2(0.5f, 0.7f, 1.0f);
            auto a = 0.5f * (rayDir.y + 1.0f);
            glm::vec3 colorScalar = (1.0f - a) * c1 + a * c2;
            return Color(colorScalar);
        }
    };
}