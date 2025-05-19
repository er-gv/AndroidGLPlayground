//
// Created by erez on 06/04/2025.
//

#pragma once
#include <string>
#include <android/log.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
//
//#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
//#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
//#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
//#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

void log_info(const char* tag, const char* messageTemplate, ...);
void log_debug(const char* tag, const char* messageTemplate, ...);
void log_error(const char* tag, const char* messageTemplate, ...);
void log_warning(const char* tag, const char* messageTemplate, ...);
void log_fatal(const char* tag, const char* messageTemplate, ...);

void printGLString(const char* name, GLenum s, const std::string& tag) ;
bool checkGlError(const char* op, const std::string& tag);




