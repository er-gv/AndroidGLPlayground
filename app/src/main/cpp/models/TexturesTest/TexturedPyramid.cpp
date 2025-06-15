//
// Created by erez on 22/04/2025.
//

#include "TexturedPyramid.h"
#include "../../engine/texturesFactory.h"
#include "../../logger.h"
#include "../../engine/libs/glm/gtc/matrix_transform.hpp"
#include "../../engine/libs/glm/gtc/type_ptr.hpp"

#define LOG_TAG "FRACTAL_CUBE"

TexturedPyramid::~TexturedPyramid(){
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    delete material;
}

bool TexturedPyramid::init(){

    initMaterial();
    initGeometry();

    return true;
}

bool TexturedPyramid::initMaterial(){


    material->generateTextures({"texture/bumpy_bricks_public_domain.jpg","texture/stone_wall_public_domain.png"});

        auto attributesInitialized = material->addAttributes(std::vector<std::tuple< const char*, GLsizei, GLsizei>> {
                {"a_Position", 3, 0}, {"a_TexCoordinate", 2, 3},
        });

        auto uniformsInitialized = material->addUniforms(std::vector<const char*>{
                "u_Texture", "u_MVPMatrix"
        });
        //material->logUniforms();

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
    material->populateAttribBuffers();


    material->enable();

    auto uMatMVPHandle = material->getUniformLocation("u_MVPMatrix");
    glUniformMatrix4fv(uMatMVPHandle, 1, GL_FALSE, glm::value_ptr(transform()));

    glActiveTexture(GL_TEXTURE0); // Activate texture unit 0
    glBindTexture(GL_TEXTURE_2D, material->getTexture(0));
    glActiveTexture(GL_TEXTURE1); // Activate texture unit 1
    glBindTexture(GL_TEXTURE_2D, material->getTexture(1));

    for(auto k=0, offset=0; k< 4; ++k, offset+=3 ) {
        auto uSampler2DHandle = material->getUniformLocation("u_Texture");
        glUniform1i(uSampler2DHandle, k%2);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, reinterpret_cast<const void *>(offset*sizeof(GLuint)));
        checkGlError("glDrawElements", LOG_TAG);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    material->disable();

}

void TexturedPyramid::updateState(){


    static const auto TWO_PI{glm::two_pi<float>()};

    m_rotationAngle += m_delta_angle;
    if(m_rotationAngle > TWO_PI)
        m_rotationAngle -= TWO_PI;
    transform.reset();
    transform.translate(glm::vec3(0.0f, 0.3f, -.3f));
    transform.scale(glm::vec3(0.6f, 1.0f, 0.6f));
    transform.rotate(m_rotationAngle, glm::vec3(0.0f, 1.0f, 1.0f));
    std::this_thread::sleep_for(std::chrono::milliseconds(2));

}

TexturedPyramid::TexturedPyramid(Material *tex) : Model(tex) {

}
