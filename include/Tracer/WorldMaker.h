#pragma once
#include "pch.h"
#include "Data/Transform.h"
#include "Data/Tracing/Ray.h"
#include "Data/Geometry/Size.h"
#include "Data/Geometry/Point.h"
#include "Data/Tracing/Camera.h"
#include "Tracer/World.h"

namespace rt
{
    class WorldMaker
    {
    public:
        WorldMaker()
        {
        }

        World makeSimpleWorld() const
        {
            World world;
            glm::vec3 c1(0.8, 0.8, 0.0);
            glm::vec3 c2(0.1, 0.2, 0.5);

            world.add(std::make_unique<Sphere>(glm::vec3(0, 0, -1.5f), 0.5f, std::make_shared<Lambertian>(c1)));
            world.add(std::make_unique<Sphere>(glm::vec3(0, -100.5, -1.5f), 100.0f, std::make_shared<Lambertian>(c2)));
            return world;
        }
    };
}