//
// Created by Alex_Li on 2018/11/27.
//

#include "point.h"
#include "vector.h"

Point::Point(double x, double y, double z) : x(x), y(y), z(z) {}

double Point::getX() const
{
	return x;
}

void Point::setX(double x)
{
	Point::x = x;
}

double Point::getY() const
{
	return y;
}

void Point::setY(double y)
{
	Point::y = y;
}

double Point::getZ() const
{
	return z;
}

void Point::setZ(double z)
{
	Point::z = z;
}

void Point::setPoint(double x, double y, double z)
{
	Point::x = x;
	Point::y = y;
	Point::z = z;
}

void Point::movePoint(double x, double y, double z)
{
	Point::x += x;
	Point::y += y;
	Point::z += z;
}

void Point::movePoint(const Vector &vector)
{
	movePoint(vector.x, vector.y, vector.z);
}
