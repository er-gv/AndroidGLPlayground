//
// Created by erez on 24/05/2025.
//

#include "Icosahedron.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "../../logger.h"
#define LOG_TAG "ICOSAHEDRON"

Icosahedron::~Icosahedron(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(mProgram);
}

bool Icosahedron::init(){
    initGeometry();
    initShader();
    return true;
}

bool Icosahedron::initShader(){
    const auto vertexShaderSrc ="shaders/chess/vertex.glsl";
    const auto fragmentShaderSrc ="shaders/chess/fragment.glsl";
    mProgram = ShadersBuilder::buildGLProgram(vertexShaderSrc,
                                              fragmentShaderSrc);
    if (!mProgram) {
        log_error(LOG_TAG, "Could not create program.");
        return false;
    }

    aPositionHandle = glGetAttribLocation(mProgram, "a_Position");
    checkGlError("glGetAttribLocation", LOG_TAG);
    log_debug(LOG_TAG,"glGetAttribLocation(\"aPosition\") = %u\n", aPositionHandle);


    uEvenColorHandle = glGetUniformLocation(mProgram, "uEvenColor");
    checkGlError("glGetUniformLocation", LOG_TAG);
    log_info(LOG_TAG, "glGetUniformLocation(\"uEvenColor\") = %d\n", uEvenColorHandle);

    uOddColorHandle = glGetUniformLocation(mProgram, "uOddColor");
    checkGlError("glGetUniformLocation", LOG_TAG);
    log_info(LOG_TAG, "glGetUniformLocation(\"uOddColor\") = %d\n", uOddColorHandle);

    uSquareSizeHandle = glGetUniformLocation(mProgram, "uSquareSize");
    checkGlError("glGetUniformLocation", LOG_TAG);
    log_info(LOG_TAG, "glGetUniformLocation(\"uSquareSize\") = %d\n", uSquareSizeHandle);

    uFaceNormalHandle = glGetUniformLocation(mProgram, "uFaceNormal");
    uLightDirectionHandle = glGetUniformLocation(mProgram, "uLightDirection");

    uMatMVPHandle = glGetUniformLocation(mProgram, "u_mat_mvp");
    checkGlError("glGetUniformLocation", LOG_TAG);
    log_info(LOG_TAG, "glGetUniformLocation(\"u_mat_mvp\") = %d\n", uMatMVPHandle);


    return true;

}

bool Icosahedron::initGeometry() {
    const GLfloat PHI = 0.525731f;
    const GLfloat THETA = 0.850651f;
    const GLfloat vertices[]{

            -PHI, 0.0f, +THETA,  // 0
            +PHI, 0.0f, +THETA,   // 1
            -PHI, 0.0f, -THETA, // 2
            +PHI, 0.0f, -THETA,  // 3
            0.0f, +THETA, +PHI,   // 4
            0.0f, +THETA, -PHI,  // 5
            0.0f, -THETA, +PHI,  // 6
            0.0f, -THETA, -PHI, // 7
            +THETA, +PHI, 0.0f,   // 8
            -THETA, +PHI, 0.0f,  // 9
            +THETA, -PHI, 0.0f,  // 10
            -THETA, -PHI, 0.0f
    };
            

    const GLuint indices[]{
            0, 1, 4, 9, 11, 6,1,
            3, 8, 10, 7,2,5,8,
            4, 8, 1, 10, 6, 7, 11, 2, 9, 5, 4, 8
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
    glVertexAttribPointer(aPositionHandle, 3, GL_FLOAT, GL_FALSE, 0,
                          nullptr);
    checkGlError("glVertexAttribPointer", LOG_TAG);
    glEnableVertexAttribArray(aPositionHandle);
    checkGlError("glEnableVertexAttribArray", LOG_TAG);

    glUseProgram(mProgram);
    checkGlError("glUseProgram", LOG_TAG);

    glUniformMatrix4fv(uMatMVPHandle, 1, GL_FALSE, glm::value_ptr(modelview));

    glUniform3f(uSquareSizeHandle, 0.15f, 0.15f, 0.15f);
    glUniform3f(uLightDirectionHandle,glm::cos(glm::radians(30.f)), 1, 1.f);

    glUniform3f(uEvenColorHandle, 0.65, 0.28, 12);
    glUniform3f(uOddColorHandle, 0.93, 0.74,0.05);

    glUniform3f(uFaceNormalHandle, 0.f, 0.f, -1.f);
    auto stride = 3u*sizeof(GLuint);

    unsigned offset{0};
    glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_INT,
                   reinterpret_cast<const void *>(0));
    checkGlError("glDrawElements", LOG_TAG);

    glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_INT,
                   reinterpret_cast<const void *>(8));
    checkGlError("glDrawElements", LOG_TAG);

    glDrawElements(GL_TRIANGLE_FAN, 10, GL_UNSIGNED_INT,
                   reinterpret_cast<const void *>(15));
    checkGlError("glDrawElements", LOG_TAG);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(aPositionHandle);
    glUseProgram(0);

}

void Icosahedron::updateState() {

    static const auto TWO_PI = glm::two_pi<float>();
    m_rotationAngle +=m_delta_angle;
    if(m_rotationAngle > TWO_PI)
        m_rotationAngle -= TWO_PI;
    reset_modelview();
    //scale(glm::vec3{0.35f});
    //rotate(glm::vec3{1.0f, 1.0f, 1.0f}, m_rotationAngle);
    //translate(glm::vec3(-0.0f, 0.f, -0.0f));
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
}
