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
    scene.setViewPort(w, h);
    return true;
}




extern "C"  {
    JNIEXPORT void JNICALL
    Java_com_ergv_quantizedshapes_FractalPolyhedronsSceneLib_nativeInit(
            JNIEnv* env, jobject obj, jint width, jint height);


    JNIEXPORT void JNICALL
    Java_com_ergv_quantizedshapes_FractalPolyhedronsSceneLib_nativeStep(JNIEnv* env, jobject obj);

}


extern "C" {



    JNIEXPORT void JNICALL Java_com_ergv_quantizedshapes_FractalPolyhedronsSceneLib_nativeInit(
            JNIEnv* env, jobject obj, jint width, jint height) {
        log_info(LOG_TAG, "@FractalJNILib_init(%d, %d)", width, height);

        setupGraphics(width, height);
    }

    JNIEXPORT void JNICALL Java_com_ergv_quantizedshapes_FractalPolyhedronsSceneLib_nativeStep(
            JNIEnv * env, jobject obj) {
        scene.render();
    }
}
