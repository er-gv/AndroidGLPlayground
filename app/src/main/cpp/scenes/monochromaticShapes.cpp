//
// Created by erez on 04/05/2025.
//

#include <jni.h>
#include "../logger.h"

#include "../scenes/Scene.h"
#include "../models/MonochromeCube/MonochromeCube.h"
#include "../models/OrangePyramid/OrangePyramid.h"

#define LOG_TAG "MONOCHROME_CUBE"

static Scene scene;

bool setupGraphics(int w, int h) {
    log_info(LOG_TAG,"@monochromaticColorsScene::setupGraphics(%d, %d)", w, h);
    scene.reset();
    scene.addDirectionalLight(DirectionalLight());
    auto* monochromeCube = new MonochromeCube();
    auto* orangePyramid = new OrangePyramid();
    monochromeCube->init();
    orangePyramid->init();
    scene.addModel(monochromeCube);
    scene.addModel(orangePyramid);
    scene.setClearColor(glm::vec3(0.0f, 0.3f, 0.0f));
    scene.setViewPort(w, h);
    return true;
}

extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_scenes_MonochromaticModels_nativeInit(JNIEnv* env,
                                                                      jobject obj,
                                                                      jint width,
                                                                      jint height);


extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_scenes_MonochromaticModels_nativeStep(JNIEnv* env, jobject obj);



extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_scenes_MonochromaticModels_nativeInit(JNIEnv* env, jobject obj, jint width, jint height) {
    log_info(LOG_TAG, "monochromaticColorsScene_init(%d, %d)", width, height);
    setupGraphics(width, height);
}

extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_scenes_MonochromaticModels_nativeStep(JNIEnv* env, jobject obj) {
    scene.render();
    //quantizedCube.tick();
    //quantizedCube.renderFrame();
}

extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_scenes_MonochromaticModels_nativeDestroy(JNIEnv* env, jobject obj) {
    log_info(LOG_TAG, "@GL2JNILib_destroy");
    scene.reset();
    //quantizedCube.renderFrame();
}

