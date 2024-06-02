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
        Camera(const rt::Size &viewSize) : viewSize(viewSize), viewportU(viewSize.width, 0, 0), viewportV(0, -viewSize.height, 0)
        {
        }
        virtual ~Camera() = default;
        virtual Ray spawnRay(float u, float v) const = 0;
        const Size &getViewSize() const
        {
            return viewSize;
        }

    protected:
        const rt::Size viewSize;
        const glm::vec3 viewportU;
        const glm::vec3 viewportV;

        glm::vec3 getViewportPosition(float u, float v) const
        {
            glm::vec3 rotatedViewportU = transform.rot * viewportU;
            glm::vec3 rotatedViewportV = transform.rot * viewportV;
            glm::vec3 viewPortUpperLeft = transform.pos - rotatedViewportU * 0.5f - rotatedViewportV * 0.5f;
            glm::vec3 origin = viewPortUpperLeft + u * rotatedViewportU + v * rotatedViewportV;
            return origin;
        }

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
            const glm::vec3 direction = transform.rot * glm::vec3(0.0f, 0.0f, -1.0f); // Assuming camera looks along -Z axis
            return Ray(getViewportPosition(u, v), direction);
        }

    private:
    };

    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera(const rt::Size &viewSize, float hFOV = 45.0f) : Camera(viewSize), hFOV(hFOV)
        {
            focalLength = static_cast<float>(viewSize.width) / (2.0f * tan(glm::radians(hFOV) / 2.0f));
        }

        virtual Ray spawnRay(float u, float v) const override
        {
            return Ray(); // TODO
        }

    private:
        float hFOV; // Degrees
        float focalLength;
    };
}