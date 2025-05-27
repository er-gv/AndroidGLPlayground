//
// Created by erez on 04/05/2025.
//

#include "ChessCube.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//
// Created by erez on 22/04/2025.
//

#include "../../logger.h"
#define LOG_TAG "MONOCHROMATIC_CUBE"

ChessCube::~ChessCube(){
    glDeleteBuffers(1, &vbo);
    //glDeleteBuffers(1, &EBO);
    glDeleteProgram(mProgram);
}

bool ChessCube::init(){
    const auto vertexShaderSrc ="shaders/chess/vertex.glsl";
    const auto fragmentShaderSrc ="shaders/chess/fragment.glsl";
    mProgram = ShadersBuilder::buildGLProgram(vertexShaderSrc,
                                              fragmentShaderSrc);
    if (!mProgram) {
        log_error(LOG_TAG, "Could not create program.");
        return false;
    }

    aPositionHandle = glGetAttribLocation(mProgram, "aPosition");
    checkGlError("glGetAttribLocation", LOG_TAG);
    log_info(LOG_TAG,"glGetAttribLocation(\"aPosition\") = %d\n", aPositionHandle);

    uSquareSizeHandle = glGetUniformLocation(mProgram, "uSquareSize");
    uOddColorHandle = glGetUniformLocation(mProgram, "uOddColor");
    uEvenColorHandle = glGetUniformLocation(mProgram, "uEvenColor");

    checkGlError("glGetUniformLocation", LOG_TAG);
    log_info(LOG_TAG, "glGetUniformLocation(\"uSquareSizeolor\") = %d\n", uSquareSizeHandle);


    uFaceNormalHandle = glGetUniformLocation(mProgram, "uFaceNormal");
    uLightDirectionHandle = glGetUniformLocation(mProgram, "uLightDirection");
    uMatMVPHandle = glGetUniformLocation(mProgram, "u_mat_mvp");

    return initVBO();

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

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return true;
}


void ChessCube::render() const {

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glVertexAttribPointer(aPositionHandle, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat),
                          (void*) nullptr);
    checkGlError("glVertexAttribPointer", LOG_TAG);
    glEnableVertexAttribArray(aPositionHandle);
    checkGlError("glEnableVertexAttribArray", LOG_TAG);


    glUseProgram(mProgram);
    glUniformMatrix4fv(uMatMVPHandle, 1, GL_FALSE, glm::value_ptr(modelview));


    auto stride = 4u*sizeof(GLuint);
    auto offset = 0u;
    glUniform3f(uEvenColorHandle, 1.0, 0.0, 0.0);
    glUniform3f(uOddColorHandle, 0.0, 1.0, 0.0);
    glUniform3f(uSquareSizeHandle, 0.25, 0.25, 0.25);
    glUniform3f(uLightDirectionHandle,glm::cos(glm::radians(30.f)), 1, 1.f);

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
        glUniform3f(uFaceNormalHandle, faceNormals[k],faceNormals[k+1],faceNormals[k+2]);
        glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT,
                       reinterpret_cast<const void *>(offset));
        checkGlError("glDrawElements", LOG_TAG);
        offset+=stride;
    }


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(aPositionHandle);
    glUseProgram(0);

}

void ChessCube::updateState() {

    auto static TWO_PI{glm::two_pi<float>()};
    m_rotationAngle +=m_delta_angle;
    if(m_rotationAngle > TWO_PI)
        m_rotationAngle -= TWO_PI;
    reset_modelview();
    //translate(-pivot);
    scale(glm::vec3{0.35f});
    rotate(glm::vec3{-1.0f, 1.0f, 1.0f}, m_rotationAngle);
    translate(glm::vec3(1.60f, 0.6f, 0.0f));
    //translate(pivot);
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
}
