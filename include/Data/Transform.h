#pragma once
#include "pch.h"

namespace rt
{
    struct Transform
    {
        glm::vec3 pos;
        glm::quat rot;
        glm::vec3 scale;
        Transform() : pos(0.0f, 0.0f, 0.0f), rot(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), scale(1.0f, 1.0f, 1.0f)
        {
        }
    };
}