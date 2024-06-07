#pragma once
#include "pch.h"
#include "Data/Hit/Hittable.h"

namespace rt
{
    class HittableObject : public Hittable
    {
    public:
        HittableObject(const Material &mat);
        virtual ~HittableObject() = default;
        virtual std::optional<HitRecord> hit(const Ray &r, const Interval &rT) const override;

    private:
        Material mat;
        HitRecord getHitRecord(const Ray &r, float t) const;
        virtual glm::vec3 getOutwardNormal(const glm::vec3 &sp) const = 0; // sp is guaranteed to be a surface point
        virtual std::vector<float> getIntersectionDistances(const Ray &r) const = 0;
    };
}