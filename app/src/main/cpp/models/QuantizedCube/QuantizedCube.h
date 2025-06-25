//
// Created by erez on 22/04/2025.
//

#pragma once

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <cmath>
#include <map>
#include "../../engine/libs/glm/vec3.hpp"
#include "../Model.h"
#include "../../logger.h"
#include "../../engine/shadersBuilder.h"

class QuantizedCube : public Model{
private:
    GLfloat quanta{10.0f};

    //GLuint aPositionHandle{8};
    //GLuint aColorHandle{0};
    GLuint VBO{0};
    unsigned int EBO{0};

    void initModel();
    bool initMaterial();

public:
    QuantizedCube(const Scene&, Material* material);
    ~QuantizedCube() override;
    bool init() override;
    void updateState() override;
    void render() const override;



};

