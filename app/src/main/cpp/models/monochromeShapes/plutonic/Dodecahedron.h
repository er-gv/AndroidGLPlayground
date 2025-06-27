//
// Created by erez on 04/05/2025.
//


#pragma once

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <cmath>
#include "../../Model.h"
#include "../../../logger.h"
#include "../../../engine/shadersBuilder.h"

class Dodecahedron : public Model{
private:

    GLuint VBO{0};
    GLuint EBO{0};
    bool initVBO();


public:
    Dodecahedron(const Scene&, Material* material);
    ~Dodecahedron() override;
    bool init() override;
    void updateState() override;
    void render() const override;

};


