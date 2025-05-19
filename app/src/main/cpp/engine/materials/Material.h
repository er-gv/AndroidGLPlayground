//
// Created by erez on 15/05/2025.
//

#pragma once

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <map>

class Material {
    GLuint glProgram;
    Material()=default;

    std::map<std::string, GLuint> uniformLocations;
    std::map<std::string, GLuint> attribLocations;

public:
    ~Material();
    static Material materialBuilder(const char const* vertexShaderSrc, const char const* fragmentShaderSrc);
    void addUniform(const std::string& uniformName);
    void addAttribute(const std::string& attributeName);
    inline void useMaterial(){glUseProgram(this->glProgram);}
    inline void disableMaterial(){glUseProgram(0);}
};



