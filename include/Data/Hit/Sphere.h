#pragma once
#include "pch.h"

namespace rt
{
    class Sphere
    {
    public:
        Sphere(const glm::vec3 &center, float radius) : center(center), radius(radius)
        {
        }

    public:
        glm::vec3 center;
        float radius;

        glm::vec3 getOutwardNormal(const glm::vec3 &sp) const
        {
            return (sp - center) / radius;
        }

        std::vector<float> getIntersectionDistances(const Ray &r) const
        {
            std::vector<float> dists;

            glm::vec3 oc = center - r.origin();
            auto a = glm::length2(r.direction());
            auto h = glm::dot(r.direction(), oc);
            auto c = glm::length2(oc) - radius * radius;
            auto discriminant = h * h - a * c;

            if (discriminant >= 0)
            {
                auto sqrtd = glm::sqrt(discriminant);
                auto root1 = (h - sqrtd) / a;
                auto root2 = (h + sqrtd) / a;
                dists.push_back(root1);
                if (sqrtd != 0)
                {
                    dists.push_back(root2);
                }
            }

            return dists;
        }
        };
}