cmake_minimum_required(VERSION 3.12)
project(OpenGL-Sandbox)

set(CMAKE_CXX_STANDARD 11)
set(HEADER_FILE point.h surface.h model.h vector.h camera.h group.h texture.h material.h LoadPNG/lodepng.h LoadPNG/lodepng_util.h light.h)
set(SOURCE_FILE main.cpp point.cpp surface.cpp model.cpp vector.cpp camera.cpp group.cpp texture.cpp material.cpp LoadPNG/lodepng.cpp LoadPNG/lodepng_util.cpp loadtexture.cpp light.cpp)

add_executable(OpenGL-Sandbox ${SOURCE_FILE} ${HEADER_FILE})
target_link_libraries(OpenGL-Sandbox opengl32 glu32 freeglut)
