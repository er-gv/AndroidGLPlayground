package com.ergv.glsandbox

import android.app.NativeActivity
import android.content.Intent
import android.os.Bundle
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val button1: Button = findViewById(R.id.button1)
        val button2: Button = findViewById(R.id.button2)
        val button3: Button = findViewById(R.id.button3)

        button1.setOnClickListener {
            launchNativeActivity()
        }

        button2.setOnClickListener {
            launchNativeActivity()
        }

        button3.setOnClickListener {
            launchNativeActivity()
        }
    }

    private fun launchNativeActivity() {
        val intent = Intent(this, NativeActivity::class.java)
        startActivity(intent)
    }
}