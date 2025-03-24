#include <jni.h>
#include <GLES2/gl2.h>
#include <android/log.h>

// Vertex shader source code
const char* vertexShaderSource =
        "attribute vec4 vPosition;"
        "void main() {"
        "  gl_Position = vPosition;"
        "}";

// Fragment shader source code
const char* fragmentShaderSource =
        "precision mediump float;"
        "uniform vec4 vColor;"
        "void main() {"
        "  gl_FragColor = vColor;"
        "}";

// Shader program variables
GLuint shaderProgram;
GLuint vPosition;
GLuint vColor;

// Triangle vertices
GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f,  // Vertex 1 (X, Y, Z)
        -0.5f, -0.5f, 0.0f, // Vertex 2 (X, Y, Z)
        0.5f, -0.5f, 0.0f   // Vertex 3 (X, Y, Z)
};

// Function to compile shader
GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    if (shader == 0) {
        __android_log_print(ANDROID_LOG_ERROR, "OpenGL ES", "Error creating shader");
        return 0;
    }

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            char* infoLog = (char*)malloc(sizeof(char) * infoLen);
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            __android_log_print(ANDROID_LOG_ERROR, "OpenGL ES", "Error compiling shader:\n%s\n", infoLog);
            free(infoLog);
        }
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

extern "C" JNIEXPORT jboolean JNICALL Java_com_example_nativeopenglapp_MyGLRenderer_init(JNIEnv* env, jobject /* this */) {

    // Compile vertex shader
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    if (vertexShader == 0) {
        return false;
    }

    // Compile fragment shader
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    if (fragmentShader == 0) {
        glDeleteShader(vertexShader);
        return false;
    }

    // Create program
    shaderProgram = glCreateProgram();
    if (shaderProgram == 0) {
        __android_log_print(ANDROID_LOG_ERROR, "OpenGL ES", "Error creating program");
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }

    // Attach shaders and link program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for errors
    GLint linked;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint infoLen = 0;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            char* infoLog = (char*)malloc(sizeof(char) * infoLen);
            glGetProgramInfoLog(shaderProgram, infoLen, NULL, infoLog);
            __android_log_print(ANDROID_LOG_ERROR, "OpenGL ES", "Error linking program:\n%s\n", infoLog);
            free(infoLog);
        }
        glDeleteProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }

    // After successful linking detach shaders
    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);

    // Now delete shaders, they are not needed anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Get attribute and uniform locations
    vPosition = glGetAttribLocation(shaderProgram, "vPosition");
    vColor = glGetUniformLocation(shaderProgram, "vColor");

    // Set clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    return true;
}

extern "C" JNIEXPORT jboolean JNICALL Java_com_example_nativeopenglapp_MyGLRenderer_render(JNIEnv* env, jobject /* this */) {

    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use program
    glUseProgram(shaderProgram);

    // Set uniform values
    glUniform4f(vColor, 0.0f, 0.0f, 1.0f, 1.0f); // Blue color

    // Load vertex data
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(vPosition);

    // Draw triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);

    return true;
}

extern "C" JNIEXPORT void JNICALL Java_com_example_nativeopenglapp_MyGLRenderer_resize(JNIEnv* env, jobject /* this */, jint width, jint height) {
// Set the viewport
glViewport(0, 0, width, height);
}