//
// Created by erez on 24/05/2025.
//

#pragma once


#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <cmath>
#include "../Model.h"
#include "../../logger.h"
#include "../../engine/shadersBuilder.h"

class Icosahedron : public Model{
    GLuint mProgram{0};
    GLuint aPositionHandle{0};
    GLint uSquareSizeHandle{-6};
    GLint uOddColorHandle{-6};
    GLint uEvenColorHandle{-6};
    GLint uFaceNormalHandle{0};
    GLint uLightDirectionHandle{0};

    GLint uMatMVPHandle{-6};

    GLuint VBO{0};
    GLuint EBO{0};


    float m_rotationAngle{0};
    float m_delta_angle{glm::pi<float>()/150};
    glm::mat4 mvp = glm::mat4(1.0f);

bool initGeometry();
bool initShader();

public:
~Icosahedron() override;
explicit Icosahedron(const Scene&, Material* material);
virtual bool init();
virtual void render() const;
virtual void updateState();






};


