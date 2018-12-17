//
// Created by Alex_Li on 18-12-10.
//

#ifndef OPENGL_CAMERA_H
#define OPENGL_CAMERA_H

#include <GL/glut.h>
#include <iostream>
#include "point.h"
#include "vector.h"

class Camera
{
private:
	Point eye = {3, 0, 1};
	Point center = {0, 0, 0};
	Point up = {0, 0, 1};
	bool upLock = false;

public:
	Camera() = default;
	explicit Camera(bool upLock);

public:
	void setUpLock(bool upLock);
	void setEye(const Point &eye);
	void setCenter(const Point &center);
	void setUp(const Point &up);

public:
	void setCamera();
	void scale(double ratio);
	void translate(double x_dif, double y_dif, double z_dif);
	void rotateAroundCenter(double x_dif, double y_dif);
	void rotateAroundEye(double x_dif, double y_dif);
};


#endif //OPENGL_CAMERA_H
