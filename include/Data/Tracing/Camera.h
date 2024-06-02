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
        virtual ~Camera() = default;
        virtual Ray spawnRay(float u, float v) const = 0;

    protected:
    private:
    };

    class OrthogonalCamera : public Camera
    {
    public:
        virtual Ray spawnRay(float u, float v) const override
        {
            return Ray(); // TODO
        }

    private:
    };

    class PerspectiveCamera : public Camera
    {
    public:
        virtual Ray spawnRay(float u, float v) const override
        {
            return Ray(); // TODO
        }

    private:
    };
}