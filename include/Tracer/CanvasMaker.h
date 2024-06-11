#pragma once
#include "pch.h"
#include "Data/Transform.h"
#include "Data/Tracing/Ray.h"
#include "Data/Geometry/Size.h"
#include "Data/Geometry/Point.h"
#include "Data/Tracing/Camera.h"
#include "Tracer/RaySpawner.h"
#include "Data/Canvas.h"
#include "Tracer/World.h"
#include "Tracer/Background.h"
#include "Data/CanvasScalar.h"
#include "Tracer/Tracer.h"
#include "Tracer/WorldMaker.h"

namespace rt
{
    class CanvasMaker
    {
    public:
        CanvasMaker(const Size &canvasSize) : canvasScalar(canvasSize)
        {
            spdlog::log(spdlog::level::info, "Canvas Size {} {}", canvasSize.width, canvasSize.height);
            camera = std::make_unique<PerspectiveCamera>(canvasSize, 90.0f);
        }

        Canvas makeCanvas() const
        {
            return canvasScalar.getCanvas();
        }

        void sampleCanvas()
        {
            const auto indices = canvasScalar.getIndices();
            std::for_each(std::execution::par, indices.begin(), indices.end(),
                          [&](const Point &p)
                          {
                              canvasScalar.add(p, getColorSample(world, p));
                          });
        }

        void setWorld(const World &world)
        {
            this->world = world;
            canvasScalar.clear();
        }

        Transform getCameraTransform() const
        {
            return camera->transform;
        }

        void setCameraTransform(const Transform &transform)
        {
            camera->transform = transform;
            canvasScalar.clear();
        }

    private:
        std::unique_ptr<Camera> camera;
        RaySpawner raySpawner;
        Tracer tracer;
        World world;
        CanvasScalar canvasScalar;

        std::vector<Ray> getSampleRays(const Point &p) const
        {
            std::vector<Ray> rays;
            rays.push_back(raySpawner.getSampleRay(p, *camera));
            return rays;
        }

        glm::vec3 getColorSample(const World &world, const Point &p) const
        {
            std::vector<glm::vec3> colors;
            const auto &r = raySpawner.getSampleRay(p, *camera);
            colors.push_back(tracer.getRayColorScalar(r, world));
            glm::vec3 meanColor(0.0f);
            for (const auto &color : colors)
            {
                meanColor += color;
            }
            meanColor /= static_cast<float>(colors.size());
            return meanColor;
        }
    };
}