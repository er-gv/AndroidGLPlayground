//
// Created by erez on 22/04/2025.
//
// OpenGL ES 2.0 code



#include "Scene.h"
#include "../logger.h"

#define LOG_TAG "SCENE"

void Scene::printGLStats(){
    printGLString("Version", GL_VERSION, LOG_TAG);
    printGLString("Vendor", GL_VENDOR, LOG_TAG);
    printGLString("Renderer", GL_RENDERER, LOG_TAG);
    printGLString("Extensions", GL_EXTENSIONS, LOG_TAG);
}



Scene::Scene(const Boundaries& boundaries, glm::vec3 clearColor):
        boundaries{boundaries}, clearColor{clearColor}{
    log_info(LOG_TAG, "Scene created");
};

Scene::Scene(GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat near, GLfloat far):
        Scene(Boundaries{left, right, top, bottom, near, far}) {

    log_info(LOG_TAG, "Scene created");
};

void Scene::setClearColor(const glm::vec3 &color){
    clearColor = color;
}

void Scene::setBoundaries(const Boundaries &new_boundaries){
    this->boundaries = new_boundaries;
}

void Scene::setViewPort(int w, int h){
    log_info(LOG_TAG, "@Scene::setViewPort(%d, %d)", w, h);

    glViewport(0, 0, 1080, 2400);
    checkGlError("glViewport", LOG_TAG);
}


Scene::~Scene(){

    for(auto pModel : models){
        delete pModel;
    }
}

void Scene::addDirectionalLight(const DirectionalLight& light){
    directionalLight = light;
}

//void Scene::addPointLight(const PointLight& light){
//    pointLight = light;
//}
void Scene::setWaitBetweenFramesMillis(unsigned millis){
    waitBetweenFramesMillis=millis;
}

void Scene::addModel(Model* pModel){
    models.push_back(pModel);
}

void Scene::reset(){
    for(auto model : models){
        delete model;
    }
    models.clear();
}

void Scene::render(){
    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
    checkGlError("glClearColor", LOG_TAG);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear", LOG_TAG);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    for(auto pModel : models){
        pModel->updateState();
        pModel->render();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(waitBetweenFramesMillis));

}
