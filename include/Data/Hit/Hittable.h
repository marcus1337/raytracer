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
        virtual std::optional<HitRecord> hit(const Ray &r, const Interval &rT) const = 0;

    private:
    };
}