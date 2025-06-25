//
// Created by erez on 14/06/2025.
//

#include "TexturedCube.h"

#include "../../logger.h"
#include "../../engine/libs/glm/gtc/matrix_transform.hpp"
#include "../../engine/libs/glm/gtc/type_ptr.hpp"
#include "../../scenes/Scene.h"

#define LOG_TAG "FRACTAL_CUBE"

TexturedCube::TexturedCube(const Scene& scene, Material *material): Model{scene, material} {}
TexturedCube::~TexturedCube(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    delete p_material;
}

bool TexturedCube::init(){

    initMaterial();
    initGeometry();

    return true;
}

bool TexturedCube::initMaterial() {

    p_material->generateTextures({"texture/stone_wall_public_domain.png",
                                "texture/stone_wall_public_domain.png"});

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


void TexturedCube::initGeometry(){

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

void TexturedCube::render() const{

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    p_material->populateAttribBuffers();

    p_material->enable();

    auto mvp{m_transform()};
    p_material->setProperty("u_MVPMatrix",glm::mat3(mvp));

    auto mv{glm::inverse(glm::transpose(glm::mat3(mvp)))};
    p_material->setProperty("u_NormalsMatrix",glm::mat3(mv));


    //face normals
    const glm::vec3 faceNormals[] = {
            glm::vec3{0,0,1},// front
            glm::vec3{0,0,-1}, // back
            glm::vec3{1,0,0}, // right
            glm::vec3{-1,0,0}, // left
            glm::vec3{0,1,0}, // top
            glm::vec3{0,-1,0} // bottom
    };

    auto uSampler2DHandle = p_material->getUniformLocation("u_Texture");
    glActiveTexture(GL_TEXTURE0); // Activate texture unit 0
    glBindTexture(GL_TEXTURE_2D, p_material->getTexture(0));
    glActiveTexture(GL_TEXTURE1); // Activate texture unit 1
    glBindTexture(GL_TEXTURE_2D, p_material->getTexture(1));

    for(auto k=0; k< 6; ++k) {
        glUniform1i(uSampler2DHandle, k%2);
        p_material->setProperty("u_FaceNormal", faceNormals[k]);
        glDrawArrays(GL_TRIANGLE_STRIP, 4*k, 4);
        checkGlError("glDrawArrays", LOG_TAG);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    p_material->disable();

}

void TexturedCube::updateState(){
    m_transform.multiply(perFrameTransform);
}