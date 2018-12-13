cmake_minimum_required(VERSION 3.12)
project(OpenGL)

set(CMAKE_CXX_STANDARD 11)

add_executable(OpenGL main.cpp point.cpp point.h surface.cpp surface.h model.cpp model.h vector.cpp vector.h camera.cpp camera.h group.cpp group.h texture.cpp texture.h material.cpp material.h)
target_link_libraries(OpenGL glew32 opengl32 glu32 freeglut)
