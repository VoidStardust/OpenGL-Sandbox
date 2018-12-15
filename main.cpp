#include <iostream>
#include <fstream>
#include <cmath>
#include <GL/glut.h>
#include "model.h"
#include "camera.h"
#include "vector.h"

using namespace std;

const int WIDTH = 1000;
const int HEIGHT = 500;

Model model;
Camera camera;

int x_pos = 0;
int y_pos = 0;
int push_button = 0;

const double ratio = 0.005;

void initLight()
{
	GLfloat LightAmbient1[] = {0, 0, 1, 1};
	GLfloat LightDiffuse1[] = {0, 0, 1, 1};
	GLfloat LightPosition1[] = {0, 0, 0, 1};
	GLfloat Mat_specular1[] = {1, 1, 1, 1};
	GLfloat Mat_shininess1[] = {50};

	GLfloat LightAmbient2[] = {0, 1, 0, 1};
	GLfloat LightDiffuse2[] = {0, 1, 0, 1};
	GLfloat LightPosition2[] = {1, 1, 1, 1};
	GLfloat Mat_specular2[] = {0, 0, 1, 1};
	GLfloat Mat_shininess2[] = {50};

	GLfloat LightAmbient3[] = {1, 0, 0, 1};
	GLfloat LightDiffuse3[] = {1, 0, 0, 1};
	GLfloat LightPosition3[] = {1, 0, 0, 1};
	GLfloat Mat_specular3[] = {-1, 1, 1, 1};
	GLfloat Mat_shininess3[] = {50};

	glMaterialfv(GL_FRONT, GL_SPECULAR, Mat_specular1);
	glMaterialfv(GL_FRONT, GL_SHININESS, Mat_shininess1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse1);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition1);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Mat_specular2);
	glMaterialfv(GL_FRONT, GL_SHININESS, Mat_shininess2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse2);
	glLightfv(GL_LIGHT2, GL_POSITION, LightPosition2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Mat_specular3);
	glMaterialfv(GL_FRONT, GL_SHININESS, Mat_shininess3);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient3);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse3);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition3);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
}

int initGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	return true;
}

void OnDraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera.setCamera();

	model.glDrawModel();

	glFlush();
}

void reshape(int width, int height)
{
	if(height == 0)
		height = 1;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, (double)width / height, 0.1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OnMouse(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN)
	{
		x_pos = x;
		y_pos = y;
		if(button == GLUT_LEFT_BUTTON)
			push_button = 1;
		else if(button == GLUT_RIGHT_BUTTON)
			push_button = 2;
		else if(button == 3)
		{
			camera.scale(ratio);
		}
		else if(button == 4)
		{
			camera.scale(-ratio);
		}
	}
}

void OnMove(int x, int y)
{
	double x_dif = ratio * (x_pos - x);
	double y_dif = ratio * (y_pos - y);

	if(push_button == 1)
	{
		model.translateModel(0, -x_dif, y_dif);

		x_pos = x;
		y_pos = y;
	}
	else if(push_button == 2)
	{
		camera.rotateAroundCenter(x_dif, y_dif);
//		camera.rotateAroundEye(-x_dif, -y_dif);

		x_pos = x;
		y_pos = y;
	}
}

int main(int argc, char *argv[])
{
//	fstream input1("mech_f_432.obj");
//	model.getModel(input1);
//	input1.close();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(-1, -1);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("OpenGL Windows Test");

	initGL();
	initLight();

//	fstream input1("test.obj");
	fstream input1("mech_f_432.obj");
	model.getModel(input1);
	input1.close();

	glutDisplayFunc(OnDraw);
	glutIdleFunc(OnDraw);
	glutReshapeFunc(reshape);
	glutMouseFunc(OnMouse);
	glutMotionFunc(OnMove);

	glutMainLoop();
	return 0;
}
