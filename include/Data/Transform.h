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

        void move(float sideways, float forward)
        {
            glm::vec3 forwardDir = getLookAt();
            glm::vec3 rightDir = glm::normalize(glm::cross(forwardDir, glm::vec3(0.0f, 1.0f, 0.0f)));
            pos += rightDir * sideways + forwardDir * forward;
        }

        glm::vec3 getLookAt() const
        {
            return glm::normalize(rot * glm::vec3(0.0f, 0.0f, -1.0f)); // Assumes looking along -Z axis
        }

        void addRotation(float yaw, float pitch)
        {
            glm::quat quatYaw = glm::angleAxis(glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));     // Yaw (rotation around Y-axis)
            glm::quat quatPitch = glm::angleAxis(glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f)); // Pitch (rotation around X-axis)
            glm::quat newRotation = quatYaw * quatPitch;
            rot = newRotation * rot;
            rot = glm::normalize(rot);
        }
    };
}