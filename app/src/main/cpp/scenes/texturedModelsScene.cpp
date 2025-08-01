
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <jni.h>
#include "../logger.h"

#include "../models/TexturesTest/TexturedPyramid.h"
#include "../models/TexturesTest/TexturedCube.h"
#include "Scene.h"

#define LOG_TAG "FRACTAL_COATED_MODELS"



static Scene scene;

void addCubeModel() {

    auto material {Material::materialBuilder("shaders/hello_texture/vertex.glsl",
                                                      "shaders/hello_texture/fragment.glsl")};
    auto* companionCube = new TexturedCube(scene, material);
    companionCube->init();
    companionCube->transform().

        translate(glm::vec3(0.0f, -97.5f, -.7f)).
        scale(glm::vec3(0.35f))
    ;
    companionCube->setPerFrameTransform(Transform().rotate(0.035f* glm::two_pi<float>(), glm::vec3{1.0f, 1.0f, 0.0f}));

    companionCube->material()->enable();
    companionCube->material()->setProperty("u_LightPos", glm::vec3{3.50f, 0.8f, 0.9f});
    companionCube->material()->disable();

    scene.addModel(companionCube);
}


void addPyramidModel() {

    auto material {Material::materialBuilder("shaders/hello_texture/vertex.glsl",
                                             "shaders/hello_texture/fragment.glsl")};
    auto* model = new TexturedPyramid(scene, material);
    model->init();
    model->transform().
            scale(glm::vec3{3.5, 1.0,3.5}).
            scale(glm::vec3{0.4f}).
            translate(glm::vec3(+0.83f, +19.5f, -8.7f)).

            rotate(+0.25*glm::pi<float>(), glm::vec3{1.0f, 0.0f, 0.0f}).
            rotate(-0.25*glm::pi<float>(), glm::vec3{0.0f, 0.0f, 1.0f})
            ;
    model->setPerFrameTransform(Transform().rotate(-0.035f* glm::two_pi<float>(), glm::vec3{0.0f, 1.0f, 0.0f}));

    model->material()->enable();
    model->material()->setProperty("u_LightPos", glm::vec3{0.0f, 0.8f, 0.9f});
    model->material()->disable();

    scene.addModel(model);
}


bool setupGraphics(int w, int h) {
    log_info(LOG_TAG,"@FractalPolyhedronsScene::setupGraphics(%d, %d)", w, h);
    scene.reset();
    //auto* texturedPyramid = new TexturedPyramid(scene, Material::materialBuilder("shaders/hello_texture/vertex.glsl", "shaders/hello_texture/fragment.glsl"));

    //scene.addModel(texturedPyramid);
    scene.setClearColor(glm::vec3{0.25f});
    scene.addDirectionalLight(DirectionalLight{glm::vec3{0.f, -1.f, -1.f}, glm::vec3{0.f, 0.8f, 0.2f}});
    scene.setEnvironmentLight(EnvironmentLight{glm::vec3{1.0, 1.0, 0.f}, 0.5f});
    scene.setViewPort(w, h);

    addCubeModel();
    addPyramidModel();
    return true;
}




extern "C"  {

    JNIEXPORT void JNICALL
    Java_com_ergv_gles_playground_scenes_TexturedModelsSceneLib_nativeInit(
            JNIEnv* env, jobject obj, jint width, jint height);


    JNIEXPORT void JNICALL
    Java_com_ergv_gles_playground_scenes_TexturedModelsSceneLib_nativeStep(JNIEnv* env, jobject obj);

    JNIEXPORT void JNICALL
    Java_com_ergv_gles_playground_scenes_TexturedModelsSceneLib_nativeDestroy(JNIEnv* env, jobject obj);

}


extern "C" {

    JNIEXPORT void JNICALL Java_com_ergv_gles_playground_scenes_TexturedModelsSceneLib_nativeInit(
            JNIEnv* env, jobject obj, jint width, jint height) {
        log_info(LOG_TAG, "@TexturedModels_init(%d, %d)", width, height);

        setupGraphics(width, height);
    }

    JNIEXPORT void JNICALL Java_com_ergv_gles_playground_scenes_TexturedModelsSceneLib_nativeStep(
            JNIEnv * env, jobject obj) {
        scene.render();
    }


    JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_scenes_TexturedModelsSceneLib_nativeDestroy(JNIEnv* env, jobject obj) {
        log_info(LOG_TAG, "@TexturedModels_destroy");
        scene.reset();
        //quantizedCube.renderFrame();
    }
}
