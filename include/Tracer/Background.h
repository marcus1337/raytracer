#pragma once
#include "pch.h"
#include "Data/Tracing/Ray.h"
#include "Data/Color.h"

namespace rt
{
    class Background
    {
    public:
        Color getColor(const Ray &r) const
        {
            const auto rayDir = glm::normalize(r.direction());
            glm::vec3 c1(1.0f, 1.0f, 1.0f);
            glm::vec3 c2(0.5f, 0.7f, 1.0f);
            auto a = 0.5f * (rayDir.y + 1.0f);
            glm::vec3 colorScalar = (1.0f - a) * c1 + a * c2;
            return Color(colorScalar);
        }

    private:
    };
}