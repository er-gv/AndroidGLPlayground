//
// Created by erez on 25/06/2025.
//

#include "Icosahedron.h"

#include "Icosahedron.h"
#include "../../engine/libs/glm/glm.hpp"
#include "../../engine/libs/glm/gtc/matrix_transform.hpp"
#include "../../engine/libs/glm/gtc/type_ptr.hpp"

#include "../../logger.h"
#define LOG_TAG "MONOCHROMATIC_CUBE"

Icosahedron::Icosahedron(const Scene& scene, Material *material) : Model{scene, material}{}
Icosahedron::~Icosahedron(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

bool Icosahedron::init(){

    p_material->addAttribute(std::make_tuple(std::string{"aPosition"}, 3, 0));

    p_material->addUniform("uColor");
    p_material->addUniform("u_mat_mvp");
    //p_material->addUniform("uLightDirection");
    //p_material->addUniform("uFaceNormal");

    return initVBO();

}

bool Icosahedron::initVBO() {

    const GLfloat vertices[]{

            -0.2f, +0.5f, +0.4f,  //0
            +0.2f, +0.5f, +0.4f,  //1
            +0.8f, -0.8f, +0.6f, //2
            -0.8f, -0.8f, +0.6f,  //3

            -0.8f, -0.8f, -0.6f, //4
            +0.8f, -0.8f, -0.6f,  //5
            -0.2f, +0.5f, -0.4f,  //6
            +0.2f, +0.5f, -0.4f,  //7
    };

    const GLuint indices[]{
            0, 1, 3, 2,
            1,7,2,5,
            3,4,0,6,
            4,5,6,7
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return true;
}


void Icosahedron::render() const {

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    p_material->populateAttribBuffers();

    p_material->enable();
    auto u_matMVP = p_material->getUniformLocation("u_mat_mvp");
    glUniformMatrix4fv(u_matMVP, 1, GL_FALSE, glm::value_ptr(m_transform()));

    const glm::vec3 colors[]{
            glm::vec3{0.9f, 0.2f, 0.3f},
            glm::vec3{0.2f, 0.9f, 0.3f},
            glm::vec3{0.9f, 0.1f, 0.9f},
            glm::vec3{0.9f, 0.7f, 0.1f},
    };

    auto stride = 4u*sizeof(GLuint);
    auto offset = 0u;
    for(auto& color: colors){
        p_material->setProperty("uColor", color);
        glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT,
                       reinterpret_cast<const void *>(offset));
        checkGlError("glDrawElements", LOG_TAG);
        offset+=stride;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    p_material->disable();

}

void Icosahedron::updateState() {

    m_transform.multiply(perFrameTransform);
}
