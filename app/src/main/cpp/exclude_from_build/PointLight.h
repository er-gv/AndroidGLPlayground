//
// Created by Erez on 15/05/20.
//

#pragma once


#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "../engine/libs/glm/glm.hpp"
#include "../engine/libs/glm/vec3.hpp"

class PointLight {


    glm::vec3 position;
    glm::vec3 mColor;
    float mSize;

public:
    PointLight();
    ~PointLight() = default;

    void render(const glm::mat4& view, const glm::mat4& projection);
    bool setup();

    void setColor(const glm::vec3&);

    void setPointSize(float s);
    void setPosition(const glm::vec3& other);
    //void updatePosition(long time);

};

