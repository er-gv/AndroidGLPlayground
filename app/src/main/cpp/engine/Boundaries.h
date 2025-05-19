//
// Created by erez on 23/04/2025.
//

#pragma once

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
struct Boundaries{

    GLfloat left, right, top, bottom, front, back;
    inline Boundaries(GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat front, GLfloat back):
    left{left}, right{right}, top{top}, bottom{bottom}, front{front}, back{back}{};
    inline Boundaries(): left(1), right(-1), top(1), bottom(-1), front(1), back(-1){};
};




