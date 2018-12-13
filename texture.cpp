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

//AUX_RGBImageRec *Texture::LoadBMP(char *Filename)
//{
//	FILE *File = nullptr;
//
//	if(!Filename)
//	{
//		return nullptr;
//	}
//
//	File = fopen(Filename, "r");
//
//	if(File)
//	{
//		fclose(File);
//		return auxDIBImageLoad(Filename);
//	}
//
//	return nullptr;
//}

bool Texture::LoadGLTextures()
{
//	bool Status = false;
//
//	AUX_RGBImageRec *TextureImage[1];
//	memset(TextureImage, 0, sizeof(void *) * 1);
//	TextureImage[0] = LoadBMP(textureFile);
//
//	if(TextureImage[0])
//	{
//		Status = true;
//
//		glGenTextures(1, &textureID);
//
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY,
//		             0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	}
//
//	if(TextureImage[0])
//	{
//		if(TextureImage[0]->data)
//		{
//			free(TextureImage[0]->data);
//		}
//
//		free(TextureImage[0]);
//	}
//
//	return Status;

	const int BMP_Header_Length = 54;
	GLint width, height, total_bytes;
	GLubyte *pixels = nullptr;
	FILE *pFile = fopen(textureFile, "rb");

	if(!pFile)
	{
		std::cout << textureFile << ": File does not exist." << std::endl;
		return false;
	}

	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);
	GLint line_bytes = width * 3;
	while(line_bytes % 4 != 0)
		++line_bytes;
	total_bytes = line_bytes * height;
	pixels = (GLubyte *) malloc(static_cast<size_t>(total_bytes));
	fread(pixels, static_cast<size_t>(total_bytes), 1, pFile);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	free(pixels);
	fclose(pFile);

	return true;
}

bool Texture::initTexture()
{
	if (!LoadGLTextures())
	{
		return false;
	}

	glEnable(GL_TEXTURE_2D);
	return true;
}

void Texture::enableTexture()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::setTexture(std::string File)
{
	textureFile = (char*) File.c_str();
	initTexture();
}
