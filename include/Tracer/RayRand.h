#pragma once
#include "pch.h"
#include "Tracer/Rand.h"

namespace rt
{
    class RandRand
    {
    public:
        RandRand()
        {
        }

        glm::vec3 randUnitVec()
        {
            return glm::normalize(randInUnitSphere());
        }

        glm::vec3 randInUnitSphere()
        {
            auto p = randVec(-1.f, 1.f);
            while (glm::length2(p) > 1)
                p = randVec(-1.f, 1.f);
            return p;
        }

        glm::vec3 randOnHemisphere(const glm::vec3 &normal)
        {
            auto onUnitSphere = randUnitVec();
            if (glm::dot(onUnitSphere, normal) > 0.0f)
            {
                return onUnitSphere;
            }
            else
            {
                return -onUnitSphere;
            }
        }

    private:
        Rand rand;

        glm::vec3 randVec(float minVal, float maxVal)
        {
            float x = rand.getFloat(minVal, maxVal);
            float y = rand.getFloat(minVal, maxVal);
            float z = rand.getFloat(minVal, maxVal);
            return glm::vec3(x, y, z);
        }
    };
}