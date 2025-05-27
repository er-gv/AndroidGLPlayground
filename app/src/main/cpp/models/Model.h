//
// Created by erez on 22/04/2025.
//

#pragma once

#include <thread>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Model {
public:
    virtual ~Model() = default;
    Model()=default;
    virtual bool init() = 0;
    virtual void render() const = 0;
    virtual void updateState() = 0;

protected:
    glm::vec3 pivot;
    glm::mat4 modelview{1.0f};

    inline void setPivot(glm::vec3 &p){pivot = p;}

    inline void reset_modelview(){
        modelview = glm::mat4{1.0f};
    }
    inline void translate(const glm::vec3 &t){
        modelview *= glm::translate(glm::mat4{1}, t);
    }

    inline void scale(const glm::vec3 &s){
        modelview *= glm::scale(glm::mat4{1}, s);
    }

    inline void rotate(const glm::vec3 &axis, float angle){
        modelview *= glm::rotate(glm::mat4{1}, angle, axis);
    }
};


