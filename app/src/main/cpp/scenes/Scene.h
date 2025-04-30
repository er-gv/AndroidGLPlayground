//
// Created by erez on 22/04/2025.
//

#pragma once

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <vector>

#include "../engine/Boundaries.h"
#include "../models/Model.h"
#include "../engine/Camera.h"

class Scene{
    std::vector<Model*> models;
    Camera activeCamera;
    //std::vector<Light> lights;
    Boundaries boundaries;


public:
    ~Scene();
    Scene();
    Scene(GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat near, GLfloat far);
    explicit Scene(const Boundaries& boundaries);
    void addModel(Model* pModel);
    void addCamera(const Camera& camera);

    static void printGLStats();
    void setViewPort(int w, int h);
    void render();


    //void addLight(const Light& light);
};

