//
// Created by erez on 22/04/2025.
//

#include "TexturedPyramid.h"
#include "../../engine/texturesFactory.h"
#include "../../logger.h"
#include "../../engine/libs/glm/gtc/matrix_transform.hpp"
#include "../../engine/libs/glm/gtc/type_ptr.hpp"

#define LOG_TAG "FRACTAL_CUBE"

TexturedPyramid::TexturedPyramid(const Scene& sene, Material* material): Model{sene, material}{}

TexturedPyramid::~TexturedPyramid(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    delete p_material;
}

bool TexturedPyramid::init(){

    initMaterial();
    initGeometry();

    return true;
}

bool TexturedPyramid::initMaterial(){


    p_material->generateTextures({"texture/bumpy_bricks_public_domain.jpg","texture/stone_wall_public_domain.png"});

        auto attributesInitialized = p_material->addAttributes(std::vector<std::tuple< const std::string&, GLsizei, GLsizei>> {
                {std::string{"a_Position"}, 3, 0}, {std::string{"a_TexCoordinate"}, 2, 3},
        });

        auto uniformsInitialized = p_material->addUniforms(std::vector<const std::string>{
                "u_Texture", "u_MVPMatrix", "u_NormalsMatrix", "u_FaceNormal", "u_LightPos"
        });
        //p_material->logUniforms();

        return  attributesInitialized && uniformsInitialized;

}


void TexturedPyramid::initGeometry(){

    const GLfloat triangleVertices[] = {
            // geometry XYZ - Tex UV
            +0.0f, +0.4f, +0.0f, +0.5f, +1.0f,     //0
            -0.5f, -0.6f, +0.5f, +0.0f, +0.0f,     //1
            +0.5f, -0.6f, +0.5f, +1.0f, +0.0f,  //2
            +0.5f, -0.6f, -0.5f, +0.0f, +0.0f,  //3
            -0.5f, -0.6f, -0.5f, +1.5f, +0.0f, //4
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

void TexturedPyramid::render() const{

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    p_material->populateAttribBuffers();

    p_material->enable();

    auto mvp{m_transform()};
    p_material->setProperty("u_MVPMatrix",glm::mat3(mvp));

    glm::mat3 normalsMat{glm::mat3{glm::inverse(glm::transpose(mvp))}};
    p_material->setProperty("u_NormalsMatrix",normalsMat);

    glActiveTexture(GL_TEXTURE0); // Activate texture unit 0
    glBindTexture(GL_TEXTURE_2D, p_material->getTexture(0));
    glActiveTexture(GL_TEXTURE1); // Activate texture unit 1
    glBindTexture(GL_TEXTURE_2D, p_material->getTexture(1));
    auto uSampler2DHandle = p_material->getUniformLocation("u_Texture");


    auto rotate45Deg = glm::rotate(glm::mat4{1.0}, 0.25f*glm::pi<float>(), glm::vec3{1.0,0.0,0.0});

    for(auto k=0, offset=0; k< 4; ++k, offset+=3 ) {
        glUniform1i(uSampler2DHandle, k%2);
        auto rotate90DegY = glm::rotate(glm::mat4{1.0}, k*glm::half_pi<float>(), glm::vec3{0.0,1.0,0.0});
        p_material->setProperty("u_FaceNormal", rotate45Deg*rotate90DegY);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, reinterpret_cast<const void *>(offset*sizeof(GLuint)));
        checkGlError("glDrawElements", LOG_TAG);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    p_material->disable();

}

void TexturedPyramid::updateState(){
    m_transform.multiply(perFrameTransform);
}