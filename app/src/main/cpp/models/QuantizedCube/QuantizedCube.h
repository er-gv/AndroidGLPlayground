//
// Created by erez on 22/04/2025.
//

#pragma once

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <cmath>
#include "../Model.h"
#include "../../logger.h"
#include "../../engine/shadersBuilder.h"

class QuantizedCube : public Model{
private:
    GLfloat grey{0.0f};
    float sign{1};

    GLuint mProgram{888};
    GLuint aPositionHandle{8};

    GLuint aColorHandle{0};
    GLuint uNormalHandle{0};
    GLuint uMatMVHandle{0};
    GLuint uMatMVPHandle{0};
    GLuint uTexHandle{0};

    const GLfloat mTriangleVertices[6]{0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f};

public:
    QuantizedCube() = default;
    bool init() override;
    void updateState() override;
    void render() const override;



};

