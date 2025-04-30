package com.ergv.quantizedshapes

import android.content.res.AssetManager

abstract class AbstractJNILib {
    abstract fun init(width: Int, height: Int);
    abstract fun step();


}