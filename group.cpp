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
	hasTexture = true;
}

void Group::addSurface(const Surface &f)
{
	surface.push_back(f);
}

void Group::glDrawGroup()
{
	if(hasTexture)
		texture->enableTexture();

	for(Surface &f : surface)
	{
		f.glDrawSurface();
	}
}

void Group::translateGroup(double x, double y, double z)
{
	for(Surface &f : surface)
	{
		f.translateSurface(x, y, z);
	}
}

bool Group::haveTexture() const
{
	return hasTexture;
}
