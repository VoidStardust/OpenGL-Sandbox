#include <utility>

//
// Created by Alex_Li on 2018/12/13.
//

#include "material.h"

Texture *Material::getTexture()
{
	return &texture;
}

void Material::setTexture(char *File)
{
	texture.setTexture(File);
}

void Material::setTexture(std::string File)
{
	texture.setTexture(std::move(File));
}

void Material::setNs(double ns)
{
	Material::ns = ns;
}

void Material::setKa(std::vector<double> &ka)
{
	Material::ka = ka;
}

void Material::setKd(std::vector<double> &kd)
{
	Material::kd = kd;
}

void Material::setKs(std::vector<double> &ks)
{
	Material::ks = ks;
}

void Material::setKe(std::vector<double> &ke)
{
	Material::ke = ke;
}

void Material::setNi(double ni)
{
	Material::ni = ni;
}

void Material::setD(double d)
{
	Material::d = d;
}
