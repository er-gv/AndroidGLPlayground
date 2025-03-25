package com.ergv.glsandbox


import android.opengl.GLSurfaceView
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class NativeActivity : AppCompatActivity() {

    private lateinit var glSurfaceView: GLSurfaceView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        // Create a GLSurfaceView instance and set it
        // as the ContentView for this Activity.
        glSurfaceView = GLSurfaceView(this)
        glSurfaceView.setEGLContextClientVersion(2) // Use OpenGL ES 2.0
        glSurfaceView.setRenderer(MyGLRenderer())
        setContentView(glSurfaceView)

    }
}

class MyGLRenderer : GLSurfaceView.Renderer {

    external fun init(): Boolean
    external fun render(): Boolean
    external fun resize(width: Int, height: Int)

    init {
        System.loadLibrary("native-lib")
    }

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        init()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        resize(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        render()
    }
}