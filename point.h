//
// Created by Alex_Li on 2018/11/27.
//

#ifndef OPENGL_POINT_H
#define OPENGL_POINT_H

class Vector;

class Point
{
private:
	double x = 0;
	double y = 0;
	double z = 0;

public:
	double getX() const;
	void setX(double x);
	double getY() const;
	void setY(double y);
	double getZ() const;
	void setZ(double z);

public:
	Point() = default;
	Point(double x, double y, double z);
	void setPoint(double x, double y, double z);
	void movePoint(double x, double y, double z);
	void movePoint(const Vector &vector);
	void rotatePoint(Point center, Vector axis, double angle);
};


#endif //OPENGL_POINT_H
