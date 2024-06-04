#pragma once
#include "pch.h"
#include "Data/Tracing/Ray.h"
#include "Data/Hit/Interval.h"
#include "Data/Hit/HitLocation.h"

namespace rt
{
    struct HitRecord
    {
        HitLocation loc;
        float t;
    };
}