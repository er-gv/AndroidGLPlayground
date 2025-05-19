
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <jni.h>
#include "../logger.h"

#include "../models/FractaledPolyhedrons/FractalCube.h"
#include "Scene.h"

#define LOG_TAG "FRACTAL_COATED_MODELS"

static Scene scene;


bool setupGraphics(int w, int h) {
    log_info(LOG_TAG,"@FractalPolyhedronsScene::setupGraphics(%d, %d)", w, h);

    auto* fractalCube = new FractalCube();

    fractalCube->init();
    scene.addModel(fractalCube);
    scene.setClearColor(glm::vec3{0.831f});
    scene.addDirectionalLight(DirectionalLight{glm::vec3{0.f, -1.f, -1.f}, glm::vec3{0.f, 0.8f, 0.2f}});
    scene.setViewPort(w, h);
    return true;
}




extern "C"  {
    JNIEXPORT void JNICALL
    Java_com_ergv_gles_playground_FractalPolyhedronsSceneLib_nativeInit(
            JNIEnv* env, jobject obj, jint width, jint height);


    JNIEXPORT void JNICALL
    Java_com_ergv_gles_playground_FractalPolyhedronsSceneLib_nativeStep(JNIEnv* env, jobject obj);

}


extern "C" {



    JNIEXPORT void JNICALL Java_com_ergv_gles_playground_FractalPolyhedronsSceneLib_nativeInit(
            JNIEnv* env, jobject obj, jint width, jint height) {
        log_info(LOG_TAG, "@FractalJNILib_init(%d, %d)", width, height);

        setupGraphics(width, height);
    }

    JNIEXPORT void JNICALL Java_com_ergv_gles_playground_FractalPolyhedronsSceneLib_nativeStep(
            JNIEnv * env, jobject obj) {
        scene.render();
    }
}
