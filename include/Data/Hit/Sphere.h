#pragma once
#include "pch.h"
#include "Hittable.h"

namespace rt
{
    class Sphere : public Hittable
    {
    public:
        Sphere(const glm::vec3 &center, float radius) : center(center), radius(radius)
        {
        }

        virtual std::optional<HitRecord> hit(const Ray &r, const Interval &rT) const override
        {
            glm::vec3 oc = center - r.origin();
            auto a = glm::length2(r.direction());
            auto h = glm::dot(r.direction(), oc);
            auto c = glm::length2(oc) - radius * radius;
            auto discriminant = h * h - a * c;

            if (discriminant < 0)
            {
                return std::nullopt;
                ;
            }

            auto sqrtd = glm::sqrt(discriminant);
            auto root = (h - sqrtd) / a;
            if (!rT.contains(root))
            {
                root = (h + sqrtd) / a;
                if (!rT.contains(root))
                    return std::nullopt;
            }

            HitRecord rec;
            rec.t = root;
            rec.p = r.at(rec.t);
            glm::vec3 outwardNormal = (rec.p - center) / radius;
            rec.setFaceNormal(r, outwardNormal);
            return rec;
        }

    private:
        glm::vec3 center;
        float radius;
    };
}