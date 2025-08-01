//
// Created by erez on 14/06/2025.
//

#include <algorithm>
#include "FractalCube.h"

#include "../../logger.h"
#include "../../engine/libs/glm/gtc/matrix_transform.hpp"
#include "../../engine/libs/glm/gtc/type_ptr.hpp"
#include "../../scenes/Scene.h"

#define LOG_TAG "FRACTAL_CUBE"

FractalCube::FractalCube(const Scene& scene, Material *material): Model{scene, material} {

}
FractalCube::~FractalCube(){
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
    delete p_material;
}

bool FractalCube::init(){

    initMaterial();
    initGeometry();

    return true;
}

bool FractalCube::initMaterial() {

    p_material->generateTextures(std::vector<const char*> {"texture/spectrum.jpg"});


    std::vector<std::tuple<const std::string&, GLsizei, GLsizei>> vertices{
        std::make_tuple(std::string{"a_Position"}, 3, 0),
        std::make_tuple(std::string{"a_TexCoordinate"}, 2, 3)
    };
    auto attributesInitialized = std::all_of(vertices.begin(), vertices.end(),
            [&](auto& attrib){return p_material->addAttribute(attrib);}
    );

    const std::string uniforms[]{"u_MVPMatrix", "u_NormalsMatrix", "u_FaceNormal", "u_LightPos",
                            "u_juliaSeedPoint",
                           "u_exponent", "u_SpectrumCoords", "u_Spectrum"};
    bool uniformsInitialized{true};
    for (auto& uni: uniforms) {
        p_material->addUniform(uni);
        uniformsInitialized = uniformsInitialized && (0 >= p_material->getUniformLocation(uni));
    }

    //p_material->logUniforms();
    return  attributesInitialized && uniformsInitialized;

}


void FractalCube::initGeometry(){

    const GLfloat triangleVertices[] = {
            // geometry XYZ - Tex UV

            //front face
            -1.f,  -1.f,  +1.f,   0.f, 0.f, //0
            +1.f,  -1.f,  +1.f,   1.f, 0.f,//1
            -1.f,  +1.f, +1.f,  0.f, 1.f,//2
            +1.f,  +1.f, +1.f,  1.f, 1.f,//3

            //back face
            +1.f,  -1.f,  -1.f,   1.f, 0.f, //4
            -1.f,  -1.f,  -1.f,   0.f, 0.f,//5
            +1.f,  +1.f, -1.f,  1.f, 1.f,//6
            -1.f, +1.f, -1.f,  0.f, 1.f,//7

            //right face
            +1.f,  -1.f,  +1.f,   0.f, 0.f,//1
            +1.f,  -1.f,  -1.f,   1.f, 0.f, //4
            +1.f,  +1.f, +1.f,  0.f, 1.f,//3
            +1.f,  +1.f, -1.f,  1.f, 1.f,//6

            //left face
            -1.f,  -1.f,  -1.f,   0.f, 0.f,//5
            -1.f,  -1.f,  +1.f,   1.f, 0.f, //0
            -1.f, +1.f, -1.f,  0.f, 1.f,//7
            -1.f,  +1.f, +1.f,  1.f, 1.f,//2

            //top face
            -1.f,  +1.f, +1.f,  0.f, 1.f,//2
            +1.f,  +1.f, +1.f,  1.f, 1.f,//3
            -1.f, +1.f, -1.f,  0.f, 0.f,//7
            +1.f,  +1.f, -1.f,  1.f, 0.f,//6

            //bottom face
            +1.f,  -1.f,  +1.f,   1.f, 1.f,//1
            -1.f,  -1.f,  +1.f,   0.f, 1.f, //0
            +1.f,  -1.f,  -1.f,   1.f, 0.f, //4
            -1.f,  -1.f,  -1.f,   0.f, 0.f,//5
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void FractalCube::render() const{

    p_material->enable();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    p_material->populateAttribBuffers();

    auto uMatMVPHandle = p_material->getUniformLocation("u_MVPMatrix");
    glm::mat4 mvp{m_transform()};
    p_material->setProperty("u_MVPMatrix", m_transform());
    //glUniformMatrix4fv(uMatMVPHandle, 1, GL_FALSE, glm::value_ptr(mvp));

    //auto uNormalsMatrixHandle = p_material->getUniformLocation("u_NormalsMatrix");
    glm::mat3 normalsMat{glm::inverse(glm::transpose(glm::mat3(m_transform())))};
    //glUniformMatrix3fv(uNormalsMatrixHandle, 1, GL_FALSE, glm::value_ptr( normalsMat));
    p_material->setProperty("u_NormalsMatrix", normalsMat);

    //face normals
    const glm::vec3 faceNormals[] = {
            glm::vec3{0,0,1},// front
            glm::vec3{0,0,-1}, // back
            glm::vec3{1,0,0}, // right
            glm::vec3{-1,0,0}, // left
            glm::vec3{0,1,0}, // top
            glm::vec3{0,-1,0} // bottom
    };


    p_material->setProperty("u_Spectrum", p_material->getTexture(0));
    glActiveTexture(GL_TEXTURE0); // Activate texture unit 0
    glBindTexture(GL_TEXTURE_2D, p_material->getTexture(0));

    for(auto k=0; k< 6; ++k) {
        p_material->setProperty("u_FaceNormal", faceNormals[k]);
        glDrawArrays(GL_TRIANGLE_STRIP, 4*k, 4);
        checkGlError("glDrawArrays", LOG_TAG);
    }
    p_material->disable();
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void FractalCube::updateState(){

    transform().multiply(perFrameTransform);
    p_material->setProperty("u_exponent", exponent);
    /*exponent+=0.01;
    if(exponent > 3.f)
        exponent = 1.0f;
        */
}