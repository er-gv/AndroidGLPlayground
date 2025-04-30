package com.ergv.quantizedshapes

import android.content.res.AssetManager

class AssetsFactory {

    init {
        System.loadLibrary("assetsFactory")
    }
    external fun init(assetsManager: AssetManager);
}