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
            return makeCanvas(world, raySpawner.getPixelRays(*camera));
        }

        Canvas makeCanvasAntialiased() const
        {
            return canvasScalar.getCanvas();
        }

        void sampleCanvas()
        {
            sampleCanvasParallel(world, 2);
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

        std::vector<Ray> getSampleRays(const Point &p, unsigned int numSamples) const
        {
            std::vector<Ray> rays;
            for (std::size_t i = 0; i < numSamples; i++)
            {
                rays.push_back(raySpawner.getSampleRay(p, *camera));
            }
            return rays;
        }

        std::vector<glm::vec3> getColorSamples(const World &world, const Point &p, unsigned int numSamples) const
        {
            std::vector<glm::vec3> colors;
            for (const auto &ray : getSampleRays(p, numSamples))
            {
                colors.push_back(tracer.getRayColorScalar(ray, world));
            }
            return colors;
        }

        void sampleCanvasParallel(const World &world, int numSamplesPerPixel)
        {
            const auto indices = canvasScalar.getIndices();
            std::for_each(std::execution::par, indices.begin(), indices.end(),
                          [&](const Point &p)
                          {
                              for (const auto &sample : getColorSamples(world, p, numSamplesPerPixel))
                              {
                                  canvasScalar.add(p, sample);
                              }
                          });
        }

        Canvas makeCanvas(const World &world, const std::vector<std::pair<Point, Ray>> &pixelRayPairs) const
        {
            CanvasScalar canvasScalar(camera->getViewSize());
            for (const auto &pair : pixelRayPairs)
            {
                auto colorScalar = tracer.getRayColorScalar(pair.second, world);
                canvasScalar.add(pair.first, colorScalar);
            }
            return canvasScalar.getCanvas();
        }
    };
}