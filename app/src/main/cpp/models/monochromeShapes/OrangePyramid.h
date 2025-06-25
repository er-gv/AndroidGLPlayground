//
// Created by erez on 22/05/2025.
//

#pragma once
#include "../Model.h"
#include <GLES2/gl2.h>

class OrangePyramid : public Model {

    GLuint VBO{0};
    GLuint EBO{0};

    const glm::vec3 normals[4]{
            glm::normalize(glm::cross(glm::vec3{0.75f,-0.8f, +0.75f}, glm::vec3{+0.75f,-0.8f, -0.75f})),
            glm::normalize(glm::cross(glm::vec3{+0.75f,-0.8f, -0.75f}, glm::vec3{-0.75f,-0.8f, -0.75f})),
            glm::normalize(glm::cross(glm::vec3{-0.75f,-0.8f, -0.75f}, glm::vec3{-0.75f,-0.8f, +0.75f})),
            glm::normalize(glm::cross(glm::vec3{-0.75f,-0.8f, +0.75f}, glm::vec3{+0.75f,-0.8f, +0.75f}))
    };

    void initGeometry();
    bool initMaterial();

public:
    ~OrangePyramid() override;
    OrangePyramid(const Scene&, Material* material);
    virtual bool init() override;
    virtual void render() const override;
    virtual void updateState() override;
};
