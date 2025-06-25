//
// Created by erez on 23/04/2025.
//

#include "logger.h"

#include <android/log.h>




void log_entry(const int priority, const char* tag, const char* messageTemplate, ...) {
    va_list args;
    va_start(args, messageTemplate);

    // Determine the size needed for the formatted string.
    va_list argsCopy;
    va_copy(argsCopy, args);
    int size = vsnprintf(nullptr, 0, messageTemplate, argsCopy);
    va_end(argsCopy);

    if (size < 0) {
        __android_log_print(ANDROID_LOG_ERROR, tag, "Error in formatting log message.");
        va_end(args);
        return;
    }

    // Allocate a buffer to hold the formatted string.
    std::string formattedMessage(size + 1, '\0'); // +1 for null terminator

    // Format the message into the buffer.
    vsnprintf(&formattedMessage[0], size + 1, messageTemplate, args);



    // Log the formatted message.
    __android_log_print(priority, tag, "%s", formattedMessage.c_str());
}


void log_info(const char* tag, const char* messageTemplate, ...) {
    va_list args;
    va_start(args, messageTemplate);
    log_entry(ANDROID_LOG_INFO, tag, messageTemplate, args);
    va_end(args);
}

void log_debug(const char* tag, const char* messageTemplate, ...){
    va_list args;
    va_start(args, messageTemplate);
    log_entry(ANDROID_LOG_DEBUG, tag, messageTemplate, args);
    va_end(args);
}

void log_error(const char* tag, const char* messageTemplate, ...) {
    va_list args;
    va_start(args, messageTemplate);
    log_entry(ANDROID_LOG_ERROR, tag, messageTemplate, args);
    va_end(args);
}

void log_warning(const char* tag, const char* messageTemplate, ...) {
    va_list args;
    va_start(args, messageTemplate);
    log_entry(ANDROID_LOG_WARN, tag, messageTemplate, args);
    va_end(args);
}


void log_fatal(const char* tag, const char* messageTemplate, ...) {
    va_list args;
    va_start(args, messageTemplate);
    log_entry(ANDROID_LOG_FATAL, tag, messageTemplate, args);
    va_end(args);
}

void printGLString(const char* name, GLenum s, const std::string& tag) {
    const char* v = (const char*)glGetString(s);
    log_info(tag.c_str(), "GL %s = %s\n", name, v);
}

bool checkGlError(const char* op, const std::string& tag) {
    bool hasError = false;
    for (GLenum error = glGetError(); error; error = glGetError()) {
        log_info(tag.c_str(), "after %s() glError (0x%x)\n", op, error);
        hasError = true;
    }
    return hasError;
}


