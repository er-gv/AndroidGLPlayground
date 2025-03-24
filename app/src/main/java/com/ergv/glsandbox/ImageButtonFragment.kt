package com.ergv.glsandbox

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.ImageView
import android.widget.Toast
import androidx.fragment.app.Fragment

class ImageButtonFragment : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val view = inflater.inflate(R.layout.fragment_image_button, container, false)

        // Find the views
        val imageView = view.findViewById<ImageView>(R.id.myImageView)
        val button = view.findViewById<Button>(R.id.myButton)

        // Set the image (you can replace this with a different image)
        imageView.setImageResource(R.drawable.ic_launcher_foreground)

        // Set the button click listener
        button.setOnClickListener {
            // Handle button click here
            Toast.makeText(context, "Button Clicked!", Toast.LENGTH_SHORT).show()
        }

        return view
    }
}