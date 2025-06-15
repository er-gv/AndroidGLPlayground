//
// Created by erez on 04/05/2025.
//


#pragma once

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <cmath>
#include "../Model.h"
#include "../../logger.h"
#include "../../engine/shadersBuilder.h"
#include "../../engine/materials/Material.h"

class ChessCube : public Model{
private:

    Material* material;

    GLuint VBO{0};
    GLuint EBO{0};

    bool initVBO();


public:
    explicit ChessCube(Material* material);
    ~ChessCube() override;
    bool init() override;
    void updateState() override;
    void render() const override;



};


