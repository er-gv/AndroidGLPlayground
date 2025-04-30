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

#define LOG_TAG "textureFactory"

GLuint loadTexture(const char *path) {
    GLuint textureId = 0;
    return textureId;
}


/**
 * Loads the given source code as a shader of the given type.
 */

/*
GLuint loadTexture(const char *path) {
    GLuint textureId = 0;
    jclass utilsClass = sEnv->FindClass("com/ergv/quantizedshapes/GL2JNILib");

    if (utilsClass == nullptr) {
        LOGE("Couldn't find utils class");
        return (GLuint) -1;
    }
    jmethodID loadTexture = sEnv->GetStaticMethodID(utilsClass, "loadTexture",
                                                    "(Landroid/content/res/AssetManager;Ljava/lang/String;)I");
    if (loadTexture == nullptr) {
        LOGE("Couldn't find loadTexture method");
        return (GLuint) -1;
    }
    jstring pathStr = sEnv->NewStringUTF(path);
    textureId = (GLuint) sEnv->CallStaticIntMethod(utilsClass, loadTexture, sAssetManager, pathStr);
    sEnv->DeleteLocalRef(pathStr);
    return textureId;
}



// Structure to hold texture data
struct TextureData{
    unsigned int width;
    unsigned int height;
    unsigned char* data;
};

// Function to read a PNG image from an AAsset
TextureData* loadPngFromAsset(AAsset* asset) {
    if (!asset) {
        LOGE("Invalid asset");
        return nullptr;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) {
        LOGE("png_create_read_struct failed");
        return nullptr;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        LOGE("png_create_info_struct failed");
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return nullptr;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        LOGE("Error during png read");
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return nullptr;
    }

    // Set up libpng to read from the asset
    png_set_read_fn(png_ptr, asset, [](png_structp png_ptr, png_bytep data, png_size_t length) {
        AAsset* asset = (AAsset*)png_get_io_ptr(png_ptr);
        AAsset_read(asset, data, length);
    });

    png_read_info(png_ptr, info_ptr);

    png_uint_32 width;
    png_uint_32 height;
    int bit_depth, color_type;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, nullptr, nullptr, nullptr);

    png_read_update_info(png_ptr, info_ptr);

    if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_ptr);
    if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png_ptr);
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png_ptr);
    if (bit_depth == 16)
        png_set_strip_16(png_ptr);
    if (bit_depth < 8)
        png_set_packing(png_ptr);
    if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png_ptr);
    if(png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB)
        png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);
    png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);

    // Allocate memory for image data
    png_size_t row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    png_size_t image_size = height * row_bytes;
    unsigned char* image_data = (unsigned char*) malloc(image_size);
    if (!image_data) {
        LOGE("Failed to allocate memory for image data");
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return nullptr;
    }

    // Read the image data
    png_bytep* row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for (int i = 0; i < height; i++) {
        row_pointers[i] = image_data + (i * row_bytes);
    }
    png_read_image(png_ptr, row_pointers);

    // Clean up libpng structures
    free(row_pointers);
    png_read_end(png_ptr, info_ptr);
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    TextureData* texture = new TextureData;
    texture->width = width;
    texture->height = height;
    texture->data = image_data;
    return texture;
}

GLuint loadTextureFromAsset(JNIEnv* env, jobject assetManager, const char* path) {
    GLuint textureId = 0;
    AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
    if (!mgr) {
        LOGE("Could not get AAssetManager");
        return 0;
    }

    AAsset* asset = AAssetManager_open(mgr, path, AASSET_MODE_STREAMING);
    if (!asset) {
        LOGE("Could not open asset: %s", path);
        return 0;
    }

    TextureData* texture = loadPngFromAsset(asset);
    AAsset_close(asset); // Close asset early

    if (!texture) {
        LOGE("Failed to load PNG from asset");
        return 0;
    }

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data);

    free(texture->data); // Free the image data
    delete texture; // Delete the texture data
    return textureId;
}

*/
