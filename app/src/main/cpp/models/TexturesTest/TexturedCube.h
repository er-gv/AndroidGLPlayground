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

class TexturedCube: public Model {

    GLuint VBO{0};
    GLuint EBO{0};

    float m_delta_angle{0.005f* glm::two_pi<float>()};

    void initGeometry();
    bool initMaterial();

public:
    ~TexturedCube() override;
    TexturedCube(const Scene&, Material* material);
    bool init() override;
    void render() const override;
    void updateState() override;
};

