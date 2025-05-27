//
// Created by erez on 22/04/2025.
//

#include "FractalCube.h"
#include "../../logger.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define LOG_TAG "FRACTAL_CUBE"

FractalCube::~FractalCube(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(mProgram);
}
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
    lightDirectionHandle = glGetUniformLocation(mProgram, "lightDirection");

    uMatMVPHandle = glGetUniformLocation(mProgram, "u_mat_mvp");
    return true;
}


void FractalCube::initGeometry(){

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
                            0,4,1
                            };

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces),
                 faces, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}

void FractalCube::render() const{

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glVertexAttribPointer(aPositionHandle, 3, GL_FLOAT, GL_FALSE, 0,
                          nullptr);
    checkGlError("glVertexAttribPointer", LOG_TAG);
    glEnableVertexAttribArray(aPositionHandle);
    checkGlError("glEnableVertexAttribArray", LOG_TAG);

    glUseProgram(mProgram);
    checkGlError("glUseProgram", LOG_TAG);

    //glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.3f, -6.3f))
    //modelview = glm::scale(modelview, glm::vec3(0.75f, 0.75f, 0.75f));
    glUniformMatrix4fv(uMatMVPHandle, 1, GL_FALSE, glm::value_ptr(modelview));
    glm::vec3 light(0,0, -1);
    glUniform3fv(lightDirectionHandle, 3, glm::value_ptr(light));

    unsigned offset{0};


    glLineWidth(2.0f);


    for(auto k=0; k< 4; ++k ) {
        glUniform3i(uColorHandle, triangleColors[k].r, triangleColors[k].g, triangleColors[k].b);
        glUniform3f(uFaceNormalHandle, normals[k].x, normals[k].y, normals[k].z);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, reinterpret_cast<const void *>(offset*sizeof(GLuint)));
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
    reset_modelview();
    translate(glm::vec3(0.0f, 0.3f, -.3f));
    scale(glm::vec3(0.6f, 1.0f, 0.6f));
    rotate(glm::vec3(0.0f, 1.0f, 1.0f), glm::radians(m_rotationAngle));
    std::this_thread::sleep_for(std::chrono::milliseconds(2));

}
