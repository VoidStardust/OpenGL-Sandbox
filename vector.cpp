//
// Created by Alex_Li on 2018/12/1.
//

#include "vector.h"
#include "point.h"

Vector::Vector(Point A, Point B)
{
	x = B.getX() - A.getX();
	y = B.getY() - A.getY();
	z = B.getZ() - A.getZ();
}

Vector::Vector(double x, double y, double z) : x(x), y(y), z(z) {}

Vector Vector::vectorProduct(const Vector &left, const Vector &right)
{
	return {left.y * right.z - left.z * right.y,
		    left.z * right.x - left.x * right.z,
		    left.x * right.y - left.y * right.x};
}

double Vector::scalarProduct(const Vector &left, const Vector &right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

double Vector::abs(const Vector &vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

Vector Vector::unitVector(const Vector &vector)
{
	double ratio = abs(vector);
	return {vector.x / ratio, vector.y / ratio, vector.z / ratio};
}

Vector operator*(Vector left, double right)
{
	return {left.x * right, left.y * right, left.z * right};
}

Vector operator*(double left, Vector right)
{
	return {right.x * left, right.y * left, right.z * left};
}

Vector operator+(Vector left, Vector right)
{
	return {left.x + right.x, left.y + right.y, left.z + right.z};
}

Vector operator-(Vector left, Vector right)
{
	return {left.x - right.x, left.y - right.y, left.z - right.z};
}

double Vector::getX() const
{
	return x;
}

void Vector::setX(double x)
{
	Vector::x = x;
}

double Vector::getY() const
{
	return y;
}

void Vector::setY(double y)
{
	Vector::y = y;
}

double Vector::getZ() const
{
	return z;
}

void Vector::setZ(double z)
{
	Vector::z = z;
}

Vector Vector::rotate(Vector vector, Vector axis, double theta)
{
	axis = Vector::unitVector(axis);
	double s = sin(theta);
	double c = cos(theta);
	double x = axis.x;
	double y = axis.y;
	double z = axis.z;

	Vector r1(x * x * (1 - c) + c, x * y * (1 - c) - z * s, x * z * (1 - c) + y * s);
	Vector r2(x * y * (1 - c) + z * s, y * y * (1 - c) + c, y * z * (1 - c) - x * s);
	Vector r3(x * z * (1 - c) - y * s, y * z * (1 - c) + x * s, z * z * (1 - c) + c);

	return {scalarProduct(vector, r1), scalarProduct(vector, r2), scalarProduct(vector, r3)};
}
