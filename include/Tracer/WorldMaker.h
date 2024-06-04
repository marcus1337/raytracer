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

        World makeSimpleWorld2() const
        {
            World world;
            glm::vec3 c1(0.8, 0.8, 0.0);
            glm::vec3 c2(0.1, 0.2, 0.5);
            glm::vec3 c3(0.6, 0.2, 0.5);
            world.add(std::make_unique<Sphere>(glm::vec3(0, 0, -1.5f), 0.5f, std::make_shared<Metal>(c1)));
            world.add(std::make_unique<Sphere>(glm::vec3(0, -100.5, -1.5f), 100.0f, std::make_shared<Lambertian>(c2)));
            return world;
        }

        World makeSimpleWorld() const
        {
            /*World world;
            glm::vec3 c1(0.8f, 0.8f, 0.0f);
            glm::vec3 c2(0.1f, 0.2f, 0.5f);
            glm::vec3 c3(0.8f, 0.8f, 0.8f);
            glm::vec3 c4(0.8f, 0.6f, 0.2f);

            auto materialGround = std::make_shared<Lambertian>(c1);
            auto materialCenter = std::make_shared<Lambertian>(c2);
            auto materialLeft = std::make_shared<Metal>(c3);
            auto materialRight = std::make_shared<Metal>(c4);

            world.add(std::make_unique<Sphere>(glm::vec3(0, 0, -100.5f), 100.5f, materialGround));
            world.add(std::make_unique<Sphere>(glm::vec3(0, 0, -1.5f), 0.5f, materialCenter));
            world.add(std::make_unique<Sphere>(glm::vec3(-1.f, 0, -1.5f), 0.5f, materialLeft));
            world.add(std::make_unique<Sphere>(glm::vec3(1.f, 0, -1.5f), 0.5f, materialRight));
            return world;*/

            World world;
            glm::vec3 c1(0.8, 0.8, 0.0);
            glm::vec3 c2(0.1, 0.2, 0.5);
            glm::vec3 c3(0.6, 0.2, 0.5);
            world.add(std::make_unique<Sphere>(glm::vec3(0, 0, -1.5f), 0.5f, std::make_shared<Lambertian>(c1)));
            world.add(std::make_unique<Sphere>(glm::vec3(1.f, 0, -1.5f), 0.5f, std::make_shared<Metal>(c3)));
            world.add(std::make_unique<Sphere>(glm::vec3(0, -100.5, -1.5f), 100.0f, std::make_shared<Lambertian>(c2)));
            return world;
        }
    };
}