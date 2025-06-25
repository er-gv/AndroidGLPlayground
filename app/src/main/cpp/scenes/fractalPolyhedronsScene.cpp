
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <jni.h>
#include "../logger.h"

#include "../engine/libs/glm/glm.hpp"
#include "../models/FractaledPolyhedrons/FractalCube.h"
#include "Scene.h"

#define LOG_TAG "FRACTAL_COATED_MODELS"

static Scene scene;

void addTopCube();
void addBottomCube();
void addSideCube();
void addCentralCube();

bool setupGraphics(int w, int h) {
    log_info(LOG_TAG,"@FractalPolyhedronsScene::setupGraphics(%d, %d)", w, h);
    scene.reset();
    scene.setClearColor(glm::vec3{0.125f});
    scene.addDirectionalLight(DirectionalLight{glm::vec3{0.f, -1.f, -1.f}, glm::vec3{0.f, 0.8f, 0.2f}});
    scene.setWaitBetweenFramesMillis(30u);
    scene.setViewPort(h, h);

    addTopCube();
    addSideCube();
    addCentralCube();
    addBottomCube();

    return true;
}


void addSideCube(){
    Material *m = Material::materialBuilder("shaders/mandelbrot/vertex.glsl", "shaders/mandelbrot/fragment.glsl");
    auto cube {new FractalCube(scene,m)};

    cube->init();
    cube->material()->enable();
    m->setProperty("u_exponent", 0.3);
    m->setProperty("u_juliaSeedPoint",   glm::vec2(-0.760,-0.331));
    m->setProperty("u_SpectrumCoords", glm::vec2(0.5,0.9));
    m->setProperty("u_LightPos", glm::vec3(0.0f, 0.5f, 1.9f));

    cube->material()->disable();

    cube->transform().translate(glm::vec3(-0.7f, 0.3f, -0.6f))
            .scale(glm::vec3( 0.205f, 0.205f, 0.205f));
    cube->setPerFrameTransform(Transform().rotate(glm::two_pi<float>()/100.f, glm::vec3(0.0f, 1.0f, 1.0f)));
    scene.addModel(cube);

}


void addTopCube(){
    Material *m = Material::materialBuilder("shaders/mandelbrot/vertex.glsl", "shaders/mandelbrot/fragment.glsl");
    auto cube {new FractalCube(scene,m)};

    cube->init();
    m->setProperty("u_exponent", 0.3);
    m->setProperty("u_juliaSeedPoint",   glm::vec2(-0.835,+0.2131));
    m->setProperty("u_SpectrumCoords", glm::vec2(0.35,0.9));
    m->setProperty("u_LightPos", glm::vec3(0.0f, 0.5f, 1.9f));
    m->setProperty("u_Spectrum", m->getTexture(0));

    cube->transform().translate(glm::vec3(0.3f, 0.7f, -0.6f))
            .scale(glm::vec3( 0.18f, 0.18f, 0.18f));
    cube->setPerFrameTransform(Transform().rotate(glm::two_pi<float>()/150.f, glm::vec3(1.0f, 0.0f, 0.0f)));
    scene.addModel(cube);
}


void addBottomCube(){
    Material *m = Material::materialBuilder("shaders/mandelbrot/vertex.glsl", "shaders/mandelbrot/fragment.glsl");
    auto cube {new FractalCube(scene,m)};

    cube->init();
    m->enable();
    m->setProperty("u_exponent", 0.3);
    m->setProperty("u_juliaSeedPoint",   glm::vec2(-0.835,-0.2131));
    m->setProperty("u_SpectrumCoords", glm::vec2(0.0,0.3));
    m->setProperty("u_LightPos", glm::vec3(0.0f, 0.5f, 1.9f));
    m->setProperty("u_Spectrum", m->getTexture(0));
    m->disable();

    cube->transform().translate(glm::vec3(0.0f, -0.7f, -0.6f))
            .scale(glm::vec3( 0.165f, 0.165f, 0.165f));
    cube->setPerFrameTransform(Transform().rotate(glm::two_pi<float>()/120.f, glm::vec3(0.0f, 1.0f, 0.0f)));
    scene.addModel(cube);
}


void addCentralCube(){
    Material *m = Material::materialBuilder("shaders/mandelbrot/vertex.glsl", "shaders/mandelbrot/fragment.glsl");
    auto cube {new FractalCube(scene,m)};

    cube->init();
    m->enable();
    m->setProperty("u_exponent", 0.3);
    m->setProperty("u_juliaSeedPoint",   glm::vec2(0.2,0.5));
    m->setProperty("u_SpectrumCoords", glm::vec2(0.0,1.0));
    m->setProperty("u_LightPos", glm::vec3(0.0f, 0.5f, 1.9f));
    m->setProperty("u_Spectrum", m->getTexture(0));
    m->disable();

    cube->transform().scale(glm::vec3( 0.25f, 0.25f, 0.25f))
            .translate(glm::vec3(0.0f, 0.0f, -0.6f));
    cube->setPerFrameTransform(Transform().rotate(glm::two_pi<float>()/200.f, glm::vec3(1.0f, 1.0f, 1.0f)));
    scene.addModel(cube);
}

extern "C"  {
    JNIEXPORT void JNICALL
    Java_com_ergv_gles_playground_scenes_FractalPolyhedronsSceneLib_nativeInit(
            JNIEnv* env, jobject obj, jint width, jint height);


    JNIEXPORT void JNICALL
    Java_com_ergv_gles_playground_scenes_FractalPolyhedronsSceneLib_nativeStep(JNIEnv* env, jobject obj);

}


extern "C" {



    JNIEXPORT void JNICALL Java_com_ergv_gles_playground_scenes_FractalPolyhedronsSceneLib_nativeInit(
            JNIEnv*

















            env, jobject obj, jint width, jint height) {
        log_info(LOG_TAG, "@FractalJNILib_init(%d, %d)", width, height);
        setupGraphics(width, height);
    }

    JNIEXPORT void JNICALL Java_com_ergv_gles_playground_scenes_FractalPolyhedronsSceneLib_nativeStep(
            JNIEnv * env, jobject obj) {
        scene.render();
    }


    JNIEXPORT void JNICALL
    Java_com_ergv_gles_playground_scenes_FractalPolyhedronsSceneLib_nativeDestroy(JNIEnv* env, jobject obj) {
        log_info(LOG_TAG, "@GL2JNILib_destroy");
        scene.reset();
        //quantizedCube.renderFrame();
    }
}
