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
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

class FractalCube: public Model {

    GLuint mProgram{0};
    GLuint aPositionHandle{0};
    GLint uColorHandle{-6};
    GLint uFaceNormalHandle{-6};
    GLint uMatMVPHandle{-6};

    GLuint VBO{0};
    GLuint EBO{0};


    float m_rotationAngle{0};
    float m_delta_angle{0.2f};
    glm::mat4 mvp = glm::mat4(1.0f);

    const glm::vec3 triangleColors[4]{glm::vec3{0xfc/255.0f,0x6a/255.0f, 0x03/255.0f},
                                       glm::vec3{0xed/255.0f,0x82/255.0f, 0x0e/255.0f},
                                       glm::vec3{0xfd/255.0f,0xa1/255.0f, 0x72/255.0f},
                                       glm::vec3{0xbe/255.0f,0x55/255.0f, 0x04/255.0f}
    };

    const glm::vec3 normals[4]{
            glm::normalize(glm::cross(glm::vec3{0.75f,-0.8f, +0.75f}, glm::vec3{+0.75f,-0.8f, -0.75f})),
            glm::normalize(glm::cross(glm::vec3{+0.75f,-0.8f, -0.75f}, glm::vec3{-0.75f,-0.8f, -0.75f})),
            glm::normalize(glm::cross(glm::vec3{-0.75f,-0.8f, -0.75f}, glm::vec3{-0.75f,-0.8f, +0.75f})),
            glm::normalize(glm::cross(glm::vec3{-0.75f,-0.8f, +0.75f}, glm::vec3{+0.75f,-0.8f, +0.75f}))
    };


    void initGeometry();
    bool initShader();

public:
    ~FractalCube() override = default;
    FractalCube()=default;
    virtual bool init();
    virtual void render() const;
    virtual void updateState();
};



