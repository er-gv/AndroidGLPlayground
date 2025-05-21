//
// Created by erez on 12/05/2025.
//

#include "DirectionalLight.h"
#include "../../logger.h"

#define LOG_TAG "DIRECTIONAL_LIGHT"

DirectionalLight::DirectionalLight(const glm::vec3& direction, const glm::vec3& color):
        direction{direction}, color{color}{
    log_debug(LOG_TAG, "@DirectionalLight parametrized c\'tor");
}
DirectionalLight::DirectionalLight(): DirectionalLight{
    glm::vec3{0.0f, -1.0f, -1.0f},glm::vec3{1.f}}
    {
        log_debug(LOG_TAG, "@DirectionalLight default c\'tor");
    }


void DirectionalLight::setDirection(const glm::vec3& direction){
    this->direction = direction;
}

void DirectionalLight::setColor(const glm::vec3& color){
    this->color = color;
}

const glm::vec3& DirectionalLight::getDirection() const{
    return direction;
}

const glm::vec3& DirectionalLight::getColor() const{
    return color;
}