//
// Created by erez on 06/04/2025.
//

#pragma once

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <string>


class ShadersBuilder {
public:

    static GLuint buildGLProgram(const char*  pVertexSource, const char*  pFragmentSource);
    static GLuint createShader(GLenum shaderType, const char* sourceCode);

    static bool compileShader(GLuint shader, const std::string& shaderCode);
    static GLuint linkShaders(GLuint vertexShader, GLuint  fragmentShader);

    static void reportGlProgramLinkError(GLuint program);
    static void reportShaderCompilationError(GLuint shader, GLuint shaderType);


private:

};





