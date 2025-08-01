//
// Created by erez on 10/04/2025.
//

#include "AssetsFactory.h"

#include <jni.h>
#include <GLES2/gl2.h>
#include <cstdlib>

#include <memory>
#include <stdexcept>
#include <string>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "../logger.h"
#define STB_IMAGE_IMPLEMENTATION
#include "libs/stb_image/stb_image.h"
#define LOG_TAG "ASSETS_FACTORY"

static AAssetManager* assetsManager = nullptr;


std::string readGeometryAsset(const std::string& geometry_path){
    auto* asset = AAssetManager_open(assetsManager, geometry_path.c_str(), AASSET_MODE_STREAMING);
    if (!asset) {
        log_error(LOG_TAG, "Could not open asset: %s", geometry_path.c_str());
        throw (std::runtime_error("Could not open asset."));
    }

    auto len = AAsset_getLength(asset);
    auto* buffer = new char[len+1];
    AAsset_read(asset, buffer, len);
    buffer[len]= '\0';
    AAsset_close(asset);
    log_debug(LOG_TAG, "read shader code: %s", buffer);
    std::string geometryJSON{buffer};
    delete[] buffer;
    return geometryJSON;
}



void readTextureAsset(const std::string& texture_path, TextureData &td){
    auto* asset = AAssetManager_open(assetsManager, texture_path.c_str(), AASSET_MODE_STREAMING);
    if (!asset) {
        char const* f{strdup(texture_path.c_str())};
        log_error(LOG_TAG, "Could not open asset: %s", f);
        delete[] f;
        throw (std::runtime_error("Could not open asset."));
    }

    auto len = AAsset_getLength(asset);
    auto* buffer = new unsigned char[len+1];
    AAsset_read(asset, buffer, len);
    buffer[len]= '\0';
    AAsset_close(asset);
    td.data = stbi_load_from_memory(buffer, len, &td.width, &td.height, &td.channels_in_file, td.channels_in_texture);
    delete[] buffer;
}

std::string readShaderAsset(const std::string& shader_path){
    auto asset = AAssetManager_open(assetsManager, shader_path.c_str(), AASSET_MODE_BUFFER);
    if (!asset) {
        const char* msg = strdup(shader_path.c_str());
        log_fatal(LOG_TAG, "Could not open asset: %s", msg);
        delete[] msg;
        throw (std::runtime_error("Could not open asset."));
    }
    auto len = AAsset_getLength(asset);
    auto* buffer = new char[len+1];
    AAsset_read(asset, buffer, len);
    buffer[len]= '\0';
    AAsset_close(asset);
    log_debug(LOG_TAG, "read shader code: %s", buffer);
    std::string shaderCode{buffer};
    delete[] buffer;
    return shaderCode;
}


extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_AssetsFactory_init(JNIEnv* env,  jobject obj,  jobject manager) {
    log_debug(LOG_TAG, "@AssetsFactory_init(%p, %p)", obj, manager);
    assetsManager = AAssetManager_fromJava(env, manager);
}
