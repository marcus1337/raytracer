#pragma once
#include "pch.h"
#include "Data/Tracing/Ray.h"
#include "Data/Hit/Interval.h"
#include "Data/Hit/HitRecord.h"

namespace rt
{

    class Hittable
    {
    public:
        virtual std::optional<HitRecord> hit(const Ray &r, const Interval &rT) const = 0;
        virtual ~Hittable() = default;
    };

    class HittableObject : public Hittable
    {
    public:
        HittableObject(const Material& mat) : mat(mat)
        {

        }

        virtual std::optional<HitRecord> hit(const Ray &r, const Interval &rT) const override
        {
            const auto hitT = rT.getMinValidParameter(getIntersectionDistances(r));
            if (hitT.has_value())
            {
                return getHitRecord(r, hitT.value());
            }
            else
            {
                return std::nullopt;
            }
        }

        virtual ~HittableObject() = default;

    private:
        Material mat;

        HitRecord getHitRecord(const Ray &r, float t) const // t is guaranteed to be intersection time
        {
            HitRecord rec;
            auto &loc = rec.loc;
            rec.t = t;
            loc.p = r.at(rec.t);
            loc.setFaceNormal(r, getOutwardNormal(loc.p));
            rec.mat = mat;
            return rec;
        }

        virtual glm::vec3 getOutwardNormal(const glm::vec3 &sp) const = 0; // sp is guaranteed to be a surface point
        virtual std::vector<float> getIntersectionDistances(const Ray &r) const = 0;
    };
}