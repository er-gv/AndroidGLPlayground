package com.ergv.gles.playground

import android.app.Activity
import android.os.Bundle

class GLSceneActivity: Activity() {
    var mView: GLSceneView? = null


    override fun onCreate(icicle: Bundle?) {
        super.onCreate(icicle)
        var tag: String? = intent.getStringExtra("scene_tag")
        if (tag == null) {
            tag = "quantized_triangles"
        }
        val assetsFactory = AssetsFactory()
        assetsFactory.init(assets)
        mView = GLSceneView(getApplication(), tag)
        setContentView(mView)

    }

    override fun onPause() {
        super.onPause()
        mView!!.onPause()
    }

    override fun onResume() {
        super.onResume()
        mView!!.onResume()
    }
}