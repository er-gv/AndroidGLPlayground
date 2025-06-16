//
// Created by erez on 22/05/2025.
//
#include "ChessPyramid.h"
#include "../../logger.h"
#include "../../engine/shadersBuilder.h"
#include "../../engine/libs/glm/glm.hpp"
#include "../../engine/libs/glm/gtc/matrix_transform.hpp"
#include "../../engine/libs/glm/gtc/type_ptr.hpp"
#include "../../scenes/Scene.h"

#define LOG_TAG "CHESS_PYRAMID"

ChessPyramid::~ChessPyramid(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

}
bool ChessPyramid::init(){

    initMaterial();
    initGeometry();

    return true;
}


bool ChessPyramid::initMaterial(){

    auto attributesInitialized = material->addAttributes(std::vector<std::tuple< const char*, GLsizei, GLsizei>> {
            std::make_tuple("aPosition", 3, 0)
    });

    auto uniformsInitialized = material->addUniforms(std::vector<const char*>{
            "uLightDirection", "u_mat_mvp", "uFaceNormal",
            "uSquareSize",    "uEvenColor", "uOddColor"
    });

    return  attributesInitialized && uniformsInitialized;
}


void ChessPyramid::initGeometry(){

    const GLfloat triangleVertices[] = {
            +0.0f, +0.4f, +0.0f, //0
            -0.5f, -0.6f, +0.5f, //1
            +0.5f, -0.6f, +0.5f, //2
            +0.5f, -0.6f, -0.5f, //3
            -0.5f, -0.6f, -0.5f //4
    };
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    //triangle faces
    const GLuint faces[] = {0, 1, 2,
                            0,2,3,
                            0,3,4,
                            0,4,1,
                            2,1,3, 4
    };

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces),
                 faces, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void ChessPyramid::render() const{

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    material->enable();
    material->populateAttribBuffers();


    glUniformMatrix4fv(material->getUniformLocation("u_mat_mvp"), 1, GL_FALSE, glm::value_ptr(transform()));


    unsigned offset{0};
    ;
    glUniform3f(material->getUniformLocation("uSquareSize"), 0.3f, 0.04f, 0.3f);

    auto direction {glm::cos(glm::radians(30.f))};
    glUniform3f(material->getUniformLocation("uLightDirection"), -direction, -direction, -direction);


    const GLfloat colors[] = {
            +0.8f, +0.4f, +0.0f, //0
            +0.0f, +0.4f, +0.8f, //1
            +0.8f, +0.2f, +0.8f, //2
            +0.0f, +0.8f, +0.8f, //3
    };

    auto faceNormalHandler {material->getUniformLocation("uFaceNormal")};
    auto evenColorHandler {material->getUniformLocation("uEvenColor")};
    auto oddColorHandler {material->getUniformLocation("uOddColor")};
    for(auto k=0; k< 4; ++k ) {
        glUniform3f(faceNormalHandler, normals[k].x, normals[k].y, normals[k].z);
        auto colorIndex = 6*(k%2);
        glUniform3f(evenColorHandler, colors[colorIndex], colors[colorIndex+1], colors[colorIndex+2]);
        glUniform3f(oddColorHandler, colors[colorIndex+3], colors[colorIndex+4], colors[colorIndex+5]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, reinterpret_cast<const void *>(offset*sizeof(GLuint)));
        checkGlError("glDrawElements", LOG_TAG);
        offset+=3;
    }
    //render the bottom face
    glUniform3f(faceNormalHandler, 0.f, -1.0, 0.f);

    glUniform3f(evenColorHandler, 0.65, 0.28, 12);
    glUniform3f(oddColorHandler, 0.95, 0.74,0.25);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, reinterpret_cast<const void *>(offset*sizeof(GLuint)));
    checkGlError("glDrawElements", LOG_TAG);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    material->disable();
}


void ChessPyramid::updateState(){
    static float m_rotationAngle{0};
    static const auto TWO_PI{glm::two_pi<float>()};
    static const float m_delta_angle{glm::half_pi<float>()/200.f};


    if(m_rotationAngle > TWO_PI)
        m_rotationAngle -= TWO_PI;
    transform.reset();
    transform.scale(glm::vec3{0.6f});
    transform.translate(glm::vec3(-0.3f, +0.15f, -0.3f));
    transform.rotate(-glm::half_pi<float>()*0.3, glm::vec3(1.0f, 0.0f, 1.0f) );
    transform.rotate(m_rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    m_rotationAngle += m_delta_angle;
}
