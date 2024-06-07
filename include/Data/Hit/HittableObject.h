#pragma once
#include "pch.h"
#include "Data/Hit/Hittable.h"
#include "Data/Hit/Sphere.h"

namespace rt
{

    glm::vec3 getOutwardNormal(const Sphere& sphere, const glm::vec3 &surfacePoint);
    std::vector<float> getIntersectionDistances(const Sphere& sphere, const Ray &r);

    class HittableObject : public Hittable
    {

    private:
        struct HitObjConcept
        {
            virtual ~HitObjConcept() = default;
            virtual void clone(HitObjConcept *memory) const = 0;
            virtual void move(HitObjConcept *memory) const = 0;
            virtual glm::vec3 doGetOutwardNormal(const glm::vec3 &surfacePoint) const = 0;
            virtual std::vector<float> doGetIntersectionDistances(const Ray &r) const = 0;
        };

        template <typename ObjT>
        struct HitObjModel : public HitObjConcept
        {
            void clone(HitObjConcept *memory) const override
            {
                ::new (memory) HitObjModel(*this);
            }
            void move(HitObjConcept *memory) const override
            {
                ::new (memory) HitObjModel(std::move(*this));
            }
            HitObjModel(ObjT obj) : obj_(std::move(obj))
            {
            }

            virtual glm::vec3 doGetOutwardNormal(const glm::vec3 &surfacePoint) const override
            {
                return getOutwardNormal(obj_, surfacePoint);
            }
            virtual std::vector<float> doGetIntersectionDistances(const Ray &r) const override
            {
                return getIntersectionDistances(obj_, r);
            }

            ObjT obj_;
        };

        friend glm::vec3 getOutwardNormal(const HittableObject &hitObj, const glm::vec3 &surfacePoint)
        {
            return hitObj.pimpl()->doGetOutwardNormal(surfacePoint);
        }
        friend std::vector<float> getIntersectionDistances(const HittableObject &hitObj, const Ray &r)
        {
            return hitObj.pimpl()->doGetIntersectionDistances(r);
        }

        HitObjConcept *pimpl() noexcept
        {
            return reinterpret_cast<HitObjConcept *>(buffer.data());
        }
        const HitObjConcept *pimpl() const noexcept
        {
            return reinterpret_cast<const HitObjConcept *>(buffer.data());
        }

        static constexpr std::size_t buffersize = 128UL;
        static constexpr std::size_t alignment = 16UL;

        alignas(alignment) std::array<std::byte, buffersize> buffer;

    public:
        template <typename HitObjT>
        HittableObject(HitObjT objT, const Material &mat) : mat(mat)
        {
            using M = HitObjModel<HitObjT>;
            static_assert(sizeof(M) <= buffersize, "Given type is too large");
            static_assert(alignof(M) <= alignment, "Given type is overaligned");
            ::new (pimpl()) M(objT);
        }

        ~HittableObject()
        {
            pimpl()->~HitObjConcept();
        }

        HittableObject(HittableObject const &other)
        {
            other.pimpl()->clone(pimpl());
            mat = other.mat;
        }

        HittableObject &operator=(HittableObject const &other)
        {
            HittableObject tmp(other);
            buffer.swap(tmp.buffer);
            mat = other.mat;
            return *this;
        }

        HittableObject(HittableObject &&other)
        {
            other.pimpl()->move(pimpl());
            mat = std::move(other.mat);
        }
        HittableObject &operator=(HittableObject &&other)
        {
            HittableObject tmp(std::move(other));
            buffer.swap(tmp.buffer);
            mat = std::move(other.mat);
            return *this;
        }

        virtual std::optional<HitRecord> hit(const Ray &r, const Interval &rT) const override;

    private:
        Material mat;
        HitRecord getHitRecord(const Ray &r, float t) const;
    };

}