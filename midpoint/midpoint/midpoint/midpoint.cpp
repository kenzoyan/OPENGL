// midpoint.cpp: 定义控制台应用程序的入口点。
//

// demo.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <GL/glut.h>

#include <stdlib.h>

#include <math.h>

#include <stdio.h>

int xs, ys, xe, ye;

int R;


void midPoint(int x1,int y1,int x2,int y2)
{	
	int x, y;
	float dx, dy;
	float k, e;
	e = -0.5, x = x1, y = y1;

	dx = x2 - x1, dy = y2 - y1, k = dy / dx;
	if (k >= 0)					//when k >0
	{
		if (k <= 1.0)
		{
			//printf("x=%f,y=%f,k=%f",dx,dy, k);
			for (int i = 0; i <= dx; i++)
			{
				glVertex2f(x, y);
				//printf("%d,%d\n", x, y);
				x++, e = e + k;
				if (e >= 0)
				{
					y++;
					e--;
				}
			}
		}
		else
		{
			k = 1 / k;// k>1  reverse x,y
			printf("x=%f,y=%f,k=%f\n", dx, dy, k);
			for (int i = 0; i <= dy; i++)
			{
				glVertex2f(x, y);
				printf("%d,%d\n", x, y);
				y++, e = e + k;
				if (e >= 0)
				{
					x++;
					e--;
				}
			}
		}
	}
	else
	{							// when k <0 
		k = -k;
		dy = -dy;
		if (k <= 1.0)
		{
			//printf("x=%f,y=%f,k=%f",dx,dy, k);
			for (int i = 0; i <= dx; i++)
			{
				glVertex2f(x, -y);
				//printf("%d,%d\n", x, y);
				x++, e = e + k;
				if (e >= 0)
				{
					y++;
					e--;
				}
			}
		}
		else
		{
			k = 1 / k;					// k>1  reverse x,y
			printf("x=%f,y=%f,k=%f\n", dx, dy, k);
			for (int i = 0; i <= dy; i++)
			{
				glVertex2f(x, -y);
				printf("%d,%d\n", x, y);
				y++, e = e + k;
				if (e >= 0)
				{
					x++;
					e--;
				}
			}
		}
	}
	
		
}
void circlepoints(int x, int y)
{
	glVertex2f(x, y); glVertex2f(y, x);
	glVertex2f(-x, y); glVertex2f(y, -x);
	glVertex2f(x, -y); glVertex2f(-y, x);
	glVertex2f(-x, -y); glVertex2f(-y, -x);
}

void midPointCircle(int r)
{
	int x, y;
	float d;
	x = 0; y = r; d = 1.25 - r;
	circlepoints(x, y);
	while (x<=y)
	{
		if (d < 0)
		{
			d += 2 * x + 3;
		}
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		circlepoints(x, y);
	}
	
}
void Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // 清空颜色缓冲池
	glPointSize(3);				//pointsize
	glBegin(GL_POINTS);
	
	//line
	glColor3f(0.0f, 1.0f, 1.0f);
	midPoint(0, 0, 100, 40);
	midPoint(-50, 0, 5, 70);
	midPoint(0, 0, 100, -40);
	midPoint(-50, 0, 5, -70);


	//circle
	glColor3f(0.5f, 0.0f, 0.5f);
	midPointCircle(R);
	glEnd();
	glFlush();
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	//printf("输入线段起始和终止点坐标（范围为0-400,0-400）");
	//scanf_s("%d, %d, %d, %d", &xs, &ys, &xe, &ye);
	//printf("输入圆半径：");
	//scanf_s("%d", &R);
	//xs = 0, ys = 0, xe = 50, ye = -150;
	R = 50;
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(500, 500);

	glutCreateWindow("中点画线法");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-200, 200, -200, 200);
	glutDisplayFunc(&Draw);

	glutMainLoop();
	return 0;
}