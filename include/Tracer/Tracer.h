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
            auto rec = world.hit(r, getStartInterval());
            if (rec.has_value())
            {
                return getNormalColorScalar(rec.value().normal);
            }
            return background.getColorScalar(r);
        }

    private:
        Background background;

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