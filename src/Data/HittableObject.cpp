#include "Data/Hit/HittableObject.h"

namespace rt
{

    HittableObject::HittableObject(const Material &mat) : mat(mat)
    {
    }

    std::optional<HitRecord> HittableObject::hit(const Ray &r, const Interval &rT) const
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

    HitRecord HittableObject::getHitRecord(const Ray &r, float t) const
    {
        HitRecord rec;
        auto &loc = rec.loc;
        rec.t = t;
        loc.p = r.at(rec.t);
        loc.setFaceNormal(r, getOutwardNormal(loc.p));
        rec.mat = mat;
        return rec;
    }

}