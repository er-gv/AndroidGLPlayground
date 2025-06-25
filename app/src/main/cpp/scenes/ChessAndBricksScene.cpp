//
// Created by erez on 04/05/2025.
//

#include <jni.h>
#include "../logger.h"

#include "Scene.h"
#include "../models/Chess/ChessCube.h"
#include "../models/Chess/ChessPyramid.h"
#include "../engine/materials/Material.h"

#define LOG_TAG "CHESS_AND_BRICKS_SHADERS"

static Scene scene;


void addCubeModel() {
    auto *cube = new ChessCube(scene,Material::materialBuilder(
            "shaders/chess/vertex.glsl",
            "shaders/chess/fragment.glsl")
    );
    cube->init();
    cube->transform().scale(glm::vec3{0.35f}).translate(glm::vec3(-0.60f, 0.6f, -.4f));
    cube->setPerFrameTransform(Transform()
            .rotate(glm::two_pi<float>() / 250.f, glm::vec3(-1.0f, 1.0f, 1.0f)
            ));
}

void addPyramidModel(){
    auto *pyramid = new ChessCube(scene,Material::materialBuilder(
            "shaders/chess/vertex.glsl",
            "shaders/chess/fragment.glsl")
    );
    pyramid->init();

    pyramid->transform().
        scale(glm::vec3{0.6f}).
        translate(glm::vec3(-0.3f, +0.15f, -0.3f)).
        rotate(-0.3*glm::half_pi<float>(), glm::vec3(1.0f, 0.0f, 1.0f) );

    pyramid->setPerFrameTransform(
            Transform().rotate(glm::two_pi<float>() / 200.f, glm::vec3(0.0f, 1.0f, 0.0f)));

    scene.addModel(pyramid);
}

bool setupGraphics(int w, int h) {
    log_info(LOG_TAG,"@ChessBricksScene::setupGraphics(%d, %d)", w, h);
    scene.reset();
    //scene.addPointLight();
    scene.addDirectionalLight(DirectionalLight());
    scene.setClearColor(glm::vec3(0.3f, 0.3f, 0.3f));
    scene.setWaitBetweenFramesMillis(150u);
    addCubeModel();
    addPyramidModel();
    scene.setViewPort(w, h);
    return true;
}

extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_ChessAndBricksSceneLib_nativeInit(
        JNIEnv* env,  jobject obj, jint width, jint height);


extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_scenes_ChessAndBricksSceneLib_nativeStep(
        JNIEnv* env, jobject obj);



extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_scenes_ChessAndBricksSceneLib_nativeInit(JNIEnv* env, jobject obj, jint width, jint height) {
    log_info(LOG_TAG, "monochromaticColorsScene_init(%d, %d)", width, height);
    setupGraphics(width, height);
}

extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_scenes_ChessAndBricksSceneLib_nativeStep(JNIEnv* env, jobject obj) {
    scene.render();
}

extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_scenes_ChessAndBricksSceneLib_nativeDestroy(JNIEnv* env, jobject obj) {
    log_info(LOG_TAG, "@GL2JNILib_destroy");
    scene.reset();
    //quantizedCube.renderFrame();
}

