//
// Created by erez on 06/04/2025.
//

#pragma once
#include <string>
#include <android/log.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

void log_info(const char* tag, const char* messageTemplate, ...);
void log_debug(const char* tag, const char* messageTemplate, ...);
void log_error(const char* tag, const char* messageTemplate, ...);
void log_warning(const char* tag, const char* messageTemplate, ...);
void log_fatal(const char* tag, const char* messageTemplate, ...);

void printGLString(const char* name, GLenum s, const std::string& tag) ;
bool checkGlError(const char* op, const std::string& tag);




