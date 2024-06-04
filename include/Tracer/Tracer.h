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
                const auto &loc = rec->loc;
                auto scat = rec->mat->scatter(r, rec->loc);
                if (scat.has_value())
                {
                    return scat->attenuation * getRayColorScalar(scat->r, world, depth - 1);
                }
                else
                {
                    return glm::vec3(0, 0, 0);
                }
            }

            return background.getColorScalar(r);
        }

        glm::vec3 getNormalColorScalar(const glm::vec3 &normal) const
        {
            return 0.5f * (normal + glm::vec3(1.0f));
        }

        Interval getStartInterval() const
        {
            return Interval(0.001f, std::numeric_limits<float>::max());
        }
    };
}