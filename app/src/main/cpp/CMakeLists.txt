cmake_minimum_required(VERSION 3.22.1)
project("gles_playground")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
#set(CMAKE_PREFIX_PATH "/usr/local/usr")

set(PROJECT_ROOT "src/main/cpp")
include_directories(${PROJECT_ROOT})

set(ENGINE_HOME "src/main/cpp/engine")
include_directories(${PROJECT_ROOT})

set(GLM_HOME "src/main/cpp/engine/libs/glm")
include_directories(${GLM_HOME})

set(STB_HOME "src/main/cpp/engine/libs/images_lib")
include_directories(${STB_HOME})

#set(PERLIN_HOME "libs/PerlinNoise/")
#include_directories(${PERLIN_HOME})

#set(MODELS "models")
#include_directories(${MODELS})

find_library(log-lib log)


#include_directories(${LIBPNG_HOME})

# Try to find GLM. It might be installed on the system,
# or it could be in a common location.


add_library(logger SHARED logger.cpp)
target_link_libraries(logger
        ${log-lib}
        EGL  # Direct dependency
        GLESv2 # Direct dependency
        android
)

####################################################################
##
## Main engine libraries
##
####################################################################
add_library(assetsFactory SHARED engine/AssetsFactory.cpp)
target_include_directories(assetsFactory PRIVATE ${GLM_HOME}
)
target_link_libraries(assetsFactory
        logger
        EGL  # Direct dependency
        GLESv2 # Direct dependency
        android
)

add_library(shadersFactory SHARED engine/shadersBuilder.cpp)
target_link_libraries(shadersFactory
        logger
        assetsFactory
        android
        EGL  # Direct dependency
        GLESv2 # Direct dependency
)


add_library(texturesFactory SHARED engine/texturesFactory.cpp)
target_include_directories(texturesFactory
        PRIVATE ${STB_HOME})
#include_directories(${PERLIN_HOME})
target_link_libraries(texturesFactory
        assetsFactory # for AAsset reading api
        android       # For AAssetManager, etc.
        log           # For logging (__android_log_print)
        GLESv2        # For OpenGL ES 2.0 functions
)


add_library(lights SHARED engine/lights/DirectionalLight.cpp)
target_include_directories(lights
        PRIVATE ${GLM_HOME})
target_link_libraries(lights
        logger
        android
        EGL  # Direct dependency
        GLESv2 # Direct dependency
)


add_library(materials SHARED engine/materials/Material.cpp)
target_link_libraries(materials
        logger
        shadersFactory
        texturesFactory
        android
        EGL  # Direct dependency
        GLESv2 # Direct dependency
)

#add_library(camera SHARED exclude_from_build/Camera.cpp)
#target_include_directories(camera
#        PRIVATE ${GLM_HOME})
#target_link_libraries(camera)


#add_library(model SHARED models/Model.cpp)
#target_link_libraries(model
#        logger
#        EGL # Direct dependency
#        GLESv2 # Direct dependency
#)
####################################################################
##
## Models libraries
##
####################################################################


add_library(monochromeCube SHARED models/monochromeShapes/MonochromeCube.cpp)
target_include_directories(monochromeCube
        PRIVATE ${GLM_HOME})
target_link_libraries(monochromeCube
        #        model
        shadersFactory
        materials
        logger
        android
        EGL # Direct dependency
        GLESv2 # Direct dependency
)

add_library(orangePyramid SHARED models/monochromeShapes/OrangePyramid.cpp)
target_include_directories(orangePyramid PRIVATE
        ${GLM_HOME})
target_link_libraries(orangePyramid
        materials
        shadersFactory
        logger
        android
        EGL # Direct dependency
        GLESv2 # Direct dependency
)


add_library(icosahedron SHARED models/monochromeShapes/plutonic/Icosahedron.cpp)
target_include_directories(icosahedron PRIVATE
        ${GLM_HOME})
target_link_libraries(icosahedron
        materials
        shadersFactory
        logger
        android
        EGL # Direct dependency
        GLESv2 # Direct dependency
)


add_library(quantizedCube SHARED models/QuantizedCube/QuantizedCube.cpp)
target_include_directories(quantizedCube
        PRIVATE ${GLM_HOME})
target_link_libraries(quantizedCube
        materials
        shadersFactory
        logger
        android
        EGL # Direct dependency
        GLESv2 # Direct dependency
)

add_library(chessCube SHARED models/Chess/ChessCube.cpp)
target_include_directories(chessCube
        PRIVATE ${GLM_HOME}
)
target_link_libraries(chessCube
        shadersFactory
        materials
        logger
        android
        EGL # Direct dependency
        GLESv2 # Direct dependency
)

add_library(chessPyramid SHARED models/Chess/ChessPyramid.cpp)
target_include_directories(chessPyramid
        PRIVATE ${GLM_HOME}
)
target_link_libraries(chessPyramid
        shadersFactory
        materials
        logger
        android
        EGL # Direct dependency
        GLESv2 # Direct dependency
)


#add_library(icosahedron SHARED models/Chess/Icosahedron.cpp)
#target_include_directories(icosahedron
#        PRIVATE ${GLM_HOME})
#target_link_libraries(icosahedron
#        shadersFactory
#        logger
#        android
#        EGL # Direct dependency
#        GLESv2 # Direct dependency
#)


add_library(fractalPolyhedrons SHARED models/FractaledPolyhedrons/FractalCube.cpp)
target_include_directories(fractalPolyhedrons
        PRIVATE ${GLM_HOME}
)
target_link_libraries(fractalPolyhedrons
#        model
        materials
        shadersFactory
        logger
        android
        EGL # Direct dependency
        GLESv2 # Direct dependency
)


add_library(texturedPyramid SHARED models/TexturesTest/TexturedPyramid.cpp)
target_include_directories(texturedPyramid
        PRIVATE ${GLM_HOME})
target_link_libraries(texturedPyramid
        #        model
        materials
        logger
        android
        EGL # Direct dependency
        GLESv2 # Direct dependency
)


add_library(texturedCube SHARED models/TexturesTest/TexturedCube.cpp)
target_include_directories(texturedCube
        PRIVATE ${GLM_HOME})
target_link_libraries(texturedCube
        #        model
        materials
        logger
        android
        EGL # Direct dependency
        GLESv2 # Direct dependency
)

####################################################################
##
## All scenes libraries
##
####################################################################
add_library(scenes SHARED scenes/Scene.cpp)
target_include_directories(scenes
        PRIVATE ${MODELS}
        PRIVATE  ${GLM_HOME}
)
target_link_libraries(scenes
#        camera
        materials
        logger
        android
        lights
        EGL
        GLESv2
)


add_library(fractalPolyhedronsScene SHARED scenes/fractalPolyhedronsScene.cpp)
target_include_directories(scenes
        PRIVATE ${MODELS}
        PRIVATE ${GLM_HOME}
)
target_link_libraries(fractalPolyhedronsScene
        scenes
        fractalPolyhedrons
        logger
        EGL # Direct dependency
        GLESv2 # Direct dependency
)


add_library(quantizedPolyhedronsScene SHARED scenes/quantizedModelsScene.cpp)
target_include_directories(scenes
        PRIVATE ${MODELS}
        PRIVATE ${GLM_HOME}
)

target_link_libraries(quantizedPolyhedronsScene
        scenes
        quantizedCube
        logger
        EGL # Direct dependency
        GLESv2 # Direct dependency
)


add_library(monochromaticShapesScene SHARED scenes/monochromaticShapes.cpp)
target_include_directories(scenes
        PRIVATE ${MODELS}
        PRIVATE ${GLM_HOME}
)

target_link_libraries(monochromaticShapesScene
        scenes
        monochromeCube
        orangePyramid
        logger
        EGL # Direct dependency
        GLESv2 # Direct dependency
)


add_library(chessAndBricksScene SHARED scenes/ChessAndBricksScene.cpp)
target_include_directories(scenes
        PRIVATE ${MODELS}
)
target_include_directories(scenes
        PRIVATE ${GLM_HOME}
)
target_link_libraries(chessAndBricksScene
        scenes
        chessCube
        chessPyramid
        logger
        EGL # Direct dependency
        GLESv2 # Direct dependency
)


add_library(texturedModelsScene SHARED scenes/texturedModelsScene.cpp)
target_include_directories(scenes
        PRIVATE ${MODELS}
)
target_include_directories(scenes
        PRIVATE ${GLM_HOME}
)
target_link_libraries(texturedModelsScene
        scenes
        texturedCube
        texturedPyramid
        logger
        EGL # Direct dependency
        GLESv2 # Direct dependency
)




