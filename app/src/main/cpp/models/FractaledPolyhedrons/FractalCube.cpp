//
// Created by erez on 22/04/2025.
//

#include "FractalCube.h"
#include "../../logger.h"
#include "../../gl_logging.h"

#define LOG_TAG "FRACTAL_CUBE"

bool FractalCube::init(){

    auto gVertexShader = "shaders/quantized_vs.glsl";
    auto gFragmentShader = "shaders/quantized_fs.glsl";

    mProgram = ShadersBuilder::buildGLProgram(gVertexShader, gFragmentShader);
    if (!mProgram) {
        log_error(LOG_TAG,"Could not create program.");
        return false;
    }
    aPositionHandle = glGetAttribLocation(mProgram, "attPosition");
    checkGlError("glGetAttribLocation", LOG_TAG);
    log_info(LOG_TAG,"glGetAttribLocation(\"attPosition\") = %d\n", aPositionHandle);

    aColorHandle = glGetAttribLocation(mProgram, "attColor");
    checkGlError("glGetAttribLocation", LOG_TAG);
    log_info(LOG_TAG, "glGetAttribLocation(\"attColor\") = %d\n", aColorHandle);

    uQuantaHandle = glGetUniformLocation(mProgram, "uQuanta");

    return true;
}

void FractalCube::render() const{
    const GLfloat gTriangleVertices[] = {0.0f, 0.0f, 0.75f, 0.75f, -0.75f, 0.75f,
                                         -0.0f, -0.0f, 0.75f, 0.75f, 0.75f, -0.75f,
                                         0.0f, 0.0f, 0.75f, -0.75f, -0.75f, -0.75f,
                                         -0.0f, -0.0f, -0.75f, 0.75f, -0.75f, -0.75f};


    // -0.5f, -0.2f, 0.95f, 0.5f, 0.5f, -0.8f};
    const GLfloat gTriangleColors[] = {1.0f,0.0f, 0.0f,
                                       0.0f,1.0f, 0.0f,
                                       0.0f,0.0f, 1.0f,

                                       1.0f,1.0f, 0.0f,
                                       0.0f,1.4f, 1.0f,
                                       1.0f,0.0f, 1.0f,

                                       1.0f,0.0f, 0.0f,
                                       0.0f,0.0f, 1.0f,
                                       0.0f,1.0f, 0.0f,

                                       1.0f,1.0f, 0.0f,
                                       1.0f,0.0f, 1.0f,
                                       0.0f,1.0f, 1.0f};

    glClearColor(grey, grey*0.03, grey*0.85, 1.0f);
    checkGlError("glClearColor", LOG_TAG);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear", LOG_TAG);

    glUseProgram(mProgram);
    checkGlError("glUseProgram", LOG_TAG);

    glVertexAttribPointer(aPositionHandle, 2, GL_FLOAT, GL_FALSE, 0,
                          gTriangleVertices);
    checkGlError("glVertexAttribPointer", LOG_TAG);
    glEnableVertexAttribArray(aPositionHandle);
    checkGlError("glEnableVertexAttribArray", LOG_TAG);


    glVertexAttribPointer(aColorHandle, 3, GL_FLOAT, GL_FALSE, 0,
                          gTriangleColors);
    checkGlError("glVertexAttribPointer", LOG_TAG);
    glEnableVertexAttribArray(aColorHandle);
    checkGlError("glEnableVertexAttribArray", LOG_TAG);

    glUniform1f(uQuantaHandle, 8.0f);

    glDrawArrays(GL_TRIANGLES, 0, 12);
    checkGlError("glDrawArrays", LOG_TAG);

}

void FractalCube::updateState(){
    if (grey > 1.0f || grey < 0.0f) {
        sign = -sign;
    }
    grey += 0.005f*sign;
}
