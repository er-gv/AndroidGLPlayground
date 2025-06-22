//
// Created by erez on 14/06/2025.
//

#include "TexturedCube.h"

#include "../../logger.h"
#include "../../engine/libs/glm/gtc/matrix_transform.hpp"
#include "../../engine/libs/glm/gtc/type_ptr.hpp"
#include "../../scenes/Scene.h"

#define LOG_TAG "FRACTAL_CUBE"

FractalCube::FractalCube(const Scene& scene, Material *material): Model{scene, material} {}
FractalCube::~FractalCube(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    delete p_material;
}

bool FractalCube::init(){

    initMaterial();
    initGeometry();

    return true;
}

bool FractalCube::initMaterial() {

    p_material->generateTextures({"texture/Companion_Cube.jpg",
                                "texture/trans_comanion_cube.jpg"});

    glActiveTexture(GL_TEXTURE0); // Activate texture unit 0
    glBindTexture(GL_TEXTURE_2D, p_material->getTexture(0));
    glActiveTexture(GL_TEXTURE1); // Activate texture unit 1
    glBindTexture(GL_TEXTURE_2D, p_material->getTexture(1));

    auto attributesInitialized = p_material->addAttributes(
            std::vector<std::tuple<const std::string&, GLsizei, GLsizei>>{
                    {std::string{"a_Position"},      3, 0},
                    {std::string{"a_TexCoordinate"}, 2, 3},
            });

    const char* uniforms[]{"u_Texture", "u_MVPMatrix", "u_NormalsMatrix", "u_FaceNormal", "u_LightPos"};
    bool uniformsInitialized{true};
    for (auto uni: uniforms) {
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

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    p_material->populateAttribBuffers();


    p_material->enable();

    auto uMatMVPHandle = p_material->getUniformLocation("u_MVPMatrix");
    glm::mat4 mvp{m_transform()};
    glUniformMatrix4fv(uMatMVPHandle, 1, GL_FALSE, glm::value_ptr(mvp));

    auto uNormalsMatrixHandle = p_material->getUniformLocation("u_NormalsMatrix");
    glm::mat3 normalsMat{glm::inverse(glm::transpose(glm::mat3(mvp)))};
    glUniformMatrix3fv(uNormalsMatrixHandle, 1, GL_FALSE, glm::value_ptr( normalsMat));

    auto uSampler2DHandle = p_material->getUniformLocation("u_Texture");


    //face normals
    const glm::vec3 faceNormals[] = {
            glm::vec3{0,0,1},// front
            glm::vec3{0,0,-1}, // back
            glm::vec3{1,0,0}, // right
            glm::vec3{-1,0,0}, // left
            glm::vec3{0,1,0}, // top
            glm::vec3{0,-1,0} // bottom
    };
    glUniform3f(p_material->getUniformLocation("u_LightPos"), 0.0f, 0.5f, 0.9f);

    for(auto k=0; k< 6; ++k) {
        glUniform1i(uSampler2DHandle, k%2);
        glUniform3fv(p_material->getUniformLocation("u_FaceNormal"), 1,
                     glm::value_ptr(faceNormals[k]));
        glDrawArrays(GL_TRIANGLE_STRIP, 4*k, 4);
        checkGlError("glDrawArrays", LOG_TAG);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    p_material->disable();

}

void FractalCube::updateState(){


    static const auto TWO_PI{glm::two_pi<float>()};

    m_rotationAngle += 0.4*m_delta_angle;
    if(m_rotationAngle > TWO_PI)
        m_rotationAngle -= TWO_PI;
    m_transform.reset();
    m_transform.scale(glm::vec3(0.45f));
    m_transform.translate(glm::vec3(0.0f, 0.0f, -.7f));
    m_transform.scale(glm::vec3(0.8f, 0.8f, 0.8f));
    m_transform.rotate(m_rotationAngle, glm::vec3(1.0f, 1.0f, 0.0f));
    //transform.rotate(glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
    std::this_thread::sleep_for(std::chrono::milliseconds(2));

}