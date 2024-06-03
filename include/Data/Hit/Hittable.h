#pragma once
#include "pch.h"
#include "Data/Tracing/Ray.h"
#include "Data/Hit/Interval.h"

namespace rt
{

    struct HitRecord
    {
        glm::vec3 p;
        glm::vec3 normal;
        float t;
        bool frontFace;

        void setFaceNormal(const Ray &r, const glm::vec3 &outwardNormal)
        {
            // Sets the hit record normal vector.
            // NOTE: the parameter `outward_normal` is assumed to have unit length.

            frontFace = glm::dot(r.direction(), outwardNormal) < 0;
            normal = frontFace ? outwardNormal : -outwardNormal;
        }
    };

    class Hittable
    {
    public:
        std::optional<HitRecord> hit(const Ray &r, const Interval &rT) const
        {
            const auto hitT = rT.getMinValidParameter(getIntersectionDistances(r));
            if (!hitT.has_value())
            {
                return std::nullopt;
            }
            return getHitRecord(r, hitT.value());
        }

        virtual ~Hittable() = default;

    private:
        HitRecord getHitRecord(const Ray &r, float t) const // t is guaranteed to be intersection time
        {
            HitRecord rec;
            rec.t = t;
            rec.p = r.at(rec.t);
            rec.setFaceNormal(r, getOutwardNormal(rec.p));
            return rec;
        }

        virtual glm::vec3 getOutwardNormal(const glm::vec3 &sp) const = 0; // sp is guaranteed to be a surface point
        virtual std::vector<float> getIntersectionDistances(const Ray &r) const = 0;
    };
}