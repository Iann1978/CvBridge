

# source files

set(PROJECT_NAME AVMDemo)

file(GLOB_RECURSE SRC_DEMOS
    "./*.cpp"
    "./*.h"
)


source_group("Demos"            FILES ${SRC_DEMOS})

set(SOURCES
	${SRC_DEMOS})

# include directores
include_directories(.)
include_directories(${CMAKE_SOURCE_DIR}/Plugin)
include_directories(${OPENCV_INCLUDE})

link_directories(${OPENCV_FOLDER}/build/lib/Debug)
link_directories(${CMAKE_BINARY_DIR}/Plugin/Debug)


# add libs
link_libraries(${OPENCV_LIB} opengl32.lib CVBridgePlugin.lib)


# add the project
add_library(${PROJECT_NAME} SHARED ${SOURCES})


# post event
add_custom_command(
TARGET ${PROJECT_NAME} 
POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/Debug/${PROJECT_NAME}.dll ${CMAKE_SOURCE_DIR}/../CVBridgeUnity/Assets/cvBridge/Plugins/x64/${PROJECT_NAME}.dll
)

