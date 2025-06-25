package com.ergv.gles.playground.scenes

abstract class AbstractScene {
    abstract fun init(width: Int, height: Int);
    abstract fun step();
    abstract fun destroy();


}