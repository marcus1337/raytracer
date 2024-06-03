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
            const auto hitT = rT.getMinValidParameter(getIntersectionDistances(r));
            if (!hitT.has_value())
            {
                return std::nullopt;
            }
            return getHitRecord(r, hitT.value());
        }

    private:
        glm::vec3 center;
        float radius;

        HitRecord getHitRecord(const Ray &r, float t) const // t is guaranteed to be intersection time
        {
            HitRecord rec;
            rec.t = t;
            rec.p = r.at(rec.t);
            rec.setFaceNormal(r, getOutwardNormal(rec.p));
            return rec;
        }

        glm::vec3 getOutwardNormal(const glm::vec3 &sp) const // sp is guaranteed to be a surface point
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