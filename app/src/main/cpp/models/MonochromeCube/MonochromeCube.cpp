//
// Created by erez on 04/05/2025.
//

#include "MonochromeCube.h"
#include "../../engine/libs/glm/glm.hpp"
#include "../../engine/libs/glm/gtc/matrix_transform.hpp"
#include "../../engine/libs/glm/gtc/type_ptr.hpp"

//
// Created by erez on 22/04/2025.
//

#include "../../logger.h"
#define LOG_TAG "MONOCHROMATIC_CUBE"

MonochromeCube::MonochromeCube(const Scene& scene, Material *material) : Model{scene, material}{}
MonochromeCube::~MonochromeCube(){
    glDeleteBuffers(1, &vbo);
    //glDeleteBuffers(1, &EBO);
    glDeleteProgram(mProgram);
}

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


    return initVBO();

}

bool MonochromeCube::initVBO() {

    const GLfloat vertices[]{

            -0.2f, +0.5f, +0.4f,  //0
            +0.2f, +0.5f, +0.4f,  //1
            +0.8f, -0.8f, +0.6f, //2
            -0.8f, -0.8f, +0.6f,  //3

            /*+0.8f, -0.8f, -0.6f,//5
            +0.8f, -0.8f, +0.6f, //2
            +0.2f, +0.5f, -0.4f,  //7
            +0.2f, +0.5f, +0.4f, //1

            -0.2f, +0.5f, -0.4f, //6
            -0.2f, +0.5f, +0.4f, //0
            -0.8f, -0.8f, -0.6f, //4
            -0.8f, -0.8f, +0.6f, //3
*/
            -0.8f, -0.8f, -0.6f, //4
            +0.8f, -0.8f, -0.6f,  //5
            -0.2f, +0.5f, -0.4f,  //6
            +0.2f, +0.5f, -0.4f,  //7
    };

    const GLuint indices[]{
        0, 1, 3, 2,
        1,7,2,5,
        3,4,0,6,
        4,5,6,7
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
void MonochromeCube::render() const {

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glVertexAttribPointer(aPositionHandle, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat),
                          (void*) nullptr);
    checkGlError("glVertexAttribPointer", LOG_TAG);
    glEnableVertexAttribArray(aPositionHandle);
    checkGlError("glEnableVertexAttribArray", LOG_TAG);


    glUseProgram(mProgram);
    //glm::mat4 mvp = glm::mat4(1.0f);
    //mvp = glm::scale(mvp, glm::vec3{0.35f});
    //mvp = glm::rotate(mvp, glm::radians((float)m_rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    //mvp = glm::translate(mvp, glm::vec3(1.60f, 0.2f, 0.0f));


    glUniformMatrix4fv(u_matMVP, 1, GL_FALSE, glm::value_ptr(m_transform()));

    const glm::vec3 colors[]{
        glm::vec3{0.9f, 0.2f, 0.3f},
        glm::vec3{0.2f, 0.9f, 0.3f},
        glm::vec3{0.9f, 0.1f, 0.9f},
        glm::vec3{0.9f, 0.7f, 0.1f},

    };


    auto stride = 4u*sizeof(GLuint);
    auto offset = 0u;
    for(auto i=0; i<4; ++i){
        glUniform3f(uColorHandle, colors[i].r, colors[i].g, colors[i].b);
        checkGlError("glUniform3fv", LOG_TAG);
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

void MonochromeCube::updateState() {

    static const auto TWO_PI = glm::two_pi<float>();
    static const auto rotation_delta {TWO_PI/200};
    static auto m_rotationAngle =0.f;

    if(m_rotationAngle > TWO_PI)
        m_rotationAngle -= TWO_PI;
    m_transform.reset();
    m_transform.translate(glm::vec3(1.60f, 1.3f, 0.0f));
    m_transform.scale(glm::vec3{0.35f});
    m_transform.rotate(m_rotationAngle, glm::vec3{0.0f, 1.0f, 0.0f});

    std::this_thread::sleep_for(std::chrono::milliseconds(2));

    m_rotationAngle +=rotation_delta;
}
