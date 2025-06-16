//
// Created by erez on 10/04/2025.
//



#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <linux/time.h>
#include "../logger.h"
#include "AssetsFactory.h"
#include <unistd.h>
#include "libs/PerlinNoise/PerlinNoise.hpp"

#define LOG_TAG "textureFactory"

TextureData generatePerlinNoise2D(int width, int height, float frequency, unsigned octavs, unsigned seed){
    auto perlin = TextureData(width, height, 3);
    return perlin;
}

//GLuint build2DTexture(path, colorFormat, textureFormat);
GLuint loadTextureFromAsset(const char* path) {
    GLuint textureId = 0;
    TextureData td;
    char buffer[2000];
    buffer[2000-1] = '\0';
    getcwd(buffer, 2000);

    readTextureAsset(std::string(path), td);
    if (!td.data) {
        log_error(LOG_TAG, "Failed to load PNG from asset");
        log_debug(LOG_TAG, "Loading texture from asset: %s", path);
        log_debug(LOG_TAG, "Current pwd is %s.", (char* const)buffer);
        return 0;
    }

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Set texture parameters (filtering, wrapping)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Or GL_CLAMP_TO_EDGE, etc.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Assuming you have image_data, width, height, format (e.g., GL_RGBA)
    // int width, height;
    // unsigned char* image_data = /* loaded from file or memory */;
    // GLenum format = GL_RGBA; // Based on your image data

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, td.width, td.height, 0, GL_RGB, GL_UNSIGNED_BYTE, td.data);
    glGenerateMipmap(GL_TEXTURE_2D); // Important for good quality with MIN_FILTER needing mipmaps

    // Free image_data if it's no longer needed on the CPU
    // stbi_image_free(image_data); (if using stb_image)

    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture

    free(td.data); // Free the image data
    return textureId;
}


