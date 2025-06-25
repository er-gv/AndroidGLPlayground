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

ChessPyramid::ChessPyramid(const Scene& scene, Material *material):Model{scene, material}{}
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

    auto attributesInitialized = p_material->addAttributes(std::vector<std::tuple< const std::string&, GLsizei, GLsizei>> {
            std::make_tuple(std::string{"aPosition"}, 3, 0)
    });

    auto uniformsInitialized = p_material->addUniforms(std::vector<const std::string>{
            std::string{"uLightDirection"},
            std::string{"u_mat_mvp"},
            std::string{"uFaceNormal"},
            std::string{"uSquareSize"},
            std::string{"uEvenColor"},
            std::string{"uOddColor"}
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
    p_material->enable();
    p_material->populateAttribBuffers();


    glUniformMatrix4fv(p_material->getUniformLocation("u_mat_mvp"), 1, GL_FALSE, glm::value_ptr(m_transform()));


    unsigned offset{0};
    ;
    glUniform3f(p_material->getUniformLocation("uSquareSize"), 0.3f, 0.04f, 0.3f);

    auto direction {glm::cos(glm::radians(30.f))};
    glUniform3f(p_material->getUniformLocation("uLightDirection"), -direction, -direction, -direction);


    const GLfloat colors[] = {
            +0.8f, +0.4f, +0.0f, //0
            +0.0f, +0.4f, +0.8f, //1
            +0.8f, +0.2f, +0.8f, //2
            +0.0f, +0.8f, +0.8f, //3
    };

    auto faceNormalHandler {p_material->getUniformLocation("uFaceNormal")};
    auto evenColorHandler {p_material->getUniformLocation("uEvenColor")};
    auto oddColorHandler {p_material->getUniformLocation("uOddColor")};
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
    p_material->disable();
}


void ChessPyramid::updateState(){
    transform().multiply(perFrameTransform);
}
