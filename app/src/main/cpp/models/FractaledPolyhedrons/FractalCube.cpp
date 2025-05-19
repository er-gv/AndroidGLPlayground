//
// Created by erez on 22/04/2025.
//

#include "FractalCube.h"
#include "../../logger.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define LOG_TAG "FRACTAL_CUBE"

bool FractalCube::init(){

    initShader();
    initGeometry();

    return true;
}

bool FractalCube::initShader(){
    auto gVertexShader = "shaders/monochrome_with_normals/vertex.glsl";
    auto gFragmentShader = "shaders/monochrome_with_normals/fragment.glsl";

    mProgram = ShadersBuilder::buildGLProgram(gVertexShader, gFragmentShader);
    if (!mProgram) {
        log_error(LOG_TAG,"Could not create program.");
        return false;
    }
    aPositionHandle = glGetAttribLocation(mProgram, "aPosition");
    checkGlError("glGetAttribLocation", LOG_TAG);
    log_info(LOG_TAG,"glGetAttribLocation(\"aPosition\") = %d\n", aPositionHandle);

    uColorHandle = glGetUniformLocation(mProgram, "uColor");
    checkGlError("glGetUniformLocation", LOG_TAG);
    log_info(LOG_TAG, "glGetUniformLocation(\"uColor\") = %d\n", uColorHandle);


    uFaceNormalHandle = glGetUniformLocation(mProgram, "uFaceNormal");
    uMatMVPHandle = glGetUniformLocation(mProgram, "u_mat_mvp");
    return true;
}


void FractalCube::initGeometry(){



    const GLfloat triangleVertices[] = {+0.0f, +0.00f, +0.00f,
                                        +0.75f, -1.55f, +0.75f,
                                        +0.75f, -1.55f, -0.75f,
                                        -0.75f, -1.55f,-0.75f,
                                        -0.75f, -1.55f,+0.75f
    };


    glGenBuffers(1, &VBO);

    //triangleGeometry
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    //triangle faces
    const GLuint faces[] = {0, 1, 2,
                            0,2,3,
                            0,3,4,
                            0,4, 1};

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces),
                 faces, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void FractalCube::render() const{


    glUseProgram(mProgram);
    checkGlError("glUseProgram", LOG_TAG);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(aPositionHandle, 3, GL_FLOAT, GL_FALSE, 0,
                          nullptr);
    checkGlError("glVertexAttribPointer", LOG_TAG);
    glEnableVertexAttribArray(aPositionHandle);
    checkGlError("glEnableVertexAttribArray", LOG_TAG);


    glm::mat4 rot{glm::rotate(mvp, glm::radians((float)m_rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f))};
    glUniformMatrix4fv(uMatMVPHandle, 1, GL_FALSE, glm::value_ptr(rot));
    auto stride{3 * sizeof(GLuint)};
    unsigned offset{0};
    for(auto triangleColor : triangleColors){
        glUniform3f(uColorHandle,10, 10,10);
        //glUniform3f(uFaceNormalHandle, normals[i].x, normals[i].y, normals[i].z);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, reinterpret_cast<const void *>(offset));
        checkGlError("glDrawElements", LOG_TAG);
        offset+=3;
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(aPositionHandle);
    glUseProgram(0);

}

void FractalCube::updateState(){

    m_rotationAngle += m_delta_angle;
    if(m_rotationAngle > 360)
        m_rotationAngle -= 360;

}
