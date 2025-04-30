//
// Created by erez on 22/04/2025.
//

#ifndef QUANTIZED_SHAPES_FRACTALCUBE_H
#define QUANTIZED_SHAPES_FRACTALCUBE_H


#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <cmath>
#include "../Model.h"
#include "../../logger.h"
#include "../../engine/shadersBuilder.h"

class FractalCube: public Model {

    GLuint mProgram{0};
    GLuint aPositionHandle{0};
    GLuint aColorHandle{0};
    GLint uQuantaHandle{0};

    float grey= 0.0f;
    int sign = 1;

public:
    virtual ~FractalCube() = default;
    FractalCube()=default;
    virtual bool init();
    virtual void render() const;
    virtual void updateState();
};


#endif //QUANTIZED_SHAPES_FRACTALCUBE_H
