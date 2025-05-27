//
// Created by erez on 04/05/2025.
//

#include <jni.h>
#include "../logger.h"

#include "Scene.h"
#include "../models/MonochromeCube/MonochromeCube.h"
#include "../models/OrangePyramid/OrangePyramid.h"

#define LOG_TAG "CHESS_AND_BRICKS_SHADERS"

static Scene scene;

bool setupGraphics(int w, int h) {
    log_info(LOG_TAG,"@ChessBricksScene::setupGraphics(%d, %d)", w, h);
    scene.reset();
    scene.addDirectionalLight(DirectionalLight());
    auto* cube = new MonochromeCube();
    auto* pyramid = new OrangePyramid();
    //auto* cube = new CubeWithFaceNormals();
    //auto* pyramid = new PyramidWithFaceNormals();
    cube->init();
    pyramid->init();
    scene.addModel(cube);
    scene.addModel(pyramid);
    scene.setClearColor(glm::vec3(0.3f, 0.3f, 0.3f));
    scene.setViewPort(w, h);
    return true;
}

extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_ChessAndBricksSceneLib_nativeInit(JNIEnv* env,
                                                                jobject obj,
                                                                jint width,
                                                                jint height);


extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_ChessAndBricksSceneLib_nativeStep(JNIEnv* env, jobject obj);



extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_ChessAndBricksSceneLib_nativeInit(JNIEnv* env, jobject obj, jint width, jint height) {
    log_info(LOG_TAG, "monochromaticColorsScene_init(%d, %d)", width, height);
    setupGraphics(width, height);
}

extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_ChessAndBricksSceneLib_nativeStep(JNIEnv* env, jobject obj) {
    scene.render();
    //quantizedCube.tick();
    //quantizedCube.renderFrame();
}

extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_ChessAndBricksSceneLib_nativeDestroy(JNIEnv* env, jobject obj) {
    log_info(LOG_TAG, "@GL2JNILib_destroy");
    scene.reset();
    //quantizedCube.renderFrame();
}

