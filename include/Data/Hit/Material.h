#pragma once
#include "pch.h"
#include "Data/Tracing/Ray.h"
#include "Data/Hit/HitLocation.h"

namespace rt
{
    class Material
    {
    public:
        virtual ~Material() = default;

    private:
    };
}