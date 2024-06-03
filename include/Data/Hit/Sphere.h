#pragma once
#include "pch.h"
#include "Hittable.h"

namespace rt
{
    class Sphere : public Hittable
    {
    public:
        virtual std::optional<HitRecord> hit(const Ray &r, const Interval &rT) const override
        {

            return std::nullopt;
        }

    private:
    };
}