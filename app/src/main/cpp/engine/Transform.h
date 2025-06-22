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

    inline Transform& operator=(const glm::mat4& m){
        mat = m;
        return *this;
    }

    inline explicit Transform(const glm::mat4& m): mat(m){}
    inline Transform(): mat(glm::mat4(1.0f)){}


    ~Transform()=default;


    // Returns true if the two matrices have the same values.
    inline bool operator==(const Transform &src){ return mat == src.mat; }

    // Loads this matrix with the identity matrix.
    inline Transform& reset(){
        mat = glm::mat4(1.0f);
        return *this;
    }

    // Translates this matrix by the given amounts.
    inline Transform& translate(float x, float y, float z){
        mat = glm::translate(mat, glm::vec3(x, y, z));
        return *this;

    }
    inline Transform& translate(const glm::vec3& t){
        mat = glm::translate(mat, t);
        return *this;
    }

    // Scales this matrix by the given amounts.
    inline Transform& scale(float sx, float sy, float sz) {
        mat = glm::scale(mat, glm::vec3(sx, sy, sz));
        return *this;
    }

    inline Transform& scale(float s){
        mat = glm::scale(mat, glm::vec3(s));
        return *this;
    }

    inline Transform& scale(const glm::vec3& t){
        mat = glm::scale(mat, t);
        return *this;
    }

    // Rotates this matrix the given angle.
    inline Transform& rotate(float radians, float x, float y, float z){
        mat = glm::rotate(mat, radians, glm::vec3(x, y, z));
        return *this;
    }

    inline Transform& rotate(float radians, const glm::vec3 axis){
        mat = glm::rotate(mat, radians, axis);
        return *this;
    }

    // Sets this matrix to be the result of multiplying the given matrices.
    inline Transform& multiply(const Transform &l, const Transform &r){
        mat = l.mat * r.mat;
        return *this;
    }

    inline static Transform multiply(const glm::mat4& l, const glm::mat4& r){
        return Transform(glm::mat4(l) * glm::mat4(r));
    }

    // Loads this matrix with the given data.
    inline void loadWith(const Transform &src){
        mat = src.mat;
    }

    inline const glm::mat4& operator() () const{
        return mat;
    }

};

