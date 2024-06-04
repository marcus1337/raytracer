#pragma once
#include "pch.h"
#include "Data/Tracing/Ray.h"
#include "Data/Hit/HitLocation.h"
#include "Tracer/RayRand.h"

namespace rt
{

    struct Scatter
    {
        Ray r;
        glm::vec3 attenuation; // color
    };

    class Material
    {
    public:
        virtual ~Material() = default;
        virtual std::optional<Scatter> scatter(const Ray &rIn, const HitLocation &loc) const = 0;

    protected:
        static thread_local RayRand rayRand;

        bool nearZero(const glm::vec3 &v) const
        {
            const float epsilon = 1e-8;
            return glm::all(glm::lessThan(glm::abs(v), glm::vec3(epsilon)));
        }

        glm::vec3 reflect(const glm::vec3 &v, const glm::vec3 &n) const
        {
            return v - 2 * glm::dot(v, n) * n;
        }

    private:
    };

    class Lambertian : public Material
    {
    public:
        Lambertian(const glm::vec3 &albedo) : albedo(albedo)
        {
        }

        virtual std::optional<Scatter> scatter(const Ray &rIn, const HitLocation &loc) const override
        {
            Scatter scat;
            auto scatDir = loc.normal + rayRand.randUnitVec();
            if (nearZero(scatDir))
            {
                scatDir = loc.normal;
            }
            scat.r = Ray(loc.p, scatDir);
            scat.attenuation = albedo;
            return scat;
        }

    private:
        glm::vec3 albedo; // Color
    };

    class Metal : public Material
    {
    public:
        Metal(const glm::vec3 &albedo, float fuzz) : albedo(albedo), fuzz(fuzz)
        {
        }

        virtual std::optional<Scatter> scatter(const Ray &rIn, const HitLocation &loc) const override
        {
            Scatter scat;
            auto reflected = reflect(rIn.direction(), loc.normal);
            reflected = glm::normalize(reflected) + (fuzz * rayRand.randUnitVec());
            scat.r = Ray(loc.p, reflected);
            scat.attenuation = albedo;
            if (glm::dot(scat.r.direction(), loc.normal) <= 0)
            {
                return std::nullopt;
            }

            return scat;
        }

    private:
        glm::vec3 albedo; // Color
        float fuzz;
    };
}