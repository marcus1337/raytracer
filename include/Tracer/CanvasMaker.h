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
            std::vector<glm::vec3> pointSamples(indices.size());
            std::vector<std::size_t> pointIndices;
            for (const auto &p : indices)
            {
                pointIndices.push_back(canvasScalar.getIndex(p));
            }

            setSamples(pointIndices, pointSamples);

            for (std::size_t i = 0; i < pointSamples.size(); i++)
            {
                canvasScalar.add(i, pointSamples[i]);
            }
        }

        void setSamples(const std::vector<std::size_t> &pointIndices, std::vector<glm::vec3> &pointSamples) const
        {
            const auto &indexedRays = getPointRaysIndexed();
            std::for_each(std::execution::par, pointIndices.begin(), pointIndices.end(),
                          [&](std::size_t index)
                          {
                              pointSamples[index] = getMeanColor(getColorSamples(world, indexedRays.at(index)));
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

        std::map<Point, std::vector<Ray>> getPointRays() const
        {
            std::map<Point, std::vector<Ray>> pointRays;
            for (const auto &p : canvasScalar.getIndices())
            {
                pointRays[p] = getStratifiedRays(p);
            }
            return pointRays;
        }

        std::map<std::size_t, std::vector<Ray>> getPointRaysIndexed() const
        {
            std::map<std::size_t, std::vector<Ray>> indexedRays;
            for (const auto &[key, value] : getPointRays())
            {
                indexedRays[canvasScalar.getIndex(key)] = value;
            }
            return indexedRays;
        }

        std::vector<Ray> getSampleRays(const Point &p) const
        {
            std::vector<Ray> rays;
            rays.push_back(raySpawner.getSampleRay(p, *camera));
            return rays;
        }

        Size getStrataSize() const
        {
            int numStratas = 2;
            return {numStratas, numStratas};
        }

        glm::vec3 getColorSample(const World &world, const Point &p) const
        {
            return getMeanColor(getColorSamples(world, getStratifiedRays(p)));
        }

        std::vector<Ray> getStratifiedRays(const Point &p) const
        {
            return raySpawner.getRaysStratified(p, *camera, getStrataSize());
        }

        std::vector<glm::vec3> getColorSamples(const World &world, const std::vector<Ray> &rays) const
        {
            std::vector<glm::vec3> colors;
            for (const auto &r : rays)
            {
                colors.push_back(tracer.getRayColorScalar(r, world));
            }
            return colors;
        }

        glm::vec3 getMeanColor(const std::vector<glm::vec3> &colors) const
        {
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