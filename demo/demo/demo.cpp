// demo.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <GL/glut.h>

#include <stdlib.h>

#include <math.h>

#include <stdio.h>

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // 清空颜色缓冲池
	glBegin(GL_TRIANGLES);
		glVertex3f(-0.5, -0.5, 0);
		glVertex3f(0.5, 0, 0);
		glVertex3f(0.0, 0.5, 0);
	glEnd();
	glFlush();
}
void changeSize(int w,int h)
{
	if (h == 0) 
		h = 1;
	float ratio = 1.0*w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45, ratio, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, -1.0, 0.0f, 1.0f, 0.0f);

}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(400, 400);
	glutCreateWindow("第一个OpenGL程序");
	glutDisplayFunc(&myDisplay);
	//changesize function
	glutReshapeFunc(changeSize);
	glutMainLoop();
	return 0;
}