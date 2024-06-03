#pragma once
#include "pch.h"
#include "Data/Hit/Hittable.h"
#include "Data/Hit/Sphere.h"

namespace rt
{
    class World : public Hittable
    {
    public:
        World()
        {
        }

        void add(std::unique_ptr<Hittable> hittable)
        {
            hittables.push_back(std::move(hittable));
        }

        void clear()
        {
            hittables.clear();
        }

        virtual std::optional<HitRecord> hit(const Ray &r, const Interval &rT) const override
        {
            std::optional<HitRecord> rec;
            for (const auto &hittable : hittables)
            {
                auto closestHit = rec.has_value() ? rec.value().t : rT.getMax();
                auto tmpRec = hittable->hit(r, Interval(rT.getMin(), closestHit));
                if (tmpRec.has_value())
                {
                    rec = tmpRec;
                }
            }
            return rec;
        }

    private:
        std::vector<std::unique_ptr<Hittable>> hittables;
    };
}