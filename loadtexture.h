//
// Created by Alex_Li on 2019/1/5.
//

#ifndef OPENGL_SANDBOX_LOADTEXTURE_H
#define OPENGL_SANDBOX_LOADTEXTURE_H


#include <iostream>
#include <cmath>
#include <GL/glu.h>
#include <olectl.h>
#include "LoadPNG/lodepng.h"

class LoadTexture
{
public:
	static GLuint LoadIMG(char *szPathName);
	static GLuint LoadPNG(char *fileName);
};


#endif //OPENGL_SANDBOX_LOADTEXTURE_H
