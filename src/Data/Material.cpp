#include "Data/Hit/Material.h"

namespace rt
{

    namespace MatUtil
    {
        thread_local RayRand rayRand;

        bool nearZero(const glm::vec3 &v)
        {
            const float epsilon = 1e-8;
            return glm::all(glm::lessThan(glm::abs(v), glm::vec3(epsilon)));
        }

        glm::vec3 reflect(const glm::vec3 &v, const glm::vec3 &n)
        {
            return v - 2 * glm::dot(v, n) * n;
        }
    }

    Lambertian::Lambertian(const glm::vec3 &albedo) : albedo(albedo)
    {
    }

    std::optional<Scatter> Lambertian::scatter(const Ray &rIn, const HitLocation &loc) const
    {
        Scatter scat;
        auto scatDir = loc.normal + MatUtil::rayRand.randUnitVec();
        if (MatUtil::nearZero(scatDir))
        {
            scatDir = loc.normal;
        }
        scat.r = Ray(loc.p, scatDir);
        scat.attenuation = albedo;
        return scat;
    }

    Metal::Metal(const glm::vec3 &albedo, float fuzz) : albedo(albedo), fuzz(fuzz)
    {
    }

    std::optional<Scatter> Metal::scatter(const Ray &rIn, const HitLocation &loc) const
    {
        Scatter scat;
        auto reflected = reflect(rIn.direction(), loc.normal);
        reflected = glm::normalize(reflected) + (fuzz * MatUtil::rayRand.randUnitVec());
        scat.r = Ray(loc.p, reflected);
        scat.attenuation = albedo;
        if (glm::dot(scat.r.direction(), loc.normal) <= 0)
        {
            return std::nullopt;
        }

        return scat;
    }

}