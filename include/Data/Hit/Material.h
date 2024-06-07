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

    namespace MatUtil
    {
        extern thread_local RayRand rayRand;
        bool nearZero(const glm::vec3 &v);
        glm::vec3 reflect(const glm::vec3 &v, const glm::vec3 &n);
    }

    class Material
    {
    public:
        virtual ~Material() = default;
        virtual std::optional<Scatter> scatter(const Ray &rIn, const HitLocation &loc) const = 0;

    protected:
    private:
    };

    class Lambertian : public Material
    {
    public:
        Lambertian(const glm::vec3 &albedo);

        virtual std::optional<Scatter> scatter(const Ray &rIn, const HitLocation &loc) const override;

    private:
        glm::vec3 albedo; // Color
    };

    class Metal : public Material
    {
    public:
        Metal(const glm::vec3 &albedo, float fuzz);

        virtual std::optional<Scatter> scatter(const Ray &rIn, const HitLocation &loc) const override;

    private:
        glm::vec3 albedo; // Color
        float fuzz;
    };
}