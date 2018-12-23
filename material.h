//
// Created by Alex_Li on 2018/12/13.
//

#ifndef OPENGL_MATERIAL_H
#define OPENGL_MATERIAL_H

#include <vector>
#include "texture.h"
#include "point.h"
#include "vector.h"

class Material
{
private:
	Texture texture;
	double ns = 0;
	std::vector<double> ka;
	std::vector<double> kd;
	std::vector<double> ks;
	std::vector<double> ke;
	double ni = 0;
	double d = 0;

public:
	Material() = default;

public:
	Texture *getTexture();
	void setTexture(char *File);
	void setTexture(std::string File);
	void setNs(double ns);
	void setKa(std::vector<double> &ka);
	void setKd(std::vector<double> &kd);
	void setKs(std::vector<double> &ks);
	void setKe(std::vector<double> &ke);
	void setNi(double ni);
	void setD(double d);
};


#endif //OPENGL_MATERIAL_H
