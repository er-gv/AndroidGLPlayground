//
// Created by erez on 15/05/2025.
//

#pragma once

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <map>
#include <tuple>
#include <cstring>
#include "../texturesFactory.h"

struct VertexAttribute {
    GLuint position;
    GLint size;
    GLsizei offset;
};

typedef std::tuple<const std::string&, GLsizei, GLsizei> Attrib;


class Material {

    GLuint glProgram;

    explicit Material(GLuint glProgram) : glProgram(glProgram){};

    std::map<const std::string,  VertexAttribute> attribLocations;
    std::map<const std::string, GLint> uniformLocations;
    std::vector<GLuint> textures;

    //glm::vec3 baseColor;
    //glm::vec3 specularColor;
    //float specularPercent;
    //float roughnessPercent;
    //float metallicPercent;
    //float transparencyPercent;


public:

    ~Material();
    static Material* materialBuilder(const char* vertexShaderSrc, const char* fragmentShaderSrc);


    bool addAttributes(const std::vector<std::tuple<const std::string&, GLsizei, GLsizei>>& atribs);
    bool addAttribute(const std::tuple<const std::string&, GLsizei, GLsizei>& attrib);

    bool addUniforms(const std::vector<const std::string>& uniforms);
    bool addUniform(const std::string&);

    void generateTextures(const std::vector<const char*>& textures);
    void addTexture(GLuint textureUnit);
    GLuint getTexture(GLuint idx) const;


    GLint getUniformLocation(const std::string& uniformName) const;
    GLuint getAttribLocation(const std::string& attribName) const;
    GLint getAttribSize(const std::string& attribName) const;

    bool setProperty(const std::string& property, float value) const;
    bool setProperty(const std::string& property, const glm::vec2& value) const;
    bool setProperty(const std::string& property, const glm::vec3& value) const;


    GLsizei getVertexStride() const;

    void logUniforms() const;
    void populateAttribBuffers() const;

    void enable() const;
    void disable() const;
};



