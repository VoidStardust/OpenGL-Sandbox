//
// Created by Alex_Li on 2018/12/11.
//

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include <cstdio>
#include <iostream>
#include <cmath>
#include <GL/glu.h>
#include "loadtexture.h"

class Texture
{
private:
	char *textureFile = nullptr;
	GLuint textureID = 0;

public:
	Texture() = default;
	explicit Texture(char *File);

public:
	void setTexture(char *File);
	void setTexture(std::string File);
	bool LoadGLTextures();
	bool initTexture();
	void enableTexture();
	bool hasTexture();
};


#endif //OPENGL_TEXTURE_H
