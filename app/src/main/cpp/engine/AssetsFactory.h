//
// Created by erez on 10/04/2025.
//

#pragma once
#include <string>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "libs/glm/glm.hpp"
#include "libs/stb_image/stb_image.h"


struct TextureData{
    int width;
    int height;
    int channels_in_texture;
    int channels_in_file;
    unsigned char* data;
    TextureData(int width, int height, int channels_in_texture) : width{width}, height{height},
    channels_in_texture{channels_in_texture}, data{nullptr}{
        channels_in_file = 0;
    }

    explicit constexpr TextureData(bool isTransparent=false) : width(0), height(0),
                                            channels_in_texture(isTransparent?4:3),
                                            channels_in_file(0), data(nullptr){}
};
std::string readShaderAsset(const std::string& shader_path);
void readTextureAsset(const std::string& texture_path, TextureData &td);
std::string readGeometryAsset(const std::string& geometry_path);





