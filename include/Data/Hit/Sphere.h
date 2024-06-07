#pragma once
#include "pch.h"
#include "Hittable.h"
#include "HittableObject.h"

namespace rt
{
    class Sphere : public HittableObject
    {
    public:
        Sphere(const glm::vec3 &center, float radius, const Material& mat) : HittableObject(mat), center(center), radius(radius)
        {
        }

    private:
        glm::vec3 center;
        float radius;

        virtual glm::vec3 getOutwardNormal(const glm::vec3 &sp) const override
        {
            return (sp - center) / radius;
        }

        virtual std::vector<float> getIntersectionDistances(const Ray &r) const override
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