

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
include_directories(E:/git/opencv/opencv3_4/build/include)

link_directories(E:/githome/opencv/opencv3_4/build/lib/Debug)

# predefined macro
add_definitions(-DGLEW_STATIC)

# add libs
link_libraries(${OPENCV_LIB}
	opengl32.lib)


# add the project
add_library(CVBridgePlugin SHARED ${SOURCES})


# post event
add_custom_command(
TARGET CVBridgePlugin 
POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy  ${CMAKE_BINARY_DIR}/Plugin/Debug/CVBridgePlugin.dll ${CMAKE_SOURCE_DIR}/../CVBridgeUnity/Assets/cvBridge/Plugins/x64/cvBridge.dll
)


