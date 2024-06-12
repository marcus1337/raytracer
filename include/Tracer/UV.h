#pragma once
#include "pch.h"
#include "Data/Geometry/Size.h"
#include "Data/Geometry/Point.h"

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

            return uvCenters;
        }

    private:
        Size viewSize;

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
    };
}