//
// Created by erez on 22/04/2025.
//

#include "QuantizedCube.h"
#include "../../logger.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <thread>
#include <chrono>
#define LOG_TAG "QUANTIZED_CUBE"

QuantizedCube::~QuantizedCube(){
    glDeleteProgram(mProgram);
    glDeleteBuffers(1, &VBO);
}

bool QuantizedCube::init(){
    if(!initMaterial()){
        return false;
    }
    initModel();

    return true;

}

void QuantizedCube::initModel(){
    const GLfloat mTriangleData[]{ // position xyz - color rgb

        //four vertices for front faces

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            +0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
            -0.5f, +0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
            +0.5f, +0.5f, 0.5f, 0.0f, 1.0f, 0.0f,

            // four vertices for back faces
            +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            +0.5f, +0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, +0.5f, -0.5f, 1.0f, 1.0f, 0.0f,



    };

    const GLuint indices[]{
        0,1,2,3,
        7,6,5,4,
        7,5,2,0,
        4,6,1,3,
        3,6,2, 7,
        4,1,5,0};


    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
                 indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mTriangleData),
                 mTriangleData, GL_STATIC_DRAW);



}

bool QuantizedCube::initMaterial(){

    const auto vertexShaderSrc ="shaders/vertex/color_vertex_shader.glsl";
    const auto fragmentShaderSrc ="shaders/fragment/quantized_color_fragment_shader.glsl";
    mProgram = ShadersBuilder::buildGLProgram(vertexShaderSrc,
                                              fragmentShaderSrc);
    if (!mProgram) {
        log_error(LOG_TAG, "Could not create program.");
        return false;
    }

    uMatMVPHandle = glGetUniformLocation(mProgram, "u_MVPMatrix");
    uniformLocations.insert(std::make_pair("u_MVPMatrix", uMatMVPHandle));
    if(checkGlError("glGetUniformLocation", LOG_TAG))
        return false;

    uQuantaHandle = glGetUniformLocation(mProgram, "u_Quanta");
    uniformLocations.insert(std::make_pair("u_Quanta", uQuantaHandle));
    if(checkGlError("glGetUniformLocation", LOG_TAG))
        return false;


    aColorHandle = glGetAttribLocation(mProgram, "a_Color");
    attribLocations.insert(std::make_pair("a_Color", aColorHandle));
    if(checkGlError("glGetUniformLocation", LOG_TAG))
        return false;

    aPositionHandle = glGetAttribLocation(mProgram, "a_Position");
    attribLocations.insert(std::make_pair("a_Position", aPositionHandle));
    if(checkGlError("glGetAttribLocation", LOG_TAG))
        return false;

    return true;
}

void QuantizedCube::render() const {

    glUseProgram(mProgram);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(aPositionHandle, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)nullptr);
    checkGlError("glVertexAttribPointer", LOG_TAG);
    glEnableVertexAttribArray(aPositionHandle);

    glVertexAttribPointer(aColorHandle, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    checkGlError("glVertexAttribPointer", LOG_TAG);
    glEnableVertexAttribArray(aColorHandle);

    auto mvp = glm::mat4(1.0f);
    mvp = glm::rotate(mvp, glm::radians((float)m_rotationAngle), rotation_axis);

    glUniformMatrix4fv(uMatMVPHandle, 1, GL_FALSE, glm::value_ptr(mvp));
    glUniform1f(uQuantaHandle, quanta);

    checkGlError("glUseProgram", LOG_TAG);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void *) 0);
    checkGlError("glDrawElement", LOG_TAG);
    for( unsigned i=0; i<6; ++i) {
        glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void *) (i * 4 * sizeof(unsigned)));
        checkGlError("glDrawElement", LOG_TAG);
    }
    glLineWidth(2.0f);

    for( unsigned i=0; i<6; ++i) {
        glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, (void *) (i * 4 * sizeof(unsigned)));
        checkGlError("glDrawElement", LOG_TAG);
    }
    glVertexAttribPointer(aColorHandle, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    checkGlError("glVertexAttribPointer", LOG_TAG);
    glEnableVertexAttribArray(aColorHandle);

}

void QuantizedCube::updateState() {

    m_rotationAngle +=0.2;
    if(m_rotationAngle > 360.0f)
        m_rotationAngle-=360.0f;

    std::this_thread::sleep_for(std::chrono::milliseconds(2));
}
