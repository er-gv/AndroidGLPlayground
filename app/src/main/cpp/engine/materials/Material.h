//
// Created by erez on 15/05/2025.
//

#pragma once

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <map>
#include <tuple>
#include "../texturesFactory.h"

struct VertexAttribute {
    GLuint position;
    GLint size;
    GLsizei offset;
};

typedef std::tuple<const char*, GLsizei, GLsizei> Attrib;

class Material {

    GLuint glProgram;

    explicit Material(GLuint glProgram) : glProgram(glProgram){};
    std::map<const char*,  VertexAttribute> attribLocations;
    std::map<const char*, GLint> uniformLocations;
    std::vector<GLuint> textures;

    //glm::vec3 baseColor;
    //glm::vec3 specularColor;
    //float specularPercent;
    //float roughnessPercent;
    //float metallicPercent;
    //float transparencyPercent;


public:

    ~Material();
    static Material* materialBuilder(const char*  vertexShaderSrc, const char* fragmentShaderSrc);


    bool addAttributes(const std::vector<std::tuple<const char*, GLsizei, GLsizei>>& atribs);
    bool addAttribute(const std::tuple<const char*, GLsizei, GLsizei>& attrib);

    bool addUniforms(const std::vector<const char*>& uniforms);
    bool addUniform(const char* uniformName);

    bool generateTextures(const std::vector<const char*>& textures);
    bool addTexture(GLuint textureUnit);
    GLuint getTexture(const GLuint idx) const;


    GLint getUniformLocation(const char* uniformName) const;
    GLuint getAttribLocation(const char* attribName) const;
    GLint getAttribSize(const char* attribName) const;
    GLint getAttribOffset(const char* attribName) const;


    GLsizei getVertexStride() const;

    void logUniforms() const;
    void populateAttribBuffers() const;

    void enable() const;
    void disable() const;
};



