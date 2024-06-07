#pragma once
#include "pch.h"
#include "Data/Tracing/Ray.h"
#include "Data/Hit/Interval.h"
#include "Data/Hit/HitLocation.h"
#include "Material.h"

namespace rt
{
    struct HitRecord
    {
        HitRecord() : mat(Lambertian(glm::vec3(0.5f, 0.5f, 0.5f)))
        {
        }

        HitLocation loc;
        float t;
        Material mat;
    };
}