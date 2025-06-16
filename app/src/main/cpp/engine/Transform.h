/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the License for the specific language governing permissions and limitations under
 * the License.
 */
#pragma once
#include "libs/glm/glm.hpp"
#include "libs/glm/vec3.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"
class Transform {

    glm::mat4 mat;

public:

    inline explicit Transform(){
        mat = glm::mat4(1.0f);
    }

    // Returns true if the two matrices have the same values.
    inline bool equals(const Transform &src){ return mat == src.mat; }

    // Loads this matrix with the identity matrix.
    inline void reset(){
        mat = glm::mat4(1.0f);
    }

    // Translates this matrix by the given amounts.
    inline void translate(float x, float y, float z){
        glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
        mat = trans * mat;
    }
    inline void translate(const glm::vec3& t){
        glm::mat4 trans = glm::translate(glm::mat4(1.0f), t);
        mat = trans * mat;
    }

    // Scales this matrix by the given amounts.
    inline void scale(float sx, float sy, float sz) {
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(sx, sy, sz));
        mat = scale * mat;
    }

    inline void scale(float s){
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(s));
        mat = scale * mat;
    }

    inline void scale(const glm::vec3& t){
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), t);
        mat = scale * mat;
    }

    // Rotates this matrix the given angle.
    inline void rotate(float radians, float x, float y, float z){
        glm::mat4 rot = glm::rotate(glm::mat4(1.0f), radians, glm::vec3(x, y, z));
        mat = rot * mat;
    }

    inline void rotate(float radians, const glm::vec3 axis){
        glm::mat4 rot = glm::rotate(glm::mat4(1.0f), radians, axis);
        mat = rot * mat;
    }

    // Sets this matrix to be the result of multiplying the given matrices.
    inline void multiply(const Transform &l, const Transform &r){
        mat = l.mat * r.mat;
    }

    inline void multiply(const glm::mat4& l, const glm::mat4& r){
        mat = l * r;
    }

    // Loads this matrix with the given data.
    inline void loadWith(const Transform &src){
        mat = src.mat;
    }

    inline const glm::mat4& read() const{
        return mat;
    }

    inline const glm::mat4& operator() () const{
        return mat;
    }

};

