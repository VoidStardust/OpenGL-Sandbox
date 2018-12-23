#include <cmath>

#include <cmath>

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
		return LoadPNG(textureFile);
	}
	else
	{
		return LoadIMG(textureFile);
	}
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

bool Texture::LoadIMG(char *szPathName)
{
	HDC hdcTemp;
	HBITMAP hbmpTemp;
	IPicture *pPicture;
	OLECHAR wszPath[MAX_PATH + 1];
	char szPath[MAX_PATH + 1];
	long lWidth;
	long lHeight;
	long lWidthPixels;
	long lHeightPixels;
	GLint glMaxTexDim;

	if(strstr(szPathName, "http://"))
	{
		strcpy(szPath, szPathName);
	}
	else
	{
		GetCurrentDirectory(MAX_PATH, szPath);
		strcat(szPath, "\\");
		strcat(szPath, szPathName);
	}

	MultiByteToWideChar(CP_ACP, 0, szPath, -1, wszPath, MAX_PATH);
	HRESULT hr = OleLoadPicturePath(wszPath, nullptr, 0, 0, IID_IPicture, (void **) &pPicture);

	if(FAILED(hr))
	{
//		MessageBox(HWND_DESKTOP, "图片导入失败!\n(TextureLoad Failed!)", "Error", MB_OK | MB_ICONEXCLAMATION);
		std::cout << szPathName << ": File does not exist." << std::endl;
		return FALSE;
	}

	hdcTemp = CreateCompatibleDC(GetDC(nullptr));
	if(!hdcTemp)
	{
		pPicture->Release();
//		MessageBox(HWND_DESKTOP, "图片导入失败!\n(TextureLoad Failed!)", "Error", MB_OK | MB_ICONEXCLAMATION);
		std::cout << szPathName << ": File does not exist." << std::endl;
		return FALSE;
	}

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &glMaxTexDim);

	pPicture->get_Width(&lWidth);
	lWidthPixels = MulDiv(lWidth, GetDeviceCaps(hdcTemp, LOGPIXELSX), 2540);
	pPicture->get_Height(&lHeight);
	lHeightPixels = MulDiv(lHeight, GetDeviceCaps(hdcTemp, LOGPIXELSY), 2540);

	if(lWidthPixels <= glMaxTexDim)
		lWidthPixels = 1 << (int) floor((std::log((double) lWidthPixels) / std::log(2.0f)) + 0.5f);
	else
		lWidthPixels = glMaxTexDim;

	if(lHeightPixels <= glMaxTexDim)
		lHeightPixels = 1 << (int) floor((std::log((double) lHeightPixels) / std::log(2.0f)) + 0.5f);
	else
		lHeightPixels = glMaxTexDim;

	BITMAPINFO bi = {0};
	DWORD *pBits = nullptr;

	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biWidth = lWidthPixels;
	bi.bmiHeader.biHeight = lHeightPixels;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biPlanes = 1;

	hbmpTemp = CreateDIBSection(hdcTemp, &bi, DIB_RGB_COLORS, (void **) &pBits, nullptr, 0);

	if(!hbmpTemp)
	{
		DeleteDC(hdcTemp);
		pPicture->Release();
//		MessageBox(HWND_DESKTOP, "图片导入失败!\n(TextureLoad Failed!)", "Error", MB_OK | MB_ICONEXCLAMATION);
		std::cout << szPathName << ": File does not exist." << std::endl;
		return FALSE;
	}

	SelectObject(hdcTemp, hbmpTemp);

	pPicture->Render(hdcTemp, 0, 0, lWidthPixels, lHeightPixels, 0, lHeight, lWidth, -lHeight, nullptr);

	for(long i = 0; i < lWidthPixels * lHeightPixels; i++)
	{
		BYTE *pPixel = (BYTE *) (&pBits[i]);
		BYTE temp = pPixel[0];
		pPixel[0] = pPixel[2];
		pPixel[2] = temp;
		pPixel[3] = 255;
	}

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, lWidthPixels, lHeightPixels, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBits);

	DeleteObject(hbmpTemp);
	DeleteDC(hdcTemp);

	pPicture->Release();

	return TRUE;
}

bool Texture::LoadPNG(char *fileName)
{
	unsigned error;
	unsigned width, height;
	unsigned char *pImg;
	error = lodepng_decode32_file(&pImg, &width, &height, fileName);
	if(error)
	{
		printf("error %u: %s\n", error, lodepng_error_text(error));
		return false;
	}

	unsigned i;
	unsigned char *pLine;

	pLine = (unsigned char *) malloc(4 * width);
	if(pLine == nullptr)
	{
		printf("No memory left!");
		return false;
	}
	for(i = 0; i < height / 2; i++)
	{
		memcpy(pLine, &pImg[i * 4 * width], 4 * width);
		memcpy(&pImg[i * 4 * width], &pImg[(height - 1 - i) * 4 * width], 4 * width);
		memcpy(&pImg[(height - 1 - i) * 4 * width], pLine, 4 * width);
	}
	free(pLine);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pImg);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glEnable(GL_DEPTH_TEST);
	free(pImg);

	return true;
}
