//
// Created by erez on 16/06/2025.
//


#pragma once

#include "../libs/glm/vec3.hpp"

struct EnvironmentLight{
    explicit EnvironmentLight(const glm::vec3 color, float intensity): color{color}, intensity{glm::max(0.f, intensity)}
    {}
    EnvironmentLight(): color{1.f}, intensity{1.0}{}
    glm::vec3 color;
    float intensity;
};