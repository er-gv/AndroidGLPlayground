//
// Created by erez on 24/04/2025.
//

#pragma once

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

void printGLString(const char* name, GLenum s, const std::string& tag) ;
void checkGlError(const char* op, const std::string& tag);

