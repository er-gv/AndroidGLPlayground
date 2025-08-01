//
// Created by Erez on 15/05/20.
//

#include "PointLight.h"
#include "../libs/glm/glm.hpp"
#include "../libs/glm/vec3.hpp"
#include "../libs/glm/mat4x4.hpp"
#include "../libs/glm/gtc/type_ptr.hpp"
#include "../libs/glm/gtc/matrix_transform.hpp"
#include <android/log.h>
PointLight::PointLight() {
    mSize = 5.0f;
}


bool PointLight::setup(){
    const char vertex_shader[] = "shaders/vertex/point_vertex_shader.glsl";
    const char fragment_shader[] = "shaders/fragment/point_fragment_shader.glsl";

    return true;
}

void PointLight::setColor(const glm::vec3& color){
    mColor = glm::vec3(color);
}

void PointLight::setPointSize(float s){
    mSize = s;
}

/*void PointLight::preRenderUpdate(long time){
    float angleInDegrees = (360.0f / 10000.0f) * ((int) time);
    float radians = glm::radians(angleInDegrees);
    t.identity();
    t.translate(glm::vec3(0, 0, -5));
    t.rotate(radians, glm::vec3(1.0f, 1.0f, 0.0f));
    t.translate(glm::vec3(0, 0, 2));

}*/
/*
void PointLight::render(const glm::mat4& view, const glm::mat4& projection) {

    __android_log_print(ANDROID_LOG_INFO, "POINTLIGHT", "entering render");
    mat->activate();//glUseProgram(mPointProgramHandle);
    // Pass in the mPosition
    glVertexAttrib3f(mat->getAttrib("a_Position"),  .0f, .0f, .0f);


    // Pass in the model*view*projection matrix.
    glUniformMatrix4fv(
            mat->getUniform("u_MVPMatrix"),
            1, GL_FALSE,
            glm::value_ptr(projection*view*t.get())
    );
    //Pass in light color
    glUniform3fv(mat->getUniform("u_Color"), 1, glm::value_ptr(mColor));

    //Pass light size
    glUniform1f( mat->getUniform("u_pointSize"), mSize);

    glDrawArrays(GL_POINTS, 0, 1);
    mat->deactivate();
    __android_log_print(ANDROID_LOG_INFO, "POINTLIGHT", "leaving render");
}*/
//glm::vec4 PointLight::position(){
//    return (t.get()*glm::vec4(.0f, .0f, .0f, 1.0));
//};

void PointLight::setPosition(const glm::vec3& other){
        position = other;

}
