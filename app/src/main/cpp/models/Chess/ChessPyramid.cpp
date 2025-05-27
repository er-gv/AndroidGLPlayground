//
// Created by erez on 22/05/2025.
//
#include "ChessPyramid.h"
#include "../../logger.h"
#include "../../engine/shadersBuilder.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define LOG_TAG "CHESS_PYRAMID"

ChessPyramid::~ChessPyramid(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(mProgram);
}
bool ChessPyramid::init(){

    initShader();
    initGeometry();

    return true;
}


bool ChessPyramid::initShader(){
    auto vertexShader = "shaders/chess/vertex.glsl";
    auto fragmentShader = "shaders/chess/fragment.glsl";

    mProgram = ShadersBuilder::buildGLProgram(vertexShader, fragmentShader);
    if (!mProgram) {
        log_error(LOG_TAG,"Could not create program.");
        return false;
    }
    aPositionHandle = glGetAttribLocation(mProgram, "aPosition");
    checkGlError("glGetAttribLocation", LOG_TAG);
    log_info(LOG_TAG,"glGetAttribLocation(\"aPosition\") = %d\n", aPositionHandle);

    uSquareSizeHandle = glGetUniformLocation(mProgram, "uSquareSize");
    uOddColorHandle = glGetUniformLocation(mProgram, "uOddColor");
    uEvenColorHandle = glGetUniformLocation(mProgram, "uEvenColor");

    checkGlError("glGetUniformLocation", LOG_TAG);
    log_info(LOG_TAG, "glGetUniformLocation(\"uSquareSize\") = %d\n", uSquareSizeHandle);


    uFaceNormalHandle = glGetUniformLocation(mProgram, "uFaceNormal");
    uLightDirectionHandle = glGetUniformLocation(mProgram, "uLightDirection");

    uMatMVPHandle = glGetUniformLocation(mProgram, "u_mat_mvp");
    return true;
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
    glVertexAttribPointer(aPositionHandle, 3, GL_FLOAT, GL_FALSE, 0,
                          nullptr);
    checkGlError("glVertexAttribPointer", LOG_TAG);
    glEnableVertexAttribArray(aPositionHandle);
    checkGlError("glEnableVertexAttribArray", LOG_TAG);

    glUseProgram(mProgram);
    checkGlError("glUseProgram", LOG_TAG);
    glUniformMatrix4fv(uMatMVPHandle, 1, GL_FALSE, glm::value_ptr(modelview));


    unsigned offset{0};
    glUniform3f(uSquareSizeHandle, 0.2f, 0.06f, 0.2f);
    glUniform3f(uLightDirectionHandle,glm::cos(glm::radians(30.f)), 1, 1.f);
    glLineWidth(2.0f);

    const GLfloat colors[] = {
            +0.8f, +0.4f, +0.0f, //0
            +0.0f, +0.4f, +0.8f, //1
            +0.8f, +0.2f, +0.8f, //2
            +0.0f, +0.8f, +0.8f, //3
    };

    for(auto k=0; k< 4; ++k ) {
        glUniform3f(uFaceNormalHandle, normals[k].x, normals[k].y, normals[k].z);
        auto colorIndex = 6*(k%2);
        glUniform3f(uEvenColorHandle, colors[colorIndex], colors[colorIndex+1], colors[colorIndex+2]);
        glUniform3f(uOddColorHandle, colors[colorIndex+3], colors[colorIndex+4], colors[colorIndex+5]);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, reinterpret_cast<const void *>(offset*sizeof(GLuint)));
        checkGlError("glDrawElements", LOG_TAG);
        offset+=3;
    }
    //render the bottom face
    glUniform3f(uFaceNormalHandle, 0.f, -1.0, 0.f);
    auto colorIndex = 0;
    glUniform3f(uEvenColorHandle, 0.65, 0.28, 12);
    glUniform3f(uOddColorHandle, 0.95, 0.74,0.25);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, reinterpret_cast<const void *>(offset*sizeof(GLuint)));
    checkGlError("glDrawElements", LOG_TAG);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(aPositionHandle);
    glUseProgram(0);
}


void ChessPyramid::updateState(){

    static const auto TWO_PI{glm::two_pi<float>()};
    m_rotationAngle += m_delta_angle;
    if(m_rotationAngle > TWO_PI)
        m_rotationAngle -= TWO_PI;
    reset_modelview();
    scale(glm::vec3{0.9f});
    translate(glm::vec3(-0.3f, -0.2f, 0.3f));
    rotate(glm::vec3(1.0f, 0.0f, 1.0f), -glm::half_pi<float>()*0.3);
    rotate(glm::vec3(0.0f, 1.0f, 0.0f), m_rotationAngle);
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
}
