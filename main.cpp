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

Model model(0.001);
Model skybox(1);
Model plane(0.001);
Camera camera(true);

int x_pos = 0;
int y_pos = 0;
int push_button = 0;

const double ratio = 0.005;

void initLight()
{
	GLfloat LightAmbient1[] = {1, 1, 1, 1};
	GLfloat LightDiffuse1[] = {1, 1, 1, 1};
	GLfloat LightPosition1[] = {0, 0, 0, 1};
	GLfloat Mat_specular1[] = {1, 1, 1, 1};
	GLfloat Mat_shininess1[] = {50};

	GLfloat LightAmbient2[] = {1, 1, 1, 1};
	GLfloat LightDiffuse2[] = {1, 1, 1, 1};
	GLfloat LightPosition2[] = {1, 1, 1, 1};
	GLfloat Mat_specular2[] = {0, 0, 1, 1};
	GLfloat Mat_shininess2[] = {50};

	GLfloat LightAmbient3[] = {1, 1, 1, 1};
	GLfloat LightDiffuse3[] = {1, 1, 1, 1};
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
	glClearColor(0.2f, 0.2f, 0.2f, 0.5f);
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

	skybox.glDrawModel();
	plane.glDrawModel();
	model.glDrawModel();

	glFlush();

	plane.rotateModel(Point(0, 0, 0), Vector(0, 0, 1), 0.01);
}

void OnDraw1()
{
	static float rtri = 0, rquad = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glPushMatrix();									// Reset The Current Modelview Matrix
	glTranslatef(-1.5f,0.0f,-6.0f);						// Move Left 1.5 Units And Into The Screen 6.0
	glRotatef(rtri,0.0f,1.0f,0.0f);						// Rotate The Triangle On The Y axis ( NEW )
	glBegin(GL_TRIANGLES);								// Start Drawing A Triangle
	glColor3f(1.0f,0.0f,0.0f);						// Red
	glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Front)
	glColor3f(0.0f,1.0f,0.0f);						// Green
	glVertex3f(-1.0f,-1.0f, 1.0f);					// Left Of Triangle (Front)
	glColor3f(0.0f,0.0f,1.0f);						// Blue
	glVertex3f( 1.0f,-1.0f, 1.0f);					// Right Of Triangle (Front)
	glColor3f(1.0f,0.0f,0.0f);						// Red
	glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Right)
	glColor3f(0.0f,0.0f,1.0f);						// Blue
	glVertex3f( 1.0f,-1.0f, 1.0f);					// Left Of Triangle (Right)
	glColor3f(0.0f,1.0f,0.0f);						// Green
	glVertex3f( 1.0f,-1.0f, -1.0f);					// Right Of Triangle (Right)
	glColor3f(1.0f,0.0f,0.0f);						// Red
	glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Back)
	glColor3f(0.0f,1.0f,0.0f);						// Green
	glVertex3f( 1.0f,-1.0f, -1.0f);					// Left Of Triangle (Back)
	glColor3f(0.0f,0.0f,1.0f);						// Blue
	glVertex3f(-1.0f,-1.0f, -1.0f);					// Right Of Triangle (Back)
	glColor3f(1.0f,0.0f,0.0f);						// Red
	glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Left)
	glColor3f(0.0f,0.0f,1.0f);						// Blue
	glVertex3f(-1.0f,-1.0f,-1.0f);					// Left Of Triangle (Left)
	glColor3f(0.0f,1.0f,0.0f);						// Green
	glVertex3f(-1.0f,-1.0f, 1.0f);					// Right Of Triangle (Left)
	glEnd();											// Done Drawing The Pyramid
	glPopMatrix();

	glPushMatrix();									// Reset The Current Modelview Matrix
	glTranslatef(1.5f,0.0f,-7.0f);						// Move Right 1.5 Units And Into The Screen 7.0
	glRotatef(rquad,1.0f,1.0f,1.0f);					// Rotate The Quad On The X axis ( NEW )
	glBegin(GL_QUADS);									// Draw A Quad
	glColor3f(0.0f,1.0f,0.0f);						// Set The Color To Green
	glVertex3f( 1.0f, 1.0f,-1.0f);					// Top Right Of The Quad (Top)
	glVertex3f(-1.0f, 1.0f,-1.0f);					// Top Left Of The Quad (Top)
	glVertex3f(-1.0f, 1.0f, 1.0f);					// Bottom Left Of The Quad (Top)
	glVertex3f( 1.0f, 1.0f, 1.0f);					// Bottom Right Of The Quad (Top)
	glColor3f(1.0f,0.5f,0.0f);						// Set The Color To Orange
	glVertex3f( 1.0f,-1.0f, 1.0f);					// Top Right Of The Quad (Bottom)
	glVertex3f(-1.0f,-1.0f, 1.0f);					// Top Left Of The Quad (Bottom)
	glVertex3f(-1.0f,-1.0f,-1.0f);					// Bottom Left Of The Quad (Bottom)
	glVertex3f( 1.0f,-1.0f,-1.0f);					// Bottom Right Of The Quad (Bottom)
	glColor3f(1.0f,0.0f,0.0f);						// Set The Color To Red
	glVertex3f( 1.0f, 1.0f, 1.0f);					// Top Right Of The Quad (Front)
	glVertex3f(-1.0f, 1.0f, 1.0f);					// Top Left Of The Quad (Front)
	glVertex3f(-1.0f,-1.0f, 1.0f);					// Bottom Left Of The Quad (Front)
	glVertex3f( 1.0f,-1.0f, 1.0f);					// Bottom Right Of The Quad (Front)
	glColor3f(1.0f,1.0f,0.0f);						// Set The Color To Yellow
	glVertex3f( 1.0f,-1.0f,-1.0f);					// Top Right Of The Quad (Back)
	glVertex3f(-1.0f,-1.0f,-1.0f);					// Top Left Of The Quad (Back)
	glVertex3f(-1.0f, 1.0f,-1.0f);					// Bottom Left Of The Quad (Back)
	glVertex3f( 1.0f, 1.0f,-1.0f);					// Bottom Right Of The Quad (Back)
	glColor3f(0.0f,0.0f,1.0f);						// Set The Color To Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);					// Top Right Of The Quad (Left)
	glVertex3f(-1.0f, 1.0f,-1.0f);					// Top Left Of The Quad (Left)
	glVertex3f(-1.0f,-1.0f,-1.0f);					// Bottom Left Of The Quad (Left)
	glVertex3f(-1.0f,-1.0f, 1.0f);					// Bottom Right Of The Quad (Left)
	glColor3f(1.0f,0.0f,1.0f);						// Set The Color To Violet
	glVertex3f( 1.0f, 1.0f,-1.0f);					// Top Right Of The Quad (Right)
	glVertex3f( 1.0f, 1.0f, 1.0f);					// Top Left Of The Quad (Right)
	glVertex3f( 1.0f,-1.0f, 1.0f);					// Bottom Left Of The Quad (Right)
	glVertex3f( 1.0f,-1.0f,-1.0f);					// Bottom Right Of The Quad (Right)
	glEnd();											// Done Drawing The Quad
	glPopMatrix();

	glFlush();

	camera.setCamera();

	rtri+=0.01f;											// Increase The Rotation Variable For The Triangle ( NEW )
	rquad-=0.01f;										// Decrease The Rotation Variable For The Quad ( NEW )
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
			push_button = 2;
		else if(button == GLUT_RIGHT_BUTTON)
			push_button = 1;
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

