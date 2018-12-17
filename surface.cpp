//
// Created by Alex_Li on 2018/11/27.
//

#include "surface.h"

Surface::Surface(std::vector<Point> &point) : point(point) {}

Surface::Surface(std::vector<Point> &point, std::vector<Point> &texturePoint) :
		point(point), texturePoint(texturePoint) {}

void Surface::glDrawSurface(bool hasTexture)
{
	glBegin(GL_POLYGON);
	for(int i = 0; i < point.size(); ++i)
	{
		if(normal.getX() != 0 || normal.getY() != 0 || normal.getZ() != 0)
			glNormal3d(normal.getX(), normal.getY(), normal.getZ());

		if(hasTexture)
			glTexCoord3d(texturePoint[i].getX(),
			             texturePoint[i].getY(),
			             texturePoint[i].getZ());
		glVertex3d(point[i].getX(),
		           point[i].getY(),
		           point[i].getZ());
	}
	glEnd();
}

void Surface::setTexturePoint(std::vector<Point> &texturePoint)
{
	Surface::texturePoint = texturePoint;
}

void Surface::setSurface(std::vector<Point> &point)
{
	Surface::point = point;
}

void Surface::addPoint(Point &point)
{
	Surface::point.push_back(point);
}

void Surface::addTexturePoint(Point &texturePoint)
{
	Surface::texturePoint.push_back(texturePoint);
}

void Surface::setNormal(Vector &vector)
{
	Surface::normal = vector;
}

void Surface::translateSurface(double x, double y, double z)
{
	for(Point &p : point)
	{
		p.movePoint(x, y, z);
	}
}
