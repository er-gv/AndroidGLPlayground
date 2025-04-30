//
// Created by erez on 22/04/2025.
//

#include "QuantizedCube.h"
#include "../../logger.h"
#include "../../gl_logging.h"
#define LOG_TAG "QUANTIZED_CUBE"

bool QuantizedCube::init(){
    const auto vertexShaderSrc ="shaders/hello_vs.glsl";
    const auto fragmentShaderSrc ="shaders/hello_fs.glsl";
    mProgram = ShadersBuilder::buildGLProgram(vertexShaderSrc,
                                             fragmentShaderSrc);
    if (!mProgram) {
        log_error(LOG_TAG, "Could not create program.");
        return false;
    }
    GLuint aTexCoordHandle = glGetAttribLocation(mProgram, "aTexCoord");
    aPositionHandle = glGetAttribLocation(mProgram, "aPosition");
    checkGlError("glGetAttribLocation", LOG_TAG);
    log_error(LOG_TAG,"glGetAttribLocation(\"aPosition\") = %u\n", aPositionHandle);

    /*
    uColorHandle = glGetUniformLocation((mProgram, "uColor");
    LOGI("glGetUniformLocation(\"uColor\") = %d\n", uColorHandle);
    uNormalHandle = glGetUniformLocation(mProgram, "uNormal");
    LOGI("glGetUniformLocation(\"uNormal\") = %d\n", uNormalHandle);
    uMatMVHandle = glGetUniformLocation(mProgram, "uMat_MV");
    LOGI("glGetUniformLocation(\"uMat_MV\") = %d\n", uMatMVHandle);
    uMatMVPHandle = glGetUniformLocation(mProgram, "uMat_MVP");
    LOGI("glGetUniformLocation(\"uMat_MVP\") = %d\n", uMatMVPHandle);
     */
    return true;

}

void QuantizedCube::render() const {
    glClearColor(grey, grey*0.03f, grey*0.85f, 1.0f);
    checkGlError("glClearColor", LOG_TAG);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear", LOG_TAG);

    glUseProgram(mProgram);
    checkGlError("glUseProgram", LOG_TAG);

    glVertexAttribPointer(aPositionHandle, 2, GL_FLOAT, GL_FALSE, 0,
                          mTriangleVertices);
    checkGlError("glVertexAttribPointer", LOG_TAG);
    glEnableVertexAttribArray(aPositionHandle);
    checkGlError("glEnableVertexAttribArray", LOG_TAG);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    checkGlError("glDrawArrays", LOG_TAG);
}

void QuantizedCube::updateState() {


    if (grey > 1.0f || grey < 0.0f) {
        sign = -sign;
    }
    grey += sign * 0.01f;
}
