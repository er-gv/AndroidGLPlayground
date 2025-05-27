cmake_minimum_required(VERSION 3.22.1)
project("gles_playground")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
#set(CMAKE_PREFIX_PATH ";/usr/local;/usr")
set(GLM_HOME "/usr/local/include/GL/glm")
set(ENGINE_HOME "cpp/engine")
find_library(log-lib log)
include_directories(${GLM_HOME})

# Try to find GLM. It might be installed on the system,
# or it could be in a common location.


add_library(logger SHARED logger.cpp)
target_link_libraries(logger
        ${log-lib}
        EGL  # Direct dependency
        GLESv2 # Direct dependency
        android
)


add_library(assetsFactory SHARED engine/AssetsFactory.cpp)
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

add_library(lights SHARED engine/lights/DirectionalLight.cpp)
target_include_directories(lights
        PRIVATE ${GLM_HOME})
target_link_libraries(lights
        logger
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

add_library(orangePyramid SHARED models/OrangePyramid/OrangePyramid.cpp)
target_link_libraries(orangePyramid
        #        model
        shadersFactory
        logger
        android
        EGL # Direct dependency
        GLESv2 # Direct dependency
)


add_library(quantizedCube SHARED models/QuantizedCube/QuantizedCube.cpp)
target_link_libraries(quantizedCube
#        model
        shadersFactory
        logger
        android
        EGL # Direct dependency
        GLESv2 # Direct dependency
)

add_library(chessCube SHARED models/Chess/ChessCube.cpp)
target_link_libraries(chessCube
        shadersFactory
        logger
        android
        EGL # Direct dependency
        GLESv2 # Direct dependency
)

add_library(chessPyramid SHARED models/Chess/ChessPyramid.cpp)
target_link_libraries(chessPyramid
        shadersFactory
        logger
        android
        EGL # Direct dependency
        GLESv2 # Direct dependency
)


add_library(icosahedron SHARED models/Chess/Icosahedron.cpp)
target_link_libraries(icosahedron
        shadersFactory
        logger
        android
        EGL # Direct dependency
        GLESv2 # Direct dependency
)


add_library(fractalPolyhedrons SHARED models/FractaledPolyhedrons/FractalCube.cpp)
target_link_libraries(fractalPolyhedrons
#        model
        shadersFactory
        logger
        android
        EGL # Direct dependency
        GLESv2 # Direct dependency
)


add_library(monochromeCube SHARED models/MonochromeCube/MonochromeCube.cpp)
target_link_libraries(monochromeCube
        #        model
        shadersFactory
        logger
        android
        EGL # Direct dependency
        GLESv2 # Direct dependency
)


add_library(scenes SHARED scenes/Scene.cpp)
#target_include_directories(scenes
#        PRIVATE ${GLM_HOME})
target_link_libraries(scenes
#        camera
        logger
        android
        lights
        EGL
        GLESv2
)


add_library(fractalPolyhedronsScene SHARED scenes/fractalPolyhedronsScene.cpp)
#target_include_directories(fractalPolyhedronsScene
#        PRIVATE ${GLM_HOME})
target_link_libraries(fractalPolyhedronsScene
        scenes
        fractalPolyhedrons
        logger
        EGL # Direct dependency
        GLESv2 # Direct dependency
)


add_library(quantizedPolyhedronsScene SHARED scenes/quantizedModelsScene.cpp)
#target_include_directories(quantizedPolyhedronsScene
#        PRIVATE ${GLM_HOME})
target_link_libraries(quantizedPolyhedronsScene
        scenes
        quantizedCube
        logger
        EGL # Direct dependency
        GLESv2 # Direct dependency
)


add_library(monochromaticShapesScene SHARED scenes/monochromaticShapes.cpp)
target_link_libraries(monochromaticShapesScene
        scenes
        monochromeCube
        orangePyramid
        logger
        EGL # Direct dependency
        GLESv2 # Direct dependency
)


add_library(chessAndBricksScene SHARED scenes/ChessAndBricksScene.cpp)
target_link_libraries(chessAndBricksScene
        scenes
        chessCube
        chessPyramid
        icosahedron
        logger
        EGL # Direct dependency
        GLESv2 # Direct dependency
)



