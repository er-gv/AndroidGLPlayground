#include <jni.h>
#include "../engine/libs/glm/glm.hpp"
#include "../engine/libs/glm/vec3.hpp"
#include "../logger.h"

#include "../models/QuantizedCube/QuantizedCube.h"
#include "../scenes/Scene.h"

#define LOG_TAG "GL2JNILib"

static Scene scene;

void addCubeModel() {

    auto quantizedMaterial {Material::materialBuilder("shaders/quantized_colors/vertex.glsl",
                                                      "shaders/quantized_colors/fragment.glsl")};
    auto* quantizedCube = new QuantizedCube(scene, quantizedMaterial);
    quantizedCube->init();
    quantizedCube->setPerFrameTransform(Transform().rotate(glm::two_pi<float>() / 50.f, glm::vec3{1.0f, 1.0f, -1.0f}));
    scene.addModel(quantizedCube);
}

bool setupGraphics(int w, int h) {
    log_info(LOG_TAG,"@quantizeModelsScene::setupGraphics(%d, %d)", w, h);
    scene.reset();
    scene.setClearColor(glm::vec3{0.1f, 0.6f, 0.85f});
    addCubeModel();
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

