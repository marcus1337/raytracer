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

        World makeWorld() const
        {
            World world;
            glm::vec3 c1(0.8, 0.8, 0.0);
            glm::vec3 c2(0.6, 0.2, 0.5);
            glm::vec3 c3(0.8, 0.7, 0.7);

            Sphere sphere1(glm::vec3(0, 0, -1.5f), 0.5f);
            Sphere sphere2(glm::vec3(1.f, 0, -1.5f), 0.5f);
            Sphere sphere3(glm::vec3(0, -100.5, -1.5f), 100.0f);
            
            Material m1 = Lambertian(c1);
            Material m2 = Metal(c2, 0.3);
            Material m3 = Lambertian(c3);

            world.add(HittableObject(sphere1, m1));
            world.add(HittableObject(sphere2, m2));
            world.add(HittableObject(sphere3, m3));
            return world;
        }
    };
}