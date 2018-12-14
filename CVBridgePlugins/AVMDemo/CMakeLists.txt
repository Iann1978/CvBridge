

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
include_directories(${CMAKE_SOURCE_DIR}/../3rdparty/opencv-3.4.4-vc14_vc15/build/include)

link_directories(${CMAKE_SOURCE_DIR}/../3rdparty/opencv-3.4.4-vc14_vc15/build/x64/vc15/lib)
link_directories(${CMAKE_BINARY_DIR}/Plugin/Debug)


# add libs
link_libraries(opencv_world344d.lib opengl32.lib CVBridgePlugin.lib)


# add the project
add_library(${PROJECT_NAME} SHARED ${SOURCES})


# post event
add_custom_command(
TARGET ${PROJECT_NAME} 
POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/Debug/${PROJECT_NAME}.dll ${CMAKE_SOURCE_DIR}/../CVBridgeUnity/Assets/cvBridge/Plugins/x64/${PROJECT_NAME}.dll
)

