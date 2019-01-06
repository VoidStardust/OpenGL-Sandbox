#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/gl.h>
#include <GL/glaux.h>
#include <bits/stdc++.h>
 class Light
{
    public:
        enum LightType{SPOT_LIGHT,POINT_LIGHT,DIRECTIONAL_LIGHT};
		enum Mode{DEFAULT,DEFINATION};
		Light(GLenum light,LightType type,Mode mode);
		void setMatSpecular(GLfloat x,GLfloat y,GLfloat z);
		void setMatShininess(GLfloat shininess);
		void setLightPosition(GLfloat x,GLfloat y,GLfloat z);
		void setLightAmbient(GLfloat r,GLfloat g,GLfloat b);
		void setLightDiffuse(GLfloat r,GLfloat g,GLfloat b);
		void setLightSpecular(GLfloat x,GLfloat y,GLfloat z);
		void setSpotDirection(GLfloat x,GLfloat y,GLfloat z);
		void setLightModelAmbient(GLfloat x,GLfloat y,GLfloat z);
		void setAngle(GLfloat angle);
		void init();
		void enable();
		void disable();
	private:
		GLenum light;
		LightType type;
		Mode mode;
		void initSpotLight();
		void initPointLight();
		void initDirecitonalLight();
		GLfloat matSpecular[4];
		GLfloat matShininess[1];
		GLfloat lightPosition[4];
		GLfloat lightAmbient[4];
		GLfloat lightDiffuse[4];
		GLfloat lightSpecular[4];
		GLfloat spotDirection[4];
		GLfloat lightModelAmbient[4];
		GLfloat angle;
		void setDefault();
		void setValue4(GLfloat* arr,GLfloat a,GLfloat b,GLfloat c,GLfloat d);
};


#endif // LIGHT_H_INCLUDED
