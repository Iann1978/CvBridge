

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

source_group("Unity"            FILES ${SRC_UNITY})
source_group("GLEW"            FILES ${SRC_GLEW})
source_group("CVBridge"            FILES ${SRC_CVBRIDGE})

set(SOURCES
	${SRC_UNITY}
	${SRC_GLEW}
	${SRC_CVBRIDGE})

# include directores
include_directories(.)

# predefined macro
ADD_DEFINITIONS(-DGLEW_STATIC)

# add libs
LINK_LIBRARIES("E:/test/opencv/opencv/build/x64/vc15/lib/opencv_world341d.lib" "opengl32.lib")


# add the project
add_library(CVBridgePlugin SHARED ${SOURCES})


# post event
add_custom_command(
TARGET CVBridgePlugin 
POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy  ${CMAKE_BINARY_DIR}/Plugin/Debug/CVBridgePlugin.dll ${CMAKE_SOURCE_DIR}/../CVBridgeUnity/Assets/cvBridge/Plugins/x64/cvBridge.dll
)


