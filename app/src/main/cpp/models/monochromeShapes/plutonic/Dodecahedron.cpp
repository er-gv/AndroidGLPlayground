//
// Created by erez on 04/05/2025.
//

#include "Dodecahedron.h"
#include "../../../engine/libs/glm/glm.hpp"
#include "../../../engine/libs/glm/gtc/matrix_transform.hpp"
#include "../../../engine/libs/glm/gtc/type_ptr.hpp"

#include "../../../logger.h"
#define LOG_TAG "MONOCHROMATIC_CUBE"

Dodecahedron::Dodecahedron(const Scene& scene, Material *material) : Model{scene, material}{}
Dodecahedron::~Dodecahedron(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

bool Dodecahedron::init(){

    p_material->addAttribute(std::make_tuple(std::string{"aPosition"}, 3, 0));

    p_material->addUniform("uColor");
    p_material->addUniform("u_mat_mvp");
    //p_material->addUniform("uLightDirection");
    //p_material->addUniform("uFaceNormal");

    return initVBO();

}

bool Dodecahedron::initVBO() {

    const auto phi{1.618034f};
    const auto invphi{1.0f/phi};

    const GLfloat vertices[]{
            +1.0000, +1.0000, 1.0000,// 0
            +1.0000, +1.0000, -1.0000,
            +1.0000, -1.0000, +1.0000,
            +1.0000, -1.0000, -1.0000,

            -1.0000, +1.0000, 1.0000,
            -1.0000, +1.0000, -1.0000,
            -1.0000, -1.0000, +1.0000,
            -1.0000, -1.0000, -1.0000,

            //green set, bottom - top, Y axis to +-phi
            0, +phi, +invphi,  //9
            0, +phi, -invphi,
            0, -phi, +invphi,
            0, -phi, -invphi,

            //blue set, left - right, X axis to +-phi
            +phi,+invphi,  0.f,//13
            -phi,+invphi,  0.f,//14
            +phi,-invphi,  0.f,//15
            -phi,-invphi,  0.f,//16

            //red group
            //red set, front - back, Z axis to +-phi
            0, +invphi, +phi,//17
            0, +invphi,  -phi,
            0, -invphi,+phi,
            0, -invphi,-phi,
    };

    const GLuint indices[]{
            0, 8, 1, 17, 13,
            1, 13, 3, 11, 17,
            1, 19, 7, 15, 13,
            9, 17, 11, 4, 10,
            12, 4, 11, 3, 18,
            3, 13, 15, 8, 18,
            7, 19, 5, 16, 15,
            5, 9, 10, 6, 16,
            2, 14, 12, 10, 6,
            2, 14, 18, 8, 20,
            2, 6, 16, 20, 8,
            4, 12, 14, 20, 16
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


void Dodecahedron::render() const {

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    p_material->populateAttribBuffers();

    p_material->enable();
    auto u_matMVP = p_material->getUniformLocation("u_mat_mvp");
    glUniformMatrix4fv(u_matMVP, 1, GL_FALSE, glm::value_ptr(m_transform()));

    const glm::vec3 colors[]{
        glm::vec3{0.9f, 0.2f, 0.3f},
        glm::vec3{0.8f, 0.3f, 0.4f},
        glm::vec3{0.7f, 0.4f, 0.3f},
        glm::vec3{0.6f, 0.5f, 0.4f},

    };
    
    auto stride = 5u*sizeof(GLuint);
    auto offset = 0u;
    for(int i=0; i<1; ++i){
        p_material->setProperty("uColor", colors[i%4]);
        glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT,
                       reinterpret_cast<const void *>(offset));
        checkGlError("glDrawElements", LOG_TAG);
        offset+=stride;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    p_material->disable();

}

void Dodecahedron::updateState() {

    m_transform.multiply(perFrameTransform);
}
