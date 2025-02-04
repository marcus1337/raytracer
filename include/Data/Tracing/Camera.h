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
        Camera(const rt::Size &viewSize) : viewSize(viewSize), viewportWidth(viewportHeight * getAspectRatio()),
                                           viewportU(viewportWidth, 0, 0), viewportV(0, -viewportHeight, 0)
        {
        }
        virtual ~Camera() = default;
        Ray spawnRay(const glm::vec2 &uv) const
        {
            return spawnRay(uv.x, uv.y);
        }
        virtual Ray spawnRay(float u, float v) const = 0;
        const Size &getViewSize() const
        {
            return viewSize;
        }

    private:
        const rt::Size viewSize;
        float getAspectRatio() const
        {
            return (float)viewSize.width / (float)viewSize.height;
        }

    protected:
        const float viewportHeight = 20.0f;
        const float viewportWidth;
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
            return Ray(getViewportPosition(u, v), transform.getLookAt());
        }

    private:
    };

    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera(const rt::Size &viewSize, float hFOV) : Camera(viewSize), hFOV(hFOV)
        {
            focalLength = static_cast<float>(viewportWidth) / (2.0f * tan(glm::radians(hFOV) / 2.0f));
        }

        virtual Ray spawnRay(float u, float v) const override
        {
            return Ray(transform.pos, getRayDirection(u, v));
        }

    private:
        float hFOV; // Degrees
        float focalLength;

        glm::vec3 getViewportOffset() const
        {
            return transform.pos + transform.getLookAt() * focalLength;
        }

        glm::vec3 getRayDirection(float u, float v) const
        {
            const glm::vec3 viewportOffsetPos = getViewportOffset() + getViewportPosition(u, v);
            return glm::normalize(viewportOffsetPos - transform.pos);
        }
    };
}