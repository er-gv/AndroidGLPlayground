//
// Created by erez on 22/04/2025.
//

#pragma once

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <vector>
#include "../engine/libs/glm/glm.hpp"
#include "../engine/libs/glm/vec3.hpp"

#include "../engine/Boundaries.h"
#include "../engine/lights/DirectionalLight.h"
#include "../exclude_from_build/PointLight.h"
#include "../models/Model.h"
#include "../engine/lights/environmentLight.h"
//#include "../exclude_from_build/Camera.h"

class Scene{
    std::vector<Model*> models;
    //Camera activeCamera;
    //std::vector<Light> lights;
    //std::map<unsigned , light&> lights;
    //PointLight pointLight;
    DirectionalLight directionalLight;
    EnvironmentLight enviromentLight;
    Boundaries boundaries;
    glm::vec3 clearColor;
    unsigned waitBetweenFramesMillis{100};


public:
    ~Scene();
    explicit Scene(
            const Boundaries& boundaries= Boundaries{-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f},
            glm::vec3 clearColor= glm::vec3{0.0f, 0.0f, 0.0f}
            );

    Scene(GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat near, GLfloat far);

    void addModel(Model* pModel);
    //void addCamera(const Camera& camera);

    static void printGLStats();
    void setViewPort(int w, int h);
    void setClearColor(const glm::vec3 &color);
    void setWaitBetweenFramesMillis(unsigned millis);
    void setBoundaries(const Boundaries &new_boundaries);
    void render();
    void reset();

    void addDirectionalLight(const DirectionalLight& light);
    void setEnvironmentLight(const EnvironmentLight &light){ enviromentLight=light;}
    //void addPointLight(const PointLight& light);
};

