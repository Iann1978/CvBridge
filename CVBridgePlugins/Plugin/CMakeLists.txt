

# source files
file(GLOB_RECURSE SRC_UNITY
    "./Unity/*.cpp"
    "./Unity/*.h"
)

file(GLOB_RECURSE SRC_GLEW
    "./GLEW/*.cpp"
    "./GLEW/*.h"
	"./GLEW/*.c"
)

file(GLOB_RECURSE SRC_CVBRIDGE
    "./CVBridge/*.cpp"
    "./CVBridge/*.h"
)


file(GLOB_RECURSE SRC_DEMOS
    "./Demos/*.cpp"
    "./Demos/*.h"
)

source_group("Unity"            FILES ${SRC_UNITY})
source_group("GLEW"            FILES ${SRC_GLEW})
source_group("CVBridge"            FILES ${SRC_CVBRIDGE})
source_group("Demos"            FILES ${SRC_DEMOS})

set(SOURCES
	${SRC_UNITY}
	${SRC_GLEW}
	${SRC_CVBRIDGE}
	${SRC_DEMOS})

# include directores
include_directories(.)
include_directories(${CMAKE_SOURCE_DIR}/../3rdparty/opencv-3.4.4-vc14_vc15/build/include)

link_directories(${CMAKE_SOURCE_DIR}/../3rdparty/opencv-3.4.4-vc14_vc15/build/x64/vc15/lib)

# predefined macro
add_definitions(-DGLEW_STATIC)

# add libs
link_libraries(opencv_world344d.lib opengl32.lib)


# add the project
add_library(CVBridgePlugin SHARED ${SOURCES})


# post event
add_custom_command(
TARGET CVBridgePlugin 
POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy  ${CMAKE_BINARY_DIR}/Plugin/Debug/CVBridgePlugin.dll ${CMAKE_SOURCE_DIR}/../CVBridgeUnity/Assets/cvBridge/Plugins/x64/cvBridge.dll
)


