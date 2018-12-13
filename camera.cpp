//
// Created by Alex_Li on 18-12-10.
//

#include "camera.h"

void Camera::setUpLock(bool upLock)
{
	Camera::upLock = upLock;
}

void Camera::setEye(const Point &eye)
{
	Camera::eye = eye;
}

void Camera::setCenter(const Point &center)
{
	Camera::center = center;
}

void Camera::setUp(const Point &up)
{
	Camera::up = up;
}

void Camera::setCamera()
{
	glLoadIdentity();
	gluLookAt(eye.getX(), eye.getY(), eye.getZ(),
	          center.getX(), center.getY(), center.getZ(),
	          up.getX(), up.getY(), up.getZ());
}

void Camera::scale(double ratio)
{
	Vector move(eye, center);
	move = move * ratio;
	eye.movePoint(move);
}

void Camera::translate(double x_dif, double y_dif, double z_dif)
{
	Vector perspective(eye, center);
	Vector upVector(Point(0, 0, 0), up);

	double a = Vector::scalarProduct(perspective, upVector) / Vector::scalarProduct(upVector, upVector);
	Vector moveX = Vector::unitVector(Vector::vectorProduct(perspective, upVector));
	Vector moveY = Vector::unitVector(perspective - (a * upVector));
	Vector moveZ = Vector::unitVector(upVector);

	Vector move = moveX * x_dif + moveY * y_dif + moveZ * z_dif;

	eye.movePoint(move);
	center.movePoint(move);
}

void Camera::rotateAroundCenter(double x_dif, double y_dif)
{
	Vector perspective(eye, center);
	Vector upVector(Point(0, 0, 0), up);

	Vector axis = Vector::unitVector(Vector::vectorProduct(perspective, upVector));

	Vector d = Vector::rotate(perspective, axis, y_dif);
	Vector e = Vector::rotate(upVector, axis, y_dif);

	Vector moveY = perspective - d;


	Vector f = Vector::unitVector(perspective);
	Vector g = f * Vector::scalarProduct(upVector, f);
	Vector h = Vector::unitVector(upVector - g);

	Vector i = Vector::rotate(perspective, h, x_dif);
	Vector j = Vector::rotate(upVector, h, x_dif);

	Vector moveX = perspective - i;

	Vector move = moveX + moveY;

	eye.movePoint(move);

	if(!upLock)
	{
		Vector moveUpX = j - upVector;
		Vector moveUpY = e - upVector;
		Vector moveUp = moveUpX + moveUpY;
		up.movePoint(moveUp);
	}
}

void Camera::rotateAroundEye(double x_dif, double y_dif)
{
	Vector perspective(eye, center);
	Vector upVector(Point(0, 0, 0), up);

	Vector yAxis = Vector::unitVector(Vector::vectorProduct(perspective, upVector));
	Vector moveY = Vector::rotate(perspective, yAxis, y_dif) - perspective;

	Vector xAxis;
	if(!upLock)
	{
		Vector f = Vector::unitVector(perspective);
		Vector g = f * Vector::scalarProduct(upVector, f);
		xAxis = Vector::unitVector(upVector - g);
	}
	else
	{
		xAxis = Vector::unitVector(upVector);
	}

	Vector moveX = Vector::rotate(perspective, xAxis, x_dif) - perspective;

	Vector move = moveX + moveY;
	center.movePoint(move);

	if(!upLock)
	{
		Vector moveUpX = upVector - Vector::rotate(upVector, xAxis, x_dif);
		Vector moveUpY = upVector - Vector::rotate(upVector, yAxis, y_dif);
		Vector moveUp = moveUpX + moveUpY;
		up.movePoint(moveUp);
	}
}