void OnKeyboard(unsigned char key, int x, int y)
{
	if(key == 'w')
		camera.translate(0, ratio * 10, 0);
	if(key == 'a')
		camera.translate(-ratio * 10, 0, 0);
	if(key == 's')
		camera.translate(0, -ratio * 10, 0);
	if(key == 'd')
		camera.translate(ratio * 10, 0, 0);
	if(key == 'q')
		plane.rotateModel(Point(0, 10, 0), Vector(0, 0, 1), 0.01);
	if(key == 'e')
		plane.rotateModel(Point(0, 10, 0), Vector(0, 0, 1), -0.01);
}

void OnMove(int x, int y)
{
	double x_dif = ratio * (x_pos - x);
	double y_dif = ratio * (y_pos - y);

	if(push_button == 1)
	{
//		model.translateModel(0, -x_dif, y_dif);
		camera.translate(x_dif, 0, -y_dif);

		x_pos = x;
		y_pos = y;
	}
	else if(push_button == 2)
	{
//		camera.rotateAroundCenter(x_dif, y_dif);
		camera.rotateAroundEye(-x_dif, -y_dif);

		x_pos = x;
		y_pos = y;
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(-1, -1);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("OpenGL Windows Test");

	initGL();
	initLight();

	fstream input1("Castelia_City/Castelia_City.obj");
//	fstream input1("twins/Twin_Islands.obj");
//	fstream input1("mech_f_432.obj");
//	fstream input1("airplane/11803_Airplane_v1_l1.obj");
//	fstream input1("boat/12219_boat_v2_L2.obj");
//	fstream input1("test/test.obj");
	model.getModel(input1);
	input1.close();

	model.rotateModel(Point(0, 0, 0), Vector(1, 0, 0), 1.5707963267948966192313216916398);

	fstream input2("airplane/11803_Airplane_v1_l1.obj");
	plane.getModel(input2);
	input2.close();

	plane.rotateModel(Point(0, 0, 0), Vector(1, 0, 0), 1.5707963267948966192313216916398);
	plane.translateModel(0, -30, 20);

	fstream input3("test/test.obj");
	skybox.getModel(input3);
	input3.close();

	glutDisplayFunc(OnDraw);
	glutIdleFunc(OnDraw);
	glutReshapeFunc(reshape);
	glutMouseFunc(OnMouse);
	glutKeyboardFunc(OnKeyboard);
	glutMotionFunc(OnMove);

	glutMainLoop();
	return 0;
}
