//
// Created by erez on 22/05/2025.
//

#pragma once
#include "../Model.h"
#include <GLES2/gl2.h>

class OrangePyramid : public Model {

    GLuint mProgram{0};
    GLuint aPositionHandle{0};
    GLint uColorHandle{-6};
    GLint uFaceNormalHandle{-6};
    GLint lightDirectionHandle{-7};
    GLint uMatMVPHandle{-6};

    GLuint VBO{0};
    GLuint EBO{0};


    float m_rotationAngle{0};

    const glm::ivec3 triangleColors[4]{glm::ivec3{0xfc, 0x6a, 0x03},
                                       glm::ivec3{0xed,0x82, 0x0e},
                                       glm::ivec3{0xfd,0xa1, 0x72},
                                       glm::ivec3{0xbe,0x55, 0x04}
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
    ~OrangePyramid() override;
    OrangePyramid(const Scene&, Material* material);
    virtual bool init() override;
    virtual void render() const override;
    virtual void updateState() override;
};
