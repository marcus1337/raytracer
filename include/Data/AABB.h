#pragma once
#include "pch.h"
#include "Data/Geometry/Point.h"
#include "Data/Geometry/Size.h"
#include "Data/Tracing/Ray.h"
#include "Data/Hit/Interval.h"

namespace rt
{
    class AABB
    {

    public:
        AABB()
        {
        }

        AABB(const Interval &a, const Interval &b, const Interval &c)
            : a(a), b(b), c(c)
        {
        }

        AABB(const glm::vec3 &minPoint, const glm::vec3 &maxPoint)
            : a(minPoint.x, maxPoint.x), b(minPoint.y, maxPoint.y), c(minPoint.z, maxPoint.z)
        {
        }

        AABB(const AABB &bbox1, const AABB &bbox2)
        {
            a = Interval::fuse(bbox1.a, bbox2.a);
            b = Interval::fuse(bbox1.b, bbox2.b);
            c = Interval::fuse(bbox1.c, bbox2.c);
        }

        bool intersect(const Ray &ray, float tLo, float tHi) const
        {
            for (std::size_t i = 0; i < 3; i++)
            {
                const auto &t01 = intersect(getInterval(i), ray.origin()[i], ray.direction()[i]);
                tLo = fmax(t01.first, tLo);
                tHi = fmax(t01.second, tHi);
                if (tHi <= tLo)
                {
                    return false;
                }
            }
            return true;
        }

    private:
        Interval a, b, c;

        const Interval &getInterval(std::size_t axis) const
        {
            switch (axis)
            {
            case 0:
                return a;
            case 1:
                return b;
            default:
                return c;
            }
        }

        std::pair<float, float> intersect(const Interval &v, float rayOrig, float rayDir) const
        {
            return rayDir == 0.0f ? intersectZeroDir(v, rayOrig) : intersectTimes(v, rayOrig, rayDir);
        }

        std::pair<float, float> intersectTimes(const Interval &v, float rayOrig, float rayDir) const
        {
            float t0 = fmin((v.getMin() - rayOrig) / rayDir,
                            (v.getMax() - rayOrig) / rayDir);
            float t1 = fmax((v.getMin() - rayOrig) / rayDir,
                            (v.getMax() - rayOrig) / rayDir);
            return {t0, t1};
        }

        std::pair<float, float> intersectZeroDir(const Interval &v, float rayOrig) const
        {
            const auto inf = std::numeric_limits<float>::infinity();
            if (rayOrig < v.getMin() || rayOrig > v.getMax())
                return {inf, -inf};
            else
                return {-inf, inf};
        }
    };
}