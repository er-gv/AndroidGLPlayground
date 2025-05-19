//
// Created by Erez on 05/04/20.
//

#pragma once



#include "../gl_includes.h"
#include "../engine/Boundaries.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

class Camera {
    glm::vec3 m_eye{};
    glm::vec3 m_bearing{};
    glm::vec3 m_up{};


public:
    Camera();
    Camera(glm::vec3 eye, glm::vec3 bearing, glm::vec3 up);
    Camera(GLfloat eye[3], GLfloat bearing[3], GLfloat up[3]);
    Camera(GLfloat eye_x, GLfloat eye_y, GLfloat eye_z,
           GLfloat bearing_x, GLfloat bearing_y, GLfloat bearing_z,
           GLfloat up_x, GLfloat up_y,  GLfloat up_z);
    Camera(const Camera& c);

    ~Camera() = default;

    const glm::vec3& eye() const;
    void eye(glm::vec3& e);
    const glm::vec3& bearing() const;
    void bearing(glm::vec3& b);
    const glm::vec3& up() const;
    void up(glm::vec3& u);

    inline glm::mat4 lookAt() const;
    inline glm::mat4 lookAtLH() const;
    inline glm::mat4 lookAtRH() const;

    inline glm::mat4 projection(float fov, float ratio, float near, float far) const;

    inline glm::mat4 projection() const;
    inline glm::mat4 frustum(const Boundaries &b) const ;

};



