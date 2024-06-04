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
        HitLocation loc;
        float t;
        std::shared_ptr<Material> mat;
    };
}