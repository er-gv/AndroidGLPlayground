//
// Created by erez on 22/05/2025.
//
#include "OrangePyramid.h"
#include "../../logger.h"
#include "../../engine/shadersBuilder.h"
#include "../../engine/libs/glm/gtc/matrix_transform.hpp"
#include "../../engine/libs/glm/gtc/type_ptr.hpp"
#define LOG_TAG "FRACTAL_CUBE"

OrangePyramid::~OrangePyramid(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(mProgram);
}

bool OrangePyramid::init(){

    initShader();
    initGeometry();

    return true;
}


bool OrangePyramid::initShader(){
    auto vertexShader = "shaders/monochrome_with_normals/vertex.glsl";
    auto fragmentShader = "shaders/monochrome_with_normals/fragment.glsl";

    mProgram = ShadersBuilder::buildGLProgram(vertexShader, fragmentShader);
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


void OrangePyramid::initGeometry(){

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

void OrangePyramid::render() const{

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glVertexAttribPointer(aPositionHandle, 3, GL_FLOAT, GL_FALSE, 0,
                          nullptr);
    checkGlError("glVertexAttribPointer", LOG_TAG);
    glEnableVertexAttribArray(aPositionHandle);
    checkGlError("glEnableVertexAttribArray", LOG_TAG);

    glUseProgram(mProgram);
    checkGlError("glUseProgram", LOG_TAG);
    glUniformMatrix4fv(uMatMVPHandle, 1, GL_FALSE, glm::value_ptr(transform()));
    glm::vec3 light(0,0, -1);
    glUniform3fv(lightDirectionHandle, 3, glm::value_ptr(light));

    unsigned offset{0};

    for(auto k=0; k< 4; ++k ) {
        glUniform3i(uColorHandle, triangleColors[k].r, triangleColors[k].g, triangleColors[k].b);
        glUniform3f(uFaceNormalHandle, normals[k].x, normals[k].y, normals[k].z);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void *)(offset*sizeof(GLuint)));
        checkGlError("glDrawElements", LOG_TAG);
        offset+=3;
    }


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(aPositionHandle);
    glUseProgram(0);

}

void OrangePyramid::updateState(){

    static const auto TWO_PI{glm::two_pi<float>()};
    static float m_delta_angle{TWO_PI/400};

    if(m_rotationAngle > TWO_PI)
        m_rotationAngle -= TWO_PI;
    transform.reset();
    transform.scale(glm::vec3{0.7f});
    transform.translate(glm::vec3(-0.4f, -0.2f, -0.3f));
    transform.rotate(m_rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    m_rotationAngle += m_delta_angle;
    std::this_thread::sleep_for(std::chrono::milliseconds(2));

}
