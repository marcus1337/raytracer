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
            virtual void clone(MatConcept *memory) const = 0;
            virtual void move(MatConcept *memory) const = 0;
        };

        template <typename MatT>
        struct MatModel : public MatConcept
        {

            void clone(MatConcept *memory) const override
            {
                ::new (memory) MatModel(*this);
            }

            void move(MatConcept *memory) const override
            {
                ::new (memory) MatModel(std::move(*this));
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
            return mat.pimpl()->do_scatter(rIn, loc);
        }

        MatConcept *pimpl() noexcept
        {
            return reinterpret_cast<MatConcept *>(buffer.data());
        }
        const MatConcept *pimpl() const noexcept
        {
            return reinterpret_cast<const MatConcept *>(buffer.data());
        }

        static constexpr std::size_t buffersize = 128UL;
        static constexpr std::size_t alignment = 16UL;

        alignas(alignment) std::array<std::byte, buffersize> buffer;

    public:
        template <typename MatT>
        Material(MatT mat)
        {
            using M = MatModel<MatT>;
            static_assert(sizeof(M) <= buffersize, "Given type is too large");
            static_assert(alignof(M) <= alignment, "Given type is overaligned");
            ::new (pimpl()) M(mat);
        }

        ~Material()
        {
            pimpl()->~MatConcept();
        }

        Material(Material const &other)
        {
            other.pimpl()->clone(pimpl());
        }

        Material &operator=(Material const &other)
        {
            Material tmp(other);
            buffer.swap(tmp.buffer);
            return *this;
        }

        Material(Material &&other)
        {
            other.pimpl()->move(pimpl());
        }
        Material &operator=(Material &&other)
        {
            Material tmp(std::move(other));
            buffer.swap(tmp.buffer);
            return *this;
        }
    };

}