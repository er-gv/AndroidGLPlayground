package com.ergv.glsandbox

import android.os.Bundle
import android.widget.ImageView
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentTransaction
import kotlin.text.replace

class MainActivity2 : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(R.layout.activity_main2)

        val myFragments: List<Fragment> = listOf(
            ImageButtonFragment(), ImageButtonFragment(), ImageButtonFragment()
        )

        val transaction: FragmentTransaction = supportFragmentManager.beginTransaction()
        transaction.replace(R.id.main_activity_layout, myFragments[0])
            .replace(R.id.main_activity_layout, myFragments[1])
            .replace(R.id.main_activity_layout, myFragments[2])
        transaction.commit()


    }
}