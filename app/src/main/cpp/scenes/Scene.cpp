//
// Created by erez on 22/04/2025.
//
// OpenGL ES 2.0 code



#include "Scene.h"
#include "../logger.h"
#include "../gl_logging.h"

#define LOG_TAG "SCENE"

void Scene::printGLStats(){
    printGLString("Version", GL_VERSION, LOG_TAG);
    printGLString("Vendor", GL_VENDOR, LOG_TAG);
    printGLString("Renderer", GL_RENDERER, LOG_TAG);
    printGLString("Extensions", GL_EXTENSIONS, LOG_TAG);
}

Scene::Scene(): Scene{Boundaries()}{};
Scene::Scene(const Boundaries& boundaries): boundaries{boundaries}{};
Scene::Scene(GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat near, GLfloat far):
    boundaries{left, right, top, bottom, near, far} {

    log_info(LOG_TAG, "Scene created");


};

void Scene::setViewPort(int w, int h){
    log_info(LOG_TAG, "@Scene::setViewPort(%d, %d)", w, h);
    //glViewport(activeCamera.0, 0, w, h);
    glViewport(0, 0, w, h);
    checkGlError("glViewport", LOG_TAG);
}


Scene::~Scene(){
    for(auto pModel : models){
        delete pModel;
    }
}

void Scene::addModel(Model* pModel){
    models.push_back(pModel);
}
void Scene::addCamera(const Camera& camera){
    activeCamera =camera;
}

void Scene::render(){

    for(auto pModel : models){
        pModel->updateState();
        pModel->render();
    }
}