//
// Created by Alex_Li on 2018/11/27.
//

#ifndef OPENGL_SURFACE_H
#define OPENGL_SURFACE_H

#include <iostream>
#include <vector>
#include <GL/glut.h>
#include "point.h"
#include "vector.h"
#include "texture.h"

class Surface
{
private:
	std::vector<Point> point;
	std::vector<Point> texturePoint;
	Vector normal;
//	Texture *texture = nullptr;
	bool hasTexture = false;

public:
	Surface() = default;
	explicit Surface(std::vector<Point> &point);
	Surface(std::vector<Point> &point, std::vector<Point> &texturePoint);

public:
	void glDrawSurface();
	void setSurface(std::vector<Point> &point);
//	void setTexture(Texture *texture);
	void setTexturePoint(std::vector<Point> &texturePoint);
	void addPoint(Point &point);
	void addTexturePoint(Point &texturePoint);
	void setNormal(Vector &vector);
	void setHasTexture(bool hasTexture);
	void translateSurface(double x, double y, double z);
};


#endif //OPENGL_SURFACE_H
