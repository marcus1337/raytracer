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

    class Lambertian
    {
    public:
        Lambertian(const glm::vec3 &albedo);
        std::optional<Scatter> scatter(const Ray &rIn, const HitLocation &loc) const;

    private:
        glm::vec3 albedo; // Color
    };

    class Metal
    {
    public:
        Metal(const glm::vec3 &albedo, float fuzz);
        std::optional<Scatter> scatter(const Ray &rIn, const HitLocation &loc) const;

    private:
        glm::vec3 albedo; // Color
        float fuzz;
    };

    std::optional<Scatter> scatter(const Lambertian &mat, const Ray &rIn, const HitLocation &loc);
    std::optional<Scatter> scatter(const Metal &mat, const Ray &rIn, const HitLocation &loc);

    class Material
    {
    private:
        struct MatConcept
        {
            virtual ~MatConcept() = default;
            virtual std::optional<Scatter> do_scatter(const Ray &rIn, const HitLocation &loc) const = 0;
            virtual std::unique_ptr<MatConcept> clone() const = 0;
        };

        template <typename MatT>
        struct MatModel : public MatConcept
        {

            std::unique_ptr<MatConcept> clone() const override
            {
                return std::make_unique<MatModel>(*this);
            }

            MatModel(MatT mat) : mat_(std::move(mat))
            {
            }

            std::optional<Scatter> do_scatter(const Ray &rIn, const HitLocation &loc) const override
            {
                return scatter(mat_, rIn, loc);
            }

            MatT mat_;
        };

        friend std::optional<Scatter> scatter(const Material &mat, const Ray &rIn, const HitLocation &loc)
        {
            return mat.pimpl->do_scatter(rIn, loc);
        }

        std::unique_ptr<MatConcept> pimpl;

    public:
        template <typename MatT>
        Material(MatT mat) : pimpl(std::make_unique<MatModel<MatT>>(std::move(mat)))
        {
        }

        Material(Material const &other) : pimpl(other.pimpl->clone())
        {
        }

        Material &operator=(Material const &other)
        {
            other.pimpl->clone().swap(pimpl);
            return *this;
        }

        // Material(Material &&other) = default;
        // Material &operator=(Material &&other) = default;
    };

}