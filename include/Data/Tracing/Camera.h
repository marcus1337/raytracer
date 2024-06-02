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
        Camera(const rt::Size &viewSize) : viewSize(viewSize)
        {
        }
        virtual ~Camera() = default;
        virtual Ray spawnRay(float u, float v) const = 0;

    protected:
        const rt::Size &viewSize;

    private:
    };

    class OrthogonalCamera : public Camera
    {
    public:
        OrthogonalCamera(const rt::Size &viewSize) : Camera(viewSize)
        {
        }
        virtual Ray spawnRay(float u, float v) const override
        {
            return Ray(); // TODO
        }

    private:
    };

    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera(const rt::Size &viewSize, float hFOV) : Camera(viewSize), hFOV(hFOV)
        {
        }

        virtual Ray spawnRay(float u, float v) const override
        {
            return Ray(); // TODO
        }

    private:
        float hFOV; // Degrees
    };
}