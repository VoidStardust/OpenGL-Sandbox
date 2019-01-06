#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glaux.h>
#include "light.h"

Light::Light(GLenum light,LightType type,Mode mode)
{
	this->light = light;
	this->type = type;
	this->mode = mode;
	if (mode == DEFAULT) Light::setDefault();
}
void Light::setValue4(GLfloat* arr,GLfloat a,GLfloat b,GLfloat c,GLfloat d)
{
	arr[0] = a;
	arr[1] = b;
	arr[2] = c;
	arr[3] = d;
}
void Light::setMatSpecular(GLfloat x,GLfloat y,GLfloat z)
{
	Light::setValue4(matSpecular,x,y,z,1);
}
void Light::setMatShininess(GLfloat shininess)
{
	matShininess[0] = shininess;
}
void Light::setLightPosition(GLfloat x,GLfloat y,GLfloat z)
{
	if (this->type == DIRECTIONAL_LIGHT) Light::setValue4(lightPosition,x,y,z,0);
	else Light::setValue4(lightPosition,x,y,z,1);
}
void Light::setLightAmbient(GLfloat r,GLfloat g,GLfloat b)
{
	Light::setValue4(lightAmbient,r,g,b,1);
}
void Light::setLightDiffuse(GLfloat r,GLfloat g,GLfloat b)
{
	Light::setValue4(lightDiffuse,r,g,b,1);
}
void Light::setLightSpecular(GLfloat x,GLfloat y,GLfloat z)
{
	Light::setValue4(lightSpecular,x,y,z,1);
}
void Light::setSpotDirection(GLfloat x,GLfloat y,GLfloat z)
{
	if (this->type != SPOT_LIGHT) return;
	Light::setValue4(spotDirection,x,y,z,1);
}
void Light::setLightModelAmbient(GLfloat x,GLfloat y,GLfloat z)
{
	Light::setValue4(lightModelAmbient,x,y,z,1);
}
void Light::setAngle(GLfloat angle)
{
	if (this->type != SPOT_LIGHT) return;
	this->angle = angle;
}
void Light::init()
{
	/*
	 * Please set the properties of the light before calling init()
	 * If the properties of the light changed, init() is necessary.
	 */
    glEnable(GL_NEAREST);
    glEnable(GL_LINEAR);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,this->lightModelAmbient);
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT,GL_SPECULAR,this->matSpecular);
 	glMaterialfv(GL_FRONT,GL_SHININESS,this->matShininess);
	if (this->type == SPOT_LIGHT) glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->lightSpecular);
	if (this->type == SPOT_LIGHT) glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, this->lightDiffuse);
    if (this->type == SPOT_LIGHT) glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, this->lightAmbient);
	glLightfv(this->light,GL_AMBIENT,this->lightAmbient);
	if (this->type == SPOT_LIGHT) glLightf(this->light,GL_SPOT_CUTOFF,this->angle);
	glLightfv(this->light,GL_AMBIENT,this->lightAmbient);
	glLightfv(this->light,GL_DIFFUSE,this->lightDiffuse);
	glLightfv(this->light,GL_SPECULAR,this->lightSpecular);
	glLightfv(this->light,GL_POSITION,this->lightPosition);
	if (this->type == SPOT_LIGHT) glLightfv(this->light,GL_SPOT_DIRECTION,this->spotDirection);
	if (this->type == SPOT_LIGHT) glLightf(this->light,GL_SPOT_EXPONENT,2.0 );
	glEnable(GL_LIGHTING);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
}
void Light::enable()
{
	glEnable(this->light);
}
void Light::disable()
{
	/*
	 * Please disable the light before drawing objects.
 	 */
	glDisable(this->light);
}
void Light::setDefault()
{
	/*
	 * In DEFAULT mode, some properties of the light will be pre-set to default value
	 * Note: Overwrite default value is possible afterward.
	 */
	Light::setLightModelAmbient(0.6,0.6,0.6);
	Light::setMatSpecular(1,1,1);
	Light::setMatShininess(50);
}
