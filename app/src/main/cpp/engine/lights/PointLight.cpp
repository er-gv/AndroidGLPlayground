
#include "PointLight.h"
void PointLight::setPosition(glm::vec3 pos){
    position = pos;
    transform = glm::translate(glm::mat4(1.0f), position);
}

void PointLight::setColor(glm::vec3 col){
    color = col;
}

const glm::vec3& PointLight::getPosition() const {
    return position;
}

const glm::vec3& PointLight::getColor() const {
    return color;
}
