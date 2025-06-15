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
    float m_rotationAngle;
    glm::vec3 rotation_axis{1.0f, 1.0f, -1.0f};
    GLfloat quanta{10.0f};

    GLuint mProgram{888};
    GLuint aPositionHandle{8};
    GLuint aColorHandle{0};
    GLuint VBO;
    unsigned int EBO;

    std::map<std::string, GLint> uniformLocations;
    std::map<std::string, GLuint> attribLocations;


    GLint uNormalHandle{0};
    GLint uMatMVHandle{0};
    GLint uMatMVPHandle{0};
    GLint uTexHandle{0};
    GLint uQuantaHandle;


    void initModel();
    bool initMaterial();

public:
    QuantizedCube() = default;
    ~QuantizedCube();
    bool init() override;
    void updateState() override;
    void render() const override;



};

