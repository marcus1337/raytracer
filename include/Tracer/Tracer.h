#pragma once
#include "pch.h"
#include "Data/Tracing/Ray.h"
#include "Data/Color.h"
#include "RayRand.h"

namespace rt
{
    class Tracer
    {
    public:
        glm::vec3 getRayColorScalar(const Ray &r, const World &world) const
        {
            return getRayColorScalar(r, world, maxDepth);
        }

    private:
        Background background;
        mutable RayRand rayRand;
        int maxDepth = 50;

        glm::vec3 getRayColorScalar(const Ray &r, const World &world, int depth) const
        {
            if (depth <= 0)
            {
                return glm::vec3(0);
            }

            auto rec = world.hit(r, getStartInterval());
            if (rec.has_value())
            {
                const auto recVal = rec.value();
                auto dir = rayRand.randOnHemisphere(recVal.normal);
                return 0.5f * getRayColorScalar(Ray(recVal.p, dir), world, depth - 1);
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