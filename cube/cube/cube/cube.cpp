// cube.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <GL/glut.h>

#include <stdlib.h>

#include <math.h>

#include <stdio.h>

// 8 points of cube

static const float vertexList[][3] =
{
	-0.5f,-0.5f,-0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
};

//points sequences
static const int indexList[][3] =
{
	{ 0, 1 },
	{ 2, 3 },
	{ 4, 5 },
	{ 6, 7 },
	{ 0, 2 },
	{ 1, 3 },
	{ 4, 6 },
	{ 5, 7 },
	{ 0, 4 },
	{ 1, 5 },
	{ 7, 3 },
	{ 2, 6 }
};

//draw cube
void drawCube()
{
	int i, j;
	glBegin(GL_LINES);
	for ( i = 0; i < 12; i++)
	{
		for (j = 0; j < 2; j++)
		{
			glVertex3fv(vertexList[indexList[i][j]]);
		}
	}
	glEnd();

	glBegin(GL_QUADS);
	//正面，白色  
	glColor3f(1, 1, 1);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glEnd();

	//coordinates
	glColor3f(1.0f, 0.0f, 0.0f); //画红色的x轴
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	glColor3f(0.0, 1.0, 0.0); //画绿色的y轴
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0, 0.0, 1.0); //画蓝色的z轴
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();
	
}

static float rotate = -120;
static int times = 0;

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	times++;
	if (times > 1000)
	{
		times = 0;
	}
	if (times % 1 == 0)
	{
		rotate += 0.3;
	}
	glRotatef(rotate, 0, 1, 0);
	glRotatef(rotate, 1, 0, 0);
	glColor3f(0, 1, 1);

	drawCube();

	glPopMatrix();
	glutSwapBuffers();






}

int main(int argc ,char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);//
	glutInitWindowSize(500, 500);	//
	glutCreateWindow("THE CUBE");  //executing in order makes right display
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutMainLoop();
    return 0;
}

