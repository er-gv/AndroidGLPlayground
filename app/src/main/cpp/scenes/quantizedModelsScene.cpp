/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// OpenGL ES 2.0 code


#include <jni.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include "../logger.h"

#include "../models/QuantizedCube/QuantizedCube.h"
#include "../scenes/Scene.h"

#define LOG_TAG "GL2JNILib"

static Scene scene;

bool setupGraphics(int w, int h) {
    log_info(LOG_TAG,"@quantizeModelsScene::setupGraphics(%d, %d)", w, h);

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
Java_com_ergv_gles_playground_QuantizedPolyhedronsSceneLib_nativeStep(JNIEnv* env, jobject obj);



extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_QuantizedPolyhedronsSceneLib_nativeInit(JNIEnv* env, jobject obj, jint width, jint height) {
    log_info(LOG_TAG, "@GL2JNILib_init(%d, %d)", width, height);
    setupGraphics(width, height);
}

extern "C" JNIEXPORT void JNICALL
Java_com_ergv_gles_playground_QuantizedPolyhedronsSceneLib_nativeStep(JNIEnv* env, jobject obj) {
    scene.render();
    //quantizedCube.tick();
    //quantizedCube.renderFrame();
}
