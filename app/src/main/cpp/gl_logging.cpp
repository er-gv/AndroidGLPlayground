//
// Created by erez on 24/04/2025.
//


#include "logger.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#define LOG_TAG "GL_LOGGING"
void printGLString(const char* name, GLenum s, const std::string& tag =LOG_TAG) {
    const char* v = (const char*)glGetString(s);
    log_info(LOG_TAG, "GL %s = %s\n", name, v);
}

void checkGlError(const char* op, const std::string& tag =LOG_TAG) {
    for (GLenum error = glGetError(); error; error = glGetError()) {
        log_info(LOG_TAG, "after %s() glError (0x%x)\n", op, error);
    }
}
