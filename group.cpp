//
// Created by Alex_Li on 2018/12/11.
//

#include "group.h"

void Group::setTexture(Texture *texture)
{
	if(!texture)
	{
		return;
	}

	Group::texture = texture;
}

void Group::setTexture(Texture &texture)
{
	Group::texture = &texture;
}

void Group::addSurface(const Surface &f)
{
	surface.push_back(f);
}

void Group::glDrawGroup()
{
	bool b = texture ? texture->hasTexture() : false;

	if(b)
	{
		texture->enableTexture();
	}
//	else
//	{
//		glDisable(GL_TEXTURE_2D);
//	}

	for(Surface &f : surface)
	{
		f.glDrawSurface(b);
//		f.glDrawSurface();
	}
}

void Group::translateGroup(double x, double y, double z)
{
	for(Surface &f : surface)
	{
		f.translateSurface(x, y, z);
	}
}

void Group::rotateGroup(Point center, Vector axis, double angle)
{
	for(Surface &f : surface)
	{
		f.rotateSurface(center, axis, angle);
	}
}
