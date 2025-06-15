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

ChessCube::ChessCube(Material* material) : material{material}{};
ChessCube::~ChessCube(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

bool ChessCube::init(){

    //{std::pair<const char* , VertexAttribute>{"aPosition", {3, 0}}};
    auto attributesInitialized = material->addAttributes(std::vector<std::tuple< const char*, GLsizei, GLsizei>> {
            std::make_tuple("aPosition", 3, 0)
    });
    auto uniformsInitialized = material->addUniforms(std::vector<const char*>{
            "uLightDirection", "u_mat_mvp", "uFaceNormal",
            "uSquareSize",    "uEvenColor", "uOddColor"
    });

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
    material->populateAttribBuffers();
    material->enable();

    glUniformMatrix4fv(material->getUniformLocation("u_mat_mvp"), 1, GL_FALSE, glm::value_ptr(transform()));


    auto stride = 4u*sizeof(GLuint);
    auto offset = 0u;
    glUniform3f(material->getUniformLocation("uEvenColor"), 1.0, 0.0, 0.0);
    glUniform3f(material->getUniformLocation("uOddColor"), 0.0, 1.0, 0.0);
    glUniform3f(material->getUniformLocation("uSquareSize"), 0.25, 0.25, 0.25);
    glUniform3f(material->getUniformLocation("uLightDirection"),glm::cos(glm::radians(30.f)), 1, 1.f);

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
        glUniform3f(material->getUniformLocation("uFaceNormal"), faceNormals[k],faceNormals[k+1],faceNormals[k+2]);
        glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT,
                       reinterpret_cast<const void *>(offset));
        checkGlError("glDrawElements", LOG_TAG);
        offset+=stride;
    }


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    material->disable();


}

void ChessCube::updateState() {

    auto static TWO_PI{glm::two_pi<float>()};
    const float m_delta_angle{glm::pi<float>()/250.f};

    static float m_rotationAngle{0.f};

    if(m_rotationAngle > TWO_PI)
        m_rotationAngle -= TWO_PI;
    transform.reset();
    //translate(-pivot);
    transform.scale(glm::vec3{0.35f});
    transform.rotate(m_rotationAngle, glm::vec3{-1.0f, 1.0f, 1.0f});
    transform.translate(glm::vec3(-0.60f, 0.6f, -.4f));

    m_rotationAngle +=m_delta_angle;
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
}
