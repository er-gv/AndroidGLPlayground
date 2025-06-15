#include <jni.h>
#include "../engine/libs/glm/glm.hpp"
#include "../engine/libs/glm/vec3.hpp"
#include "../logger.h"

#include "../models/QuantizedCube/QuantizedCube.h"
#include "../scenes/Scene.h"

#define LOG_TAG "GL2JNILib"

static Scene scene;

bool setupGraphics(int w, int h) {
    log_info(LOG_TAG,"@quantizeModelsScene::setupGraphics(%d, %d)", w, h);
    scene.reset();
    auto* fractalCube = new QuantizedCube();
    fractalCube->init();
    scene.addModel(fractalCube);
    scene.setClearColor(glm::vec3{0.1f, 0.6f, 0.85f});

    scene.setViewPort(w, h);
    return true;
}

extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_QuantizedPolyhedronsSceneLib_nativeInit(JNIEnv* env,
                                                                      jobject obj,
                                                                      jint width,
                                                                      jint height);


extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_scenes_QuantizedPolyhedronsSceneLib_nativeStep(JNIEnv* env, jobject obj);



extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_scenes_QuantizedPolyhedronsSceneLib_nativeInit(JNIEnv* env, jobject obj, jint width, jint height) {
    log_info(LOG_TAG, "@GL2JNILib_init(%d, %d)", width, height);
    setupGraphics(width, height);
}

extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_scenes_QuantizedPolyhedronsSceneLib_nativeStep(JNIEnv* env, jobject obj) {
    scene.render();
    //quantizedCube.tick();
    //quantizedCube.renderFrame();
}

extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_scenes_QuantizedPolyhedronsSceneLib_nativeDestroy(JNIEnv* env, jobject obj) {
    log_info(LOG_TAG, "@GL2JNILib_destroy");
    scene.reset();
    //quantizedCube.renderFrame();
}

