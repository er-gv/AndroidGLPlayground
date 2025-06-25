//
// Created by erez on 04/05/2025.
//

#include <jni.h>
#include "../logger.h"

#include "../scenes/Scene.h"
#include "../models/monochromeShapes/MonochromeCube.h"
#include "../models/monochromeShapes/OrangePyramid.h"

#define LOG_TAG "MONOCHROME_CUBE"

static Scene scene;

void addCubeModel() {
    auto monochromaticMaterial {Material::materialBuilder(
            "shaders/monochrome_with_normals/vertex.glsl",
            "shaders/monochrome_with_normals/fragment.glsl")};
    auto* cube = new MonochromeCube(scene, monochromaticMaterial);
    cube->init();

    cube->transform().translate(glm::vec3(0.350f, 0.5f, 0.0f)).scale(glm::vec3{0.35f});
    cube->setPerFrameTransform(Transform().rotate(glm::two_pi<float>() / 200.f, glm::vec3{0.0f, 1.0f, 0.0f}));

    cube->material()->enable();
    //cube->material()->setProperty("uLightDirection", glm::vec3{0,0, -1});
    cube->material()->disable();
    scene.addModel(cube);
}

void addPyramidModel() {
    auto monochromaticMaterial {Material::materialBuilder("shaders/monochrome_with_normals/vertex.glsl",
                                                          "shaders/monochrome_with_normals/fragment.glsl")};
    auto* pyramid = new OrangePyramid(scene, monochromaticMaterial);
    pyramid->init();

    pyramid->transform()
        .scale(glm::vec3{0.65f})
        .translate(glm::vec3{-0.2f, -0.2f, -0.3f})
        .rotate(glm::two_pi<float>() / 50.f, glm::vec3{1.0f, 1.0f, -1.0f});

    pyramid->setPerFrameTransform(Transform().rotate(glm::two_pi<float>() / 200.f, glm::vec3{0.0f, 1.0f, 0.0f}));
    scene.addModel(pyramid);
}

bool setupGraphics(int w, int h) {
    log_info(LOG_TAG,"@monochromaticColorsScene::setupGraphics(%d, %d)", w, h);
    scene.reset();
    scene.addDirectionalLight(DirectionalLight());
    scene.setClearColor(glm::vec3(0.0f, 0.3f, 0.0f));
    scene.setViewPort(w, h);
    scene.setWaitBetweenFramesMillis(20);
    addPyramidModel();
    addCubeModel();

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

