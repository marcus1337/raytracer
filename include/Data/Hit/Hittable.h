#pragma once
#include "pch.h"
#include "Data/Tracing/Ray.h"
#include "Data/Hit/Interval.h"
#include "Data/Hit/HitRecord.h"
#include "Data/AABB.h"

namespace rt
{
    class Hittable
    {
    public:
        virtual std::optional<HitRecord> hit(const Ray &r, const Interval &rT) const = 0;
        virtual ~Hittable() = default;
    };
}