//
// Created by erez on 04/05/2025.
//

#include "ChessCube.h"
#include "../../engine/libs/glm/glm.hpp"
#include "../../engine/libs/glm/gtc/matrix_transform.hpp"
#include "../../engine/libs/glm/gtc/type_ptr.hpp"

//
// Created by erez on 22/04/2025.
//

#include "../../logger.h"
#define LOG_TAG "MONOCHROMATIC_CUBE"

ChessCube::ChessCube(const Scene& scene, Material* material) :Model{scene,  material}{};
ChessCube::~ChessCube(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

bool ChessCube::init(){

    auto attributesInitialized = p_material->addAttributes({std::make_tuple(std::string{"aPosition"}, 3, 0)});
    auto uniformsInitialized = p_material->addUniforms({"u_mat_mvp", "uLightDirection", "uFaceNormal", "uSquareSize", "uEvenColor", "uOddColor"});
    return uniformsInitialized && attributesInitialized && initVBO();

}

bool ChessCube::initVBO() {

    const GLfloat vertices[]{

            -0.7f, +0.7f, +0.7f,  //0
            +0.7f, +0.7f, +0.7f,  //1
            +0.7f, -0.7f, +0.7f, //2
            -0.7f, -0.7f, +0.7f,  //3

            -0.7f, -0.7f, -0.7f, //4
            +0.7f, -0.7f, -0.7f,  //5
            -0.7f, +0.7f, -0.7f,  //6
            +0.7f, +0.7f, -0.7f,  //7
    };

    const GLuint indices[]{
        0, 1, 3, 2, //front 0,0,1
        1,7,2,5,//right 1, 0 0,
        3,4,0,6,//left -1, 0,0
        6,7,0,1,//top 0,1,0
        3,2,4,5,//bottom 0,-1,0
        4,5,6,7//back0,0,-1
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


void ChessCube::render() const {


    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    p_material->populateAttribBuffers();
    p_material->enable();

    p_material->setProperty("u_mat_mvp", m_transform());


    auto stride = 4u*sizeof(GLuint);
    auto offset = 0u;
    p_material->setProperty("uEvenColor", glm::vec3{0.f, 0.3f, 1.0});
    p_material->setProperty("uOddColor", glm::vec3{1.0, 1.0, 0.0});
    p_material->setProperty("uSquareSize", glm::vec3{0.25f});
    p_material->setProperty("uLightDirection" ,glm::cos(glm::radians(30.f)));

    const GLfloat faceNormals[]{
      0.f,0.f,1.f,
      1.f,0.f,0.f,
      -1.f,0.f,0.f,
      0.f,1.f,0.f,
      0.f,-1.f,0.f,
      0.f,0.f,-1.f
    };

    for(auto i=0; i<6; ++i){
        auto k =3*i;
        glUniform3f(p_material->getUniformLocation("uFaceNormal"), faceNormals[k],faceNormals[k+1],faceNormals[k+2]);
        glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT,
                       reinterpret_cast<const void *>(offset));
        checkGlError("glDrawElements", LOG_TAG);
        offset+=stride;
    }


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    p_material->disable();


}

void ChessCube::updateState() {

    transform().multiply(perFrameTransform);
}
