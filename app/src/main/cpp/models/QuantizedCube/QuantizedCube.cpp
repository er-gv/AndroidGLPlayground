//
// Created by erez on 22/04/2025.
//

#include "QuantizedCube.h"
#include "../../logger.h"
#include "../../engine/libs/glm/glm.hpp"
#include "../../engine/libs/glm/gtc/matrix_transform.hpp"
#include "../../engine/libs/glm/gtc/type_ptr.hpp"
#define LOG_TAG "QUANTIZED_CUBE"
QuantizedCube::QuantizedCube(const Scene& scene, Material *material) : Model{scene, material}{}
QuantizedCube::~QuantizedCube(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

bool QuantizedCube::init(){
    initMaterial();
    initModel();
    return true;
}

void QuantizedCube::initModel(){
    const GLfloat mTriangleData[]{ // position xyz - color rgb

        //four vertices for front faces

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            +0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
            -0.5f, +0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            +0.5f, +0.5f, 0.5f, 0.0f, 1.0f, 0.0f,

            // four vertices for back faces
            +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            +0.5f, +0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, +0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
    };

    const GLuint indices[]{
        0,1,2,3,
        7,6,5,4,
        7,5,2,0,
        4,6,1,3,
        3,6,2, 7,
        4,1,5,0};


    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mTriangleData),
                 mTriangleData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
                 indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

bool QuantizedCube::initMaterial(){

    p_material->addAttribute(std::make_tuple(std::string{"a_Position"}, 3, 0));
    p_material->addAttribute(std::make_tuple(std::string{"a_Color"}, 3, 3));

    p_material->addUniform(std::string{"u_MVPMatrix"});
    p_material->addUniform(std::string{"u_Quanta"});
    //p_material->addUniform(std::string{"u_FaceNormal"});

    p_material->enable();
    p_material->setProperty("u_Quanta", 8.0f);
    p_material->disable();

    return true;
}

void QuantizedCube::render() const {

    p_material->enable();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    p_material->populateAttribBuffers();
    p_material->setProperty("u_MVPMatrix", m_transform());

    for( unsigned i=0; i<6; ++i) {
        glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void *) (i * 4 * sizeof(unsigned)));
        checkGlError("glDrawElement", LOG_TAG);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    p_material->disable();
}


void QuantizedCube::updateState() {

    transform().multiply(perFrameTransform);

}
