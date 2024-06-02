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
            camera = std::make_unique<PerspectiveCamera>(canvasSize, 90.0f);
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

        bool hitSphere(const glm::vec3 center, float radius, const Ray &r) const
        {
            glm::vec3 oc = center - r.origin();
            auto a = glm::dot(r.direction(), r.direction());
            auto b = -2.0 * glm::dot(r.direction(), oc);
            auto c = glm::dot(oc, oc) - radius * radius;
            auto discriminant = b * b - 4 * a * c;
            return (discriminant >= 0);
        }

        Color backgroundColor(const Ray &ray) const
        {
            if (hitSphere(glm::vec3(0, 0, -1.5f), 0.5f, ray))
                return Color(glm::vec3(1.0f, 0, 0));

            const auto rayDir = glm::normalize(ray.direction());
            glm::vec3 c1(1.0f, 1.0f, 1.0f);
            glm::vec3 c2(0.5f, 0.7f, 1.0f);
            auto a = 0.5f * (rayDir.y + 1.0f);
            glm::vec3 colorScalar = (1.0f - a) * c1 + a * c2;
            return Color(colorScalar);
        }
    };
}