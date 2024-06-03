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

        float hitSphere(const glm::vec3 center, float radius, const Ray &r) const
        {
            glm::vec3 oc = center - r.origin();
            auto a = glm::length2(r.direction());
            auto h = glm::dot(r.direction(), oc);
            auto c = glm::length2(oc) - radius * radius;
            auto discriminant = h * h - a * c;

            if (discriminant < 0)
            {
                return -1.0f;
            }
            else
            {
                return (h - glm::sqrt(discriminant)) / a;
            }
        }

        Color backgroundColor(const Ray &ray) const
        {
            auto spherePos = glm::vec3(0, 0, -1.5f);
            float radius = 0.5f;
            auto t = hitSphere(spherePos, radius, ray);
            if (t > 0.0)
            {
                glm::vec3 N = glm::normalize(ray.at(t) - spherePos);
                auto colorScalar = radius * (N + glm::vec3(1.0f));
                return Color(colorScalar);
            }

            const auto rayDir = glm::normalize(ray.direction());
            glm::vec3 c1(1.0f, 1.0f, 1.0f);
            glm::vec3 c2(0.5f, 0.7f, 1.0f);
            auto a = 0.5f * (rayDir.y + 1.0f);
            glm::vec3 colorScalar = (1.0f - a) * c1 + a * c2;
            return Color(colorScalar);
        }
    };
}