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

class ChessCube : public Model{
private:


    GLuint mProgram{0};
    GLuint aPositionHandle{0};
    GLint uSquareSizeHandle{-6};
    GLint uOddColorHandle{-6};
    GLint uEvenColorHandle{-6};
    GLint uFaceNormalHandle{-6};
    GLint uLightDirectionHandle{0};
    GLint uMatMVPHandle{-6};

    GLuint VBO{0};
    GLuint EBO{0};


    float m_rotationAngle{0};
    const float m_delta_angle{glm::pi<float>()/250.f};
    glm::mat4 mvp = glm::mat4(1.0f);


    GLuint vbo{0};
    GLuint ebo{0};
    bool initVBO();


public:
    ChessCube() = default;
    ~ChessCube() override;
    bool init() override;
    void updateState() override;
    void render() const override;



};


