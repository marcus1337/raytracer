#include "Data/Hit/HittableObject.h"

namespace rt
{

    glm::vec3 getOutwardNormal(const Sphere &sphere, const glm::vec3 &surfacePoint)
    {
        return sphere.getOutwardNormal(surfacePoint);
    }
    std::vector<float> getIntersectionDistances(const Sphere &sphere, const Ray &r)
    {
        return sphere.getIntersectionDistances(r);
    }

    std::optional<HitRecord> HittableObject::hit(const Ray &r, const Interval &rT) const
    {
        const auto hitT = rT.getMinValidParameter(getIntersectionDistances(*this, r));
        if (hitT.has_value())
        {
            return getHitRecord(r, hitT.value());
        }
        else
        {
            return std::nullopt;
        }
    }

    HitRecord HittableObject::getHitRecord(const Ray &r, float t) const
    {
        HitRecord rec;
        auto &loc = rec.loc;
        rec.t = t;
        loc.p = r.at(rec.t);
        loc.setFaceNormal(r, getOutwardNormal(*this, loc.p));
        rec.mat = mat;
        return rec;
    }
}
