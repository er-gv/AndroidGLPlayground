package com.ergv.gles.playground

import android.content.res.AssetManager

class AssetsFactory {

    init {
        System.loadLibrary("assetsFactory")
    }
    external fun init(assetsManager: AssetManager);
}