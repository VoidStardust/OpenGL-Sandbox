//
// Created by Alex_Li on 2018/12/11.
//

#ifndef OPENGL_GROUP_H
#define OPENGL_GROUP_H

#include "surface.h"
#include "texture.h"

class Group
{
private:
	std::vector<Surface> surface;
	Texture *texture = nullptr;
//	bool hasTexture = false;

public:
	Group() = default;

public:
	void setTexture(Texture *texture);
	void setTexture(Texture &texture);
	void addSurface(const Surface &f);
	void glDrawGroup();
	void translateGroup(double x, double y, double z);
};


#endif //OPENGL_GROUP_H
