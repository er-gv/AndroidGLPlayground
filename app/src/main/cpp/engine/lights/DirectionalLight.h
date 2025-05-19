//
// Created by erez on 12/05/2025.
//

#pragma once

#include <glm/glm.hpp>

class DirectionalLight {

    glm::vec3 direction;
    glm::vec3 color;

    public:
    DirectionalLight(const glm::vec3& direction, const glm::vec3& color);
    DirectionalLight();
    ~DirectionalLight() =default;

    void setDirection(const glm::vec3& direction);
    void setColor(const glm::vec3& color);
    const glm::vec3& getDirection() const;
    const glm::vec3& getColor() const;
};



