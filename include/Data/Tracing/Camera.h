#pragma once
#include "pch.h"
#include "Data/Transform.h"
#include "Data/Tracing/Ray.h"

namespace rt
{
    class Camera
    {
    public:
        Transform transform;
        virtual ~Camera();
        virtual Ray spawnRay(float u, float v) const = 0;

    private:
    };
}