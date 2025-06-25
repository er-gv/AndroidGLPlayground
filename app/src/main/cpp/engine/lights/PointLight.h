//
// Created by erez on 09/06/2025.
//

#pragma once
#include "../libs/glm/glm.hpp"
#include "../libs/glm/vec3.hpp"
#include "../libs/glm/gtc/matrix_transform.hpp"


class PointLight {
    glm::vec3 position;
    glm::vec3 color;

    glm::mat4 transform;

public:
    void setPosition(glm::vec3 pos);

    void setColor(glm::vec3 col);

    const glm::vec3& getPosition() const;

    const glm::vec3& getColor() const;

};

