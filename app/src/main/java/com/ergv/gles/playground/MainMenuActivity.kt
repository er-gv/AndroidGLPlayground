package com.ergv.gles.playground

import android.content.Context
import android.content.Intent
import android.os.Bundle

import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.style.TextAlign

import androidx.compose.foundation.Image
import androidx.compose.foundation.border
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.width
//import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.material3.Surface
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.RectangleShape
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.ergv.gles.playground.R
import com.ergv.gles.playground.theme.ui.GlesPlaygroundTheme


class MainMenuActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            Surface(
                modifier = Modifier.fillMaxSize(),
                color = MaterialTheme.colorScheme.background
            ) {

                VerticleMenu(
                    this,
                    arrayOf("Fractal Patterns", "Quantized Triangles", "Monochromatic Faces", "Bricks", "Textures"),
                    arrayOf(R.drawable.non_fractal_pyramid, R.drawable.quantized_cube,
                        R.drawable.monochrome_shapes, R.drawable.bricks_icon, R.drawable.stone_wall_public_domain)
                )
            }
        }

    }

    @Composable
    fun VerticleMenu(
        context: Context,
        captions: Array<String>,
        icons: Array<Int>,
        modifier: Modifier = Modifier
    ) {
        Column(
            horizontalAlignment = Alignment.Start,
            modifier = modifier.padding(vertical = 120.dp)
        )
        {
            for (i in captions.indices) {
                MenuItem(context, captions[i], icons[i], modifier)
            }
        }
    }

    @Composable
    fun MenuItem(context: Context, caption: String, iconID: Int, modifier: Modifier = Modifier) {
        val image = painterResource(id = iconID)

        Row(
            modifier = modifier,
            horizontalArrangement = Arrangement.Center,
        ) {

            Image(
                image, contentDescription = "menu icon",
                modifier = Modifier
                    .clickable {

                        val intent = Intent(
                            context,
                            GLSceneActivity::class.java
                        ) // Replace SecondActivity with your target activity
                        val sceneTag = when(caption){
                            "Fractal Patterns" -> "fractals"
                            "Quantized Triangles" -> "quantized_triangles"
                            "Monochromatic Faces" -> "monochromatic_cubes"
                            "Bricks" -> "Bricks"
                            "Textures" -> "Textures"
                            else -> ""

                        }
                        intent.putExtra("scene_tag", sceneTag)
                        context.startActivity(intent)
                        Toast.makeText(context, caption, Toast.LENGTH_SHORT).show()
                    }
                    .height(120.dp)
                    .width(120.dp)
                    .padding(16.dp)
                    .border(
                        5.dp,
                        Color.Yellow,
                        RectangleShape
                    )


                // below line is used to give
                // alignment to our image view.
                //alignment = Alignment.Center,


                //val toast = Toast.makeText(this, text, duration) // in Activity
                //toast.show()
            )

            Text(
                text = caption,
                fontSize = 38.sp,
                lineHeight = 32.sp,
                textAlign = TextAlign.Start,

                modifier = Modifier.align(alignment = Alignment.CenterVertically)

            )

        }
    }


    @Preview(showBackground = true)
    @Composable
    fun GreetingPreview() {
        GlesPlaygroundTheme {
            MenuItem(MainMenuActivity(), "Canada", R.drawable.quantized_cube)
        }
    }
}
