//
// Created by erez on 22/04/2025.
//

#pragma once

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <cmath>
#include <map>
#include "../Model.h"
#include "../../logger.h"
#include "../../engine/materials/Material.h"
#include "../../engine/shadersBuilder.h"
#include "../../engine/libs/glm/glm.hpp"
#include "../../engine/libs/glm/gtc/constants.hpp"

class FractalCube: public Model {

    GLuint VBO{0};
    GLuint EBO{0};


    glm::vec2 seedPoint{0.0f, 0.0f};
    float spectrum[2]{0.0f, 0.0f};
    float m_rotationAngle{0};
    float m_delta_angle{0.8f};


    const glm::vec3 normals[6]{
            glm::vec3{  0.0,  0.0, +1.0},   //front
            glm::vec3{  0.0,  0.0, -1.0},   //back
            glm::vec3{ -1.0,  0.0,  0.0},   //left
            glm::vec3{ +1.0,  0.0,  0.0},    //right
            glm::vec3{  0.0, +1.0,  0.0},   //top
            glm::vec3{  0.0, -1.0,  0.0}    //bottom
    };

    void initGeometry();
    bool initMaterial();


public:
    ~FractalCube() override;
    explicit FractalCube(Material* material);
    virtual bool init() override;
    virtual void render() const override;
    virtual void updateState() override;

    void setSeedPoint(glm::vec2 seed);
    void setSpectrum(float left, float right);

};



