//
// Created by Alex_Li on 2018/12/11.
//

#include "texture.h"

Texture::Texture(char *File) : textureFile(File)
{
	initTexture();
}

void Texture::setTexture(char *File)
{
	textureFile = File;
	initTexture();
}

bool Texture::LoadGLTextures()
{
	std::string s = textureFile;
	if(s.find(".png") != std::string::npos)
	{
		textureID = LoadTexture::LoadPNG(textureFile);
	}
	else
	{
		textureID = LoadTexture::LoadIMG(textureFile);
	}
	return hasTexture();
}

bool Texture::hasTexture()
{
	return textureID != 0;
}

bool Texture::initTexture()
{
	if(!LoadGLTextures())
//	if(!LoadGLTextures(textureFile))
	{
		return false;
	}

	glEnable(GL_TEXTURE_2D);
	return true;
}

void Texture::enableTexture()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::setTexture(std::string File)
{
	textureFile = (char*) File.c_str();
	initTexture();
}
