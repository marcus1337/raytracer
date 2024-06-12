#pragma once
#include "pch.h"
#include "Data/Geometry/Size.h"
#include "Data/Geometry/Point.h"
#include "Tracer/Rand.h"

namespace rt
{
    class UV
    {
    public:
        UV(const Size &viewSize) : viewSize(viewSize)
        {
        }

        glm::vec2 getUVCenter(const Point &p) const
        {
            const auto &delta = getDelta();
            float u = delta.x * p.x;
            float v = delta.y * p.y;
            return glm::vec2(u, v) + delta / 2.0f;
        }

        std::vector<glm::vec2> getUVStratifiedCenters(const Point &p, const Size &strataSize) const
        {
            std::vector<glm::vec2> uvCenters;
            const auto &strataDelta = getStrataDelta(strataSize);
            const auto from = getUVFrom(p);
            for (std::size_t i = 0; i < strataSize.width; i++)
            {
                for (std::size_t j = 0; j < strataSize.height; j++)
                {
                    auto uv = from;
                    uv.x += strataDelta.x * i;
                    uv.y += strataDelta.y * j;
                    uvCenters.emplace_back(uv);
                }
            }
            return uvCenters;
        }

        std::vector<glm::vec2> getUVJitteredStratifiedCenters(const Point &p, const Size &strataSize) const
        {
            auto uvs = getUVStratifiedCenters(p, strataSize);
            const auto &strataDelta = getStrataDelta(strataSize);
            for (auto &uv : uvs)
            {
                uv += getJitter(strataDelta);
            }
            return uvs;
        }

        glm::vec2 getStrataDelta(const Size &strataSize) const
        {
            const auto &delta = getDelta();
            return {delta.x / strataSize.width, delta.y / strataSize.height};
        }

    private:
        Size viewSize;
        static thread_local Rand rand;

        glm::vec2 getDelta() const
        {
            return {getDeltaU(), getDeltaV()};
        }

        glm::vec2 getUVFrom(const Point &p) const
        {
            auto uv = getUVCenter(p);
            uv.x -= getDeltaU() / 2;
            uv.y -= getDeltaV() / 2;
            return uv;
        }

        glm::vec2 getUVTo(const Point &p) const
        {
            auto uv = getUVCenter(p);
            uv.x += getDeltaU() / 2;
            uv.y += getDeltaV() / 2;
            return uv;
        }

        float getDeltaU() const
        {
            return 1.0f / viewSize.width;
        }

        float getDeltaV() const
        {
            return 1.0f / viewSize.height;
        }

        glm::vec2 getJitter(const glm::vec2 &delta) const
        {
            float m = 0.5f; // multiplier
            auto uD = delta.x * m;
            auto vD = delta.y * m;
            float uJ = rand.getFloat(0, uD) - uD;
            float vJ = rand.getFloat(0, vD) - vD;
            return glm::vec2(uJ, vJ);
        }
    };
}