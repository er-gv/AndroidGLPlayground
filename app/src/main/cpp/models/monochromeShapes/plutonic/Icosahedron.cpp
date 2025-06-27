//
// Created by erez on 25/06/2025.
//

#include "Icosahedron.h"

#include "Icosahedron.h"
#include "../../../engine/libs/glm/glm.hpp"
#include "../../../engine/libs/glm/gtc/matrix_transform.hpp"
#include "../../../engine/libs/glm/gtc/type_ptr.hpp"

#include "../../../logger.h"
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

    const auto s_norm{0.525731f};
    const auto t_norm{0.850651f};

    const GLfloat vertices[]{
        -s_norm,  t_norm,  0,
        s_norm,  t_norm,  0,
        -s_norm, -t_norm,  0,
        s_norm, -t_norm,  0,

        0, -s_norm,  t_norm,
        0,  s_norm,  t_norm,
        0, -s_norm, -t_norm,
        0,  s_norm, -t_norm,

        t_norm,  0, -s_norm,
        t_norm,  0,  s_norm,
        -t_norm,  0, -s_norm,
        -t_norm,  0,  s_norm
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    const GLuint indices[]{
            // 5 faces around point V0
            0, 11, 5,
            0, 5, 1,
            0, 1, 7,
            0, 7, 10,
            0, 10, 11,

            // 5 adjacent faces
            1, 5, 9,
            5, 11, 4,
            11, 10, 2,
            10, 7, 6,
            7, 1, 8,

            // 5 faces around point V3
            3, 9, 4,
            3, 4, 2,
            3, 2, 6,
            3, 6, 8,
            3, 8, 9,

            // 5 adjacent faces (inverted order to make up the bottom)
            // These are the "other side" of the middle band, connecting to the bottom cap
            // To ensure correct winding order (e.g., counter-clockwise for front faces):
            4, 9, 5,    // Corresponds to 1,5,9 but seen from "below"
            2, 4, 11,   // Corresponds to 5,11,4
            6, 2, 10,   // Corresponds to 11,10,2
            8, 6, 7,    // Corresponds to 10,7,6
            9, 8, 1,     // Corresponds to 7,1,8


    };



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
            glm::vec3{52.f, 235.f, 67.f}/255.f,
            glm::vec3{26.f, 94.f, 32.f}/255.f,
            glm::vec3{127.f, 173.f, 131.f}/255.f,
            glm::vec3{9.f, 20.f, 10.f}/255.f,
    };

    p_material->setProperty("uColor", colors[0]);
    glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT,
                   reinterpret_cast<const void *>(0u));

    p_material->setProperty("uColor", colors[1]);
    glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT,
                   reinterpret_cast<const void *>(15u*sizeof(GLuint)));

    p_material->setProperty("uColor", colors[2]);
    glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT,
                   reinterpret_cast<const void *>(30u*sizeof(GLuint)));
    p_material->setProperty("uColor", colors[3]);
    glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT,
                   reinterpret_cast<const void *>(45u*sizeof(GLuint)));




    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    p_material->disable();

}

void Icosahedron::updateState() {

    m_transform.multiply(perFrameTransform);
}
