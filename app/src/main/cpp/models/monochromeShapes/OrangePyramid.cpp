//
// Created by erez on 22/05/2025.
//
#include "OrangePyramid.h"
#include "../../logger.h"
#include "../../engine/shadersBuilder.h"
#include "../../engine/libs/glm/gtc/matrix_transform.hpp"
#include "../../engine/libs/glm/gtc/type_ptr.hpp"
#define LOG_TAG "FRACTAL_CUBE"

OrangePyramid::OrangePyramid(const Scene &scene, Material* material) : Model{scene, material}{}
OrangePyramid::~OrangePyramid(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

bool OrangePyramid::init(){
    initMaterial();
    initGeometry();

    return true;
}


bool OrangePyramid::initMaterial(){

    p_material->addAttribute(std::make_tuple(std::string{"aPosition"}, 3, 0));
    p_material->addUniforms(std::vector<const std::string>{
        "u_mat_mvp", "uColor", /*"uFaceNormal", "uLightDirection"*/
    });

    return true;
}


void OrangePyramid::initGeometry(){

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
                            0,4,1
    };

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces),
                 faces, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}

void OrangePyramid::render() const{

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    p_material->populateAttribBuffers();

    p_material->enable();
    p_material->setProperty("u_mat_mvp", m_transform());
    //auto u_matMVP = p_material->getUniformLocation("u_mat_mvp");
    //glUniformMatrix4fv(u_matMVP, 1, GL_FALSE, glm::value_ptr(m_transform()));

    const glm::vec3 colors[]{
            glm::vec3{0.988f, 0.415f, 0.011f},
            glm::vec3{0.929f, 0.509f, 0.054f},
            glm::vec3{0.992f, 0.631f, 0.447f},
            glm::vec3{0.745f, 0.333f, 0.015f},
    };

    auto stride = 3u*sizeof(GLuint);
    auto offset = 0u;
    for(auto& color: colors){
        p_material->setProperty("uColor", color);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT,reinterpret_cast<const void *>(offset) );
        checkGlError("glDrawElements", LOG_TAG);
        offset+=stride;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    p_material->disable();


}

void OrangePyramid::updateState(){
    m_transform.multiply(perFrameTransform);
}
