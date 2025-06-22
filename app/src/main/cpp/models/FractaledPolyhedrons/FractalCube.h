//
// Created by erez on 14/06/2025.
//

#pragma once

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "../Model.h"
#include "../../logger.h"
#include "../../engine/libs/glm/glm.hpp"
#include "../../engine/libs/glm/gtc/constants.hpp"

class FractalCube: public Model {

    GLuint VBO{0};
    //GLuint EBO{0};
    //GLint exponentHandle{0};
    float exponent{1.0};
    void initGeometry();
    bool initMaterial();
    /*float expon = 1.f;
    float theta{0.f};
    float tetha_step = glm::pi<float>()*0.01f;*/
    float face_step = 0.001f;

public:
    ~FractalCube() override;
    FractalCube(const Scene&, Material* material);
    bool init() override;
    void render() const override;
    void updateState() override;
};

