package com.ergv.gles.playground.scenes

class FractalPolyhedronsSceneLib : AbstractScene() {
    init {
        System.loadLibrary("fractalPolyhedronsScene")
    }

    /**
     * @param width the current view width
     * @param height the current view height
     */

    external fun nativeInit(width: Int, height: Int)
    external fun nativeStep()
    external fun nativeDestroy()

    public override fun init(width: Int, height: Int){
        nativeInit(width, height)
    }

    public override fun step(){
        nativeStep()
    }

    public override fun destroy(){
        nativeDestroy();
    }

}