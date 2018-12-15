//
// Created by Alex_Li on 2018/11/27.
//

#ifndef OPENGL_MODEL_H
#define OPENGL_MODEL_H

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include "point.h"
#include "vector.h"
#include "group.h"
#include "material.h"

class Model
{
private:
	std::vector<Point> point = {Point()};
	std::vector<Point> texturePoint = {Point()};
	std::vector<Vector> normal = {Vector()};
	std::map<std::string, Material> material;
	std::vector<Group> group;

private:
	Vector translate = {-1, 0, 0};
	double angleX = 0;
	double angleY = 0;
	double angleZ = 0;

private:
//	char buf[100] = "";
	void loadMTL(std::istream &is);
	void decode(std::string s, Surface &surface);
	std::vector<std::string> stringToken(std::string token, char match = ' ');
//	bool stringToken(std::string s, int &pos, std::string &token, char match);

public:
	Model() = default;
	explicit Model(std::istream &is);

public:
	void glDrawModel();
	void getModel(std::istream &is);
	void translateModel(double x, double y, double z);
	void rotateModel(double angleX, double angleY, double angleZ);
};


#endif //OPENGL_MODEL_H
