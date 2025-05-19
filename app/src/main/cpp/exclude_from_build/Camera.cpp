#include "Camera.h"
#include "../logger.h"
#include "../engine/Boundaries.h"
#include <glm/gtc/type_ptr.hpp>

Camera::Camera():
    m_eye(glm::vec3(0,0,0)),
    m_bearing(glm::vec3(0,0, -1)),
    m_up(glm::vec3(0,1,0)){

}


Camera::Camera(glm::vec3 eye, glm::vec3 bearing, glm::vec3 up):
        m_eye(eye), m_bearing(bearing), m_up(up)
{

}

Camera::Camera(GLfloat eye[3], GLfloat bearing[3], GLfloat up[3]):
        m_eye(glm::make_vec3(eye)), m_bearing(glm::make_vec3(bearing)), m_up(glm::make_vec3(up))
{

}

Camera::Camera( GLfloat eye_x, GLfloat eye_y, GLfloat eye_z,
                GLfloat bearing_x, GLfloat bearing_y, GLfloat bearing_z,
                GLfloat up_x, GLfloat up_y,  GLfloat up_z):
        m_eye(glm::vec3(eye_x, eye_y, eye_z)),
        m_bearing(glm::vec3(bearing_x,bearing_y, bearing_z)),
        m_up(glm::vec3(up_x,up_y,up_z))
{

}

Camera::Camera(const Camera& c){
    m_eye=c.m_eye;
    m_bearing=c.m_bearing;
    m_up=c.m_up;
}


const glm::vec3& Camera::eye() const {
    return m_eye;
}

void Camera::eye(glm::vec3& e){
    m_eye = e;
}

const glm::vec3& Camera::bearing() const {
    return m_bearing;
}

void Camera::bearing(glm::vec3& b){
    m_bearing = b;
}

const glm::vec3& Camera::up() const {
    return m_up;
}
void Camera::up(glm::vec3& u){
    m_up = u;
}


glm::mat4 Camera::lookAt() const{
    return glm::lookAt(m_eye, m_bearing, m_up);
}
glm::mat4 Camera::lookAtLH() const{
    return glm::lookAtLH(m_eye, m_bearing, m_up);
}
glm::mat4 Camera::lookAtRH() const{
    return glm::lookAtRH(m_eye, m_bearing, m_up);
}


glm::mat4 Camera::projection(float fov, float ratio, float near, float far) const {
    return glm::perspective(fov, ratio, near, far);
}


glm::mat4 Camera::projection() const {
    return glm::perspective(45, 1, -1, -10);
}

glm::mat4 Camera::frustum(const Boundaries &b) const {
    return glm::frustum(b.left, b.right, b.bottom, b.top, b.front, b.back);
}