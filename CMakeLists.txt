cmake_minimum_required(VERSION 3.12)
project(OpenGL-Sandbox)

set(CMAKE_CXX_STANDARD 11)

add_executable(OpenGL-Sandbox main.cpp point.cpp point.h surface.cpp surface.h model.cpp model.h vector.cpp vector.h camera.cpp camera.h group.cpp group.h texture.cpp texture.h material.cpp material.h LoadPNG/lodepng.cpp LoadPNG/lodepng.h LoadPNG/lodepng_util.cpp LoadPNG/lodepng_util.h)
target_link_libraries(OpenGL-Sandbox glew32 opengl32 glu32 freeglut)
