//
// Created by erez on 28/04/2025.
//

#pragma once
#include <memory>
#include "AssetsFactory.h"

GLuint loadTextureFromAsset(const char* path="texture/stone_wall_public_domain.png");
TextureData generatePerlinNoise2D(int width, int height, float frequency, unsigned octavs, unsigned seed);
