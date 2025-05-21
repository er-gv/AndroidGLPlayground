//
// Created by erez on 04/05/2025.
//

#include "MonochromeCube.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//
// Created by erez on 22/04/2025.
//

#include "../../logger.h"
#define LOG_TAG "MONOCHROMATIC_CUBE"

bool MonochromeCube::init(){
    const auto vertexShaderSrc ="shaders/vertex/monochrome_face_vertex.glsl";
    const auto fragmentShaderSrc ="shaders/fragment/monochrome_face_fragment.glsl";
    mProgram = ShadersBuilder::buildGLProgram(vertexShaderSrc,
                                              fragmentShaderSrc);
    if (!mProgram) {
        log_error(LOG_TAG, "Could not create program.");
        return false;
    }

    aPositionHandle = glGetAttribLocation(mProgram, "a_Position");
    checkGlError("glGetAttribLocation", LOG_TAG);
    log_debug(LOG_TAG,"glGetAttribLocation(\"aPosition\") = %u\n", aPositionHandle);


    uColorHandle = glGetUniformLocation(mProgram, "uColor");
    checkGlError("glGetUniformLocation", LOG_TAG);
    log_info(LOG_TAG, "glGetUniformLocation(\"uColor\") = %d\n", uColorHandle);

    u_matMVP = glGetUniformLocation(mProgram, "u_MVPMatrix");
    checkGlError("glGetUniformLocation", LOG_TAG);
    log_info(LOG_TAG, "glGetUniformLocation(\"u_mat_mvp\") = %d\n", uColorHandle);

    //u_matMV = glGetUniformLocation(mProgram, "u_mat_mv");
    //checkGlError("glGetUniformLocation", LOG_TAG);
    //log_info(LOG_TAG, "glGetUniformLocation(\"u_mat_mv\") = %d\n", uColorHandle);
    /*
     uNormalHandle = glGetUniformLocation(mProgram, "uNormal");
    LOGI("glGetUniformLocation(\"uNormal\") = %d\n", uNormalHandle);
    uMatMVHandle = glGetUniformLocation(mProgram, "uMat_MV");
    LOGI("glGetUniformLocation(\"uMat_MV\") = %d\n", uMatMVHandle);
    uMatMVPHandle = glGetUniformLocation(mProgram, "uMat_MVP");
    LOGI("glGetUniformLocation(\"uMat_MVP\") = %d\n", uMatMVPHandle);
     */
    return initVBO();

}

bool MonochromeCube::initVBO() {

    const GLfloat verices[]{

            -0.2f, +0.5f, +0.4f,
            +0.2f, +0.5f, +0.4f,
            -0.8f, -0.8f, +0.6f,
            +0.8f, -0.8f, +0.6f,

            +0.8f, -0.8f, -0.6f,
            +0.8f, -0.8f, +0.6f,
            +0.2f, +0.5f, -0.4f,
            +0.2f, +0.5f, +0.4f,

            -0.2f, +0.5f, -0.4f,
            -0.2f, +0.5f, +0.4f,
            -0.8f, -0.8f, -0.6f,
            -0.8f, -0.8f, +0.6f,

            -0.8f, -0.8f, -0.6f,
            +0.8f, -0.8f, -0.6f,
            -0.2f, +0.5f, -0.4f,
            +0.2f, +0.5f, -0.4f,
};
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verices), verices, GL_STATIC_DRAW);
    return true;
}
void MonochromeCube::render() const {


    glVertexAttribPointer(aPositionHandle, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat),
                          (void*)0);
    checkGlError("glVertexAttribPointer", LOG_TAG);
    glEnableVertexAttribArray(aPositionHandle);
    checkGlError("//glEnableVertexAttribArray", LOG_TAG);

    glUseProgram(mProgram);
    glm::mat4 mvp = glm::mat4(1.0f);
    mvp = glm::rotate(mvp, glm::radians((float)m_rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    mvp = glm::translate(mvp, glm::vec3(0.0f, 0.2f, 0.0f));
    mvp = glm::scale(mvp, glm::vec3(0.75f, 0.75f, 0.75f));
    glUniformMatrix4fv(u_matMVP, 1, GL_FALSE, glm::value_ptr(mvp));

    glUniform3f(uColorHandle, 0.2f, 0.9f, 0.3f);
    checkGlError("glUniform3f", LOG_TAG);
    glDrawArrays(GL_TRIANGLE_STRIP, 12, 4);
    checkGlError("glDrawArrays", LOG_TAG);

    glUniform3f(uColorHandle, 0.9f, 0.1f, 0.9f);
    glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
    checkGlError("glDrawArrays", LOG_TAG);

    glUniform3f(uColorHandle, 0.9f, 0.7f, 0.1f);
    glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);
    checkGlError("glDrawArrays", LOG_TAG);

    //glUniform3f(uColorHandle, 0.2f+grey*0.6f, 0.3f, 0.3f*grey+0.1f);
    //checkGlError("glUniform3f", LOG_TAG);
    glUniform3f(uColorHandle, 0.9f, 0.2f, 0.3f);
    checkGlError("glUniform3f", LOG_TAG);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    checkGlError("glDrawArrays", LOG_TAG);

    glUseProgram(0);

}

void MonochromeCube::updateState() {


    if (grey > 1.0f || grey < 0.0f) {
        sign = -sign;
    }
    grey += sign * 0.01f;

    m_rotationAngle +=1.2;
    if(m_rotationAngle > 360.0f)
        m_rotationAngle -= 360.0f;
}
