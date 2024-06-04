#pragma once
#include "pch.h"
#include "Data/Tracing/Ray.h"

namespace rt
{
    struct HitLocation
    {
        glm::vec3 p;
        glm::vec3 normal;
        bool frontFace;

        void setFaceNormal(const Ray &r, const glm::vec3 &outwardNormal)
        {
            // Sets the hit record normal vector.
            // NOTE: the parameter `outward_normal` is assumed to have unit length.

            frontFace = glm::dot(r.direction(), outwardNormal) < 0;
            normal = frontFace ? outwardNormal : -outwardNormal;
        }
    };
}