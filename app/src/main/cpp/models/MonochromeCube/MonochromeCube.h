//
// Created by erez on 04/05/2025.
//


#pragma once

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <cmath>
#include "../Model.h"
#include "../../logger.h"
#include "../../engine/shadersBuilder.h"

class MonochromeCube : public Model{
private:

    GLuint mProgram{888};
    GLuint aPositionHandle{8};

    GLint uColorHandle{0};
    GLint u_matMVP{0};

    GLuint vbo{0};
    GLuint ebo{0};
    bool initVBO();


public:
    MonochromeCube(const Scene&, Material* material);
    ~MonochromeCube() override;
    bool init() override;
    void updateState() override;
    void render() const override;



};


