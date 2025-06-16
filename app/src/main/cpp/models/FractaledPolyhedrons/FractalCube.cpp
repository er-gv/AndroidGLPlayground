//
// Created by erez on 22/04/2025.
//

#include "FractalCube.h"
#include "../../logger.h"
#include "../../engine/libs/glm/gtc/matrix_transform.hpp"
#include "../../engine/libs/glm/gtc/type_ptr.hpp"
#include "../../engine/materials/Material.h"

#define LOG_TAG "FRACTAL_CUBE"

FractalCube::~FractalCube(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    delete material;
}

bool FractalCube::init(){

    initGeometry();
    return initMaterial();
}


bool FractalCube::initMaterial() {

    const char* textureName{"texture/bumpy_bricks_public_domain.jpg"};
    auto texture = loadTextureFromAsset(textureName);
    material->addTexture(texture);

    auto attributesInitialized = material->addAttributes(std::vector<std::tuple< const char*, GLsizei, GLsizei>> {
            {"a_Position", 3, 0},
    });
    auto uniformsInitialized = material->addUniforms(std::vector<const char*>{
            "u_juliaSeedPoint", "u_matMVP", "u_matMVP", "u_matMVP"
            /*, "u_MVMatrix",  "u_NormalsMatrix",
            "u_faceNormal",    "u_LightPos",
            "u_Spectrum", "u_SpectrumCoords", "u_juliaSeedPoint"*/
    });

    return uniformsInitialized && attributesInitialized;



 /*   {
        auto pos{glGetUniformLocation(material->glProgram, "u_MVPMatrix")};
        log_debug(LOG_TAG, "uniform %s is %d", "u_MVPMatrix", pos);
    }
    {
        auto pos{glGetUniformLocation(material->glProgram, "u_MVMatrix")};
        log_debug(LOG_TAG, "uniform %s is %d", "u_MVMatrix", pos);
    }
    {
        auto pos{glGetUniformLocation(material->glProgram, "u_LightPos")};
        log_debug(LOG_TAG, "uniform %s is %d", "u_LightPos", pos);
    }

    {
        auto pos{glGetUniformLocation(material->glProgram, "u_Spectrum")};
        log_debug(LOG_TAG, "uniform %s is %d", "u_Spectrum", pos);
    }
    {
        auto pos{glGetUniformLocation(material->glProgram, "u_SpectrumCoords")};
        log_debug(LOG_TAG, "uniform %s is %d","u_SpectrumCoords", pos);
    }
    {
        auto pos{glGetUniformLocation(material->glProgram, "u_juliaSeedPoint")};
        log_debug(LOG_TAG, "uniform %s is %d","u_juliaSeedPoint", pos);
    }
*/

    return uniformsInitialized && attributesInitialized;
}


void FractalCube::initGeometry(){

    const GLfloat triangleVertices[] = {
            +0.0f, +0.4f, +0.0f, 1.0,//0
            -0.5f, -0.6f, +0.5f, 1.0,//1
            +0.5f, -0.6f, +0.5f, 1.0,//2
            +0.5f, -0.6f, -0.5f, 1.0,//3
            -0.5f, -0.6f, -0.5f, 1.0,//4
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
    material->populateAttribBuffers();
    material->enable();

    glUniformMatrix4fv(material->getUniformLocation("u_matMVP"), 1, GL_FALSE, glm::value_ptr(transform()));
    glm::vec3 light(0,0, -1);
    glUniform3fv(material->getUniformLocation("u_LightPos"), 3, glm::value_ptr(light));



    unsigned offset{0};
    glUniform2f(material->getUniformLocation("u_SpectrumCoords"), spectrum[0], spectrum[1]);
    glUniform2f(material->getUniformLocation("u_juliaSeedPoint"), seedPoint.x, seedPoint.y);
    glActiveTexture(GL_TEXTURE0); // Activate texture unit 0
    glBindTexture(GL_TEXTURE_2D, material->getTexture(0));
    glUniform1i(material->getUniformLocation("u_Spectrum"), 0);

    for(auto k=0; k< 6; ++k ) {
        glUniform3f(material->getUniformLocation("u_faceNormal"), normals[k].x, normals[k].y, normals[k].z);
        glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, reinterpret_cast<const void *>(offset*sizeof(GLuint)));
        checkGlError("glDrawElements", LOG_TAG);
        offset+=4;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    material->disable();

}

void FractalCube::updateState(){

    m_rotationAngle += m_delta_angle;
    if(m_rotationAngle > 360)
        m_rotationAngle -= 360;
    transform.reset();
    transform.translate(glm::vec3(0.0f, 0.3f, -.3f));
    transform.scale(glm::vec3(0.6f, 1.0f, 0.6f));
    transform.rotate(glm::radians(m_rotationAngle), glm::vec3(0.0f, 1.0f, 1.0f));
    std::this_thread::sleep_for(std::chrono::milliseconds(2));

}


void FractalCube::setSeedPoint(glm::vec2 seed){

}

void FractalCube::setSpectrum(float left, float right){

}

FractalCube::FractalCube(Material *material) : Model(material) {}

