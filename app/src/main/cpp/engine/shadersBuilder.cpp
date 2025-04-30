//
// Created by erez on 06/04/2025.
//
//#include <android/asset_manager.h> //For Native Activity Glue (if used)

#include "shadersBuilder.h"
#include "AssetsFactory.h"
#include "../logger.h"
#include "../gl_logging.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <cstdlib>
#include <string>


#define LOG_TAG "SHADER_BUILDER"


//*************************************************************************************
//            Fixed Code
//*************************************************************************************

GLuint ShadersBuilder::createShader(GLenum shaderType, const char* sourceCode) {
    GLuint shader = glCreateShader(shaderType);
    if (!shader) {
        log_error(LOG_TAG, "Failed to create a shader id for %s", sourceCode);
        return 0;
    }

    std::string shaderCode{readShaderAsset(sourceCode)};
    bool success = compileShader(shader, shaderCode);

    if(!success){
        reportShaderCompilationError(shader, shaderType);
        return 0; //throw(std::runtime_error(err_message));
    }

    return shader;
}


bool ShadersBuilder::compileShader(const GLuint shader, const std::string& shaderCode){
    const auto* shader_source = strdup(shaderCode.c_str());
    glShaderSource(shader, 1, (const GLchar**)&shader_source, nullptr);
    glCompileShader(shader);
    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    return compiled;
}


void ShadersBuilder::reportGlProgramLinkError(GLuint program){
    GLint bufLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
    if (bufLength) {
        char *buf = (char *) malloc(bufLength);
        if (buf) {
            glGetProgramInfoLog(program, bufLength, nullptr, buf);
            log_error(LOG_TAG, "Could not link program:\n%s\n", buf);
            free(buf);
        }
    }
}

void ShadersBuilder::reportShaderCompilationError(GLuint shader, GLuint shaderType){

    log_error(LOG_TAG, "Could not compile shader %d", shader);
    GLint infoLen = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
    if (infoLen) {
        char* buf = (char*)malloc(infoLen);
        if (buf) {
            glGetShaderInfoLog(shader, infoLen, nullptr, buf);
            log_error(LOG_TAG, "Could not compile shader %d:\n%s\n", shaderType, buf);
            free(buf);
        }
    }
}

GLuint ShadersBuilder::linkShaders(GLuint vertexShader, GLuint  fragmentShader){

    log_info(LOG_TAG, "@ShadersBuilder::buildGLProgram");

    GLuint glProgram{glCreateProgram()};
    glAttachShader(glProgram, vertexShader);
    checkGlError("glAttachShader", LOG_TAG);
    glAttachShader(glProgram, fragmentShader);
    checkGlError("glAttachShader", LOG_TAG);
    glLinkProgram(glProgram);
    GLint linkStatus = GL_FALSE;
    glGetProgramiv(glProgram, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {
        reportGlProgramLinkError(glProgram);
        glDeleteProgram(glProgram);
        glProgram = 0;
    }
    return glProgram;
}

GLuint ShadersBuilder::buildGLProgram(const char*  pVertexSource, const char*  pFragmentSource){

    log_info(LOG_TAG, "@ShadersBuilder::buildGLProgram");

    GLuint vertexShader{0};
    try{
        vertexShader = createShader(GL_VERTEX_SHADER, pVertexSource);
    }
    catch (std::runtime_error &rte) {
        log_error(LOG_TAG, "Could not create vertex shader object.\n%s\n", rte.what());
    }

    GLuint fragmentShader{0};
    try{
        fragmentShader = createShader(GL_FRAGMENT_SHADER, pFragmentSource);
    }
    catch (std::runtime_error &rte) {
        log_error(LOG_TAG, "Could not create fragment shader object.\n%s\n", rte.what());
    }

    return linkShaders(vertexShader, fragmentShader);
}


