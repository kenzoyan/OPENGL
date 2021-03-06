// Mouse.cpp: 定义控制台应用程序的入口点。
//

// cube.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <GL/glut.h>

#include <stdlib.h>

#include <math.h>

#include <stdio.h>

// points 



struct GLintPoint
{
	int x, y;

};

  GLintPoint List[50];			//存储鼠标点击的坐标，与显示坐标不一样
  GLintPoint holeList[50];			//存储洞 鼠标点击的坐标，与显示坐标不一样
static  int nums = 0;
int height, width;
int pointChosen;
bool movepoint=false;			//是否对点进行拖拽
int mouseX, mouseY;
int movex, movey;
bool changecolor = false;
int polyNums[5];	//最多能够存在5个图形
int pnum = 0;
float scale = 1.0;
int holeNums[5];
int hnum=0;   //the number of hole
static int holePointsNums=0; //the number of points in holes
//确定模式 
#define drawgraph 1
#define shiftgraph 2
#define addhole	3
int now;
void showgraph()
{
	glClear(GL_COLOR_BUFFER_BIT); // 清空颜色缓冲池
	printf("darw the graph! pnum=%d\n",pnum);
	int base = 0;
	glColor3f(0.5f, 0.0f, 0.5f);
	if (changecolor)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	for (int i = 0; i < pnum; i++)
	{
		printf("into the loop\n");
		glBegin(GL_POLYGON);

		for (int j = base; j <polyNums[i]; j++)
		{
			glVertex2i(List[j].x, height - List[j].y);
		}
		glEnd();
		glFlush();
		glutPostRedisplay();
		base = polyNums[i];
	}
		base = 0;
		glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < hnum; i++)
	{
		glBegin(GL_POLYGON);

		for (int j = base; j <holeNums[i]; j++)
		{
			glVertex2i(holeList[j].x, height - holeList[j].y);
		}
		glEnd();
		glFlush();
		glutPostRedisplay();
		base = holeNums[i];
	}
}
void mouseCB(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;
	printf("%d is the mode now\n", now);
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN && (now == drawgraph|| now == addhole))			//存储点坐标 接下来可读取画图
		{

			printf("(%d,%d)", x, y);
												//调试点坐标
			/*
			glPointSize(4);
			glBegin(GL_POINTS);
			
			glVertex2i(x, height-y);
			glEnd();
			glFlush();*/
			if (now ==drawgraph)
			{
				List[nums].x = x;
				List[nums].y = y;
				nums++;
			}
			else if (now==addhole)
			{
				holeList[holePointsNums].x = x;
				holeList[holePointsNums].y = y;
				holePointsNums++;
			}
			
		}

		if (state == GLUT_DOWN && now ==shiftgraph)				//检测鼠标是否选中点 进行点拖拽
		{
			for (int i = 0; i < nums; i++)
			{
				int missx = List[i].x - mouseX;
				int missy = List[i].y - mouseY;
				//printf("%d %d\n",missx ,missy );
				if ((-10 <missx && missx < 10) && (-10 < missy &&missy< 10))//制作一定范围的窗口激活选取点
				{
					movepoint = true;
					printf("%d is the point you click\n", i + 1);
					pointChosen = i;
					break;
				}
				else
				{
					movepoint = false;
				}
			}
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && (now == drawgraph||now==addhole))			//右键点击之后 画出图形
	{
		if (state == GLUT_DOWN)
		{
			if(pnum>0)
				polyNums[pnum - 1] = nums;
			if(hnum>0)
				holeNums[hnum - 1] = holePointsNums;
			glPointSize(2);				//pointsize
			printf("nums=%d\n",nums);	
			//display 
			showgraph();
			//into the shift process
			now=shiftgraph;
			printf("into the shift graph process\n");
		}
	}

}

void mouseMotionCB(int x, int y)			//鼠标被动移动  不用点击
{
	
	if (now==shiftgraph)
	{
		if (movepoint)					//点拖拽
		{
			List[pointChosen].x = x;
			List[pointChosen].y = y;
			//display
			showgraph();
		}
		else
		{
			movex = (x - mouseX);			//全局拖拽
			movey = (y - mouseY);

			for (int i = 0; i <nums; i++)
			{
				List[i].x += movex;
				List[i].y += movey;
			}
			for (int i = 0; i <holePointsNums; i++)
			{
				holeList[i].x += movex;
				holeList[i].y += movey;
			}
			showgraph();
			
			mouseX = x;
			mouseY = y;;
		}
	}
}

void roll(int x, int y, int dir)				//旋转操作
{
	printf("into the roll process\n");
	
	float min = dir/10.0;
	float a;

	for (int i = 0; i <nums; i++)
	{	
		//0.01为最小旋转单位									效果不是很好 变形严重
		//List[i].x = x + (List[i].x - x)*cos(min) - (List[i].y - y)*sin(min);
		//List[i].y = y + (List[i].x - x)*sin(min) + (List[i].y - y)*cos(min);
																
																//效果更好，没变形

		float r= sqrt(pow(List[i].x - x, 2) + pow(List[i].y - y, 2));//r为顶点到鼠标点距离
		if (List[i].y >= y)//alpha用于表示旋转前顶点的位置，例如顶点相对鼠标点位于一二象限时，alpha是鼠标点顶点连线与x正半轴的夹角
			a = acos((List[i].x - x) / r);
		else//顶点相对鼠标点位于三四象限时，alpha对于位于一二象限的情况下计算得出的角度需要+/-180度
			a = -acos((List[i].x - x) / r);
		
		//此处为旋转后点坐标的计算公式
		List[i].x = x + r * cos(a + min);
		List[i].y = y + r * sin(a + min);
	}

	for (int i = 0; i <holePointsNums; i++)  //the rolling of the hole points
	{
		float r = sqrt(pow(holeList[i].x - x, 2) + pow(holeList[i].y - y, 2));
		if (holeList[i].y >= y)
			a = acos((holeList[i].x - x) / r);
		else
			a = -acos((holeList[i].x - x) / r);
		holeList[i].x = x + r * cos(a + min);
		holeList[i].y = y + r * sin(a + min);
	}
	showgraph();
}
void zoom(float scale)
{
	for (int j = 0; j <= nums; j++) {
		List[j].x= (int)(scale * List[j].x + (1 - scale)* width / 2);
		List[j].y = (int)(scale * List[j].y + (1 - scale)* height / 2);
	}
	for (int j = 0; j <= holePointsNums; j++) {
		holeList[j].x = (int)(scale * holeList[j].x + (1 - scale)* width / 2);
		holeList[j].y = (int)(scale * holeList[j].y + (1 - scale)* height / 2);
	}
}
void myKeyboard(unsigned char key, int x, int y)				//键盘响应事件
{
	int direction ;
	if (key == 'q')	
	{
		printf("rolling left\n");
		direction = -1;
		roll(x, y, direction);
		
	}
	else if (key== 'w')
	{
		printf("rolling right\n");
		direction = +1;
		roll(x, y, direction);
	}
	else if (key == 'i')
	{
		now = drawgraph;
		pnum++;
		printf("insert a new polygon\n");
	}
	else if (key == 'a')
	{
		now = addhole;
		hnum++;
		printf("insert a new hole\n");
	}
	else if (key=='c')
	{
		printf("change the color\n");
		changecolor = true;
		showgraph();
	}
	
	if (key == 'o')
	{
		printf("zoom bigger\n");
		scale = 1.01;
		zoom(scale);
		showgraph();
	}
	else if (key=='p')
	{
		printf("zoom smaller\n");
		scale = 0.99;
		zoom(scale);
		showgraph();
	}
}
 



void Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // 清空颜色缓冲池
	glFlush();
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

	height = 500;
	width = 500;
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(500, 500);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glFrontFace(GL_CCW); //设置逆时针方向为正面
	glutCreateWindow("POLYGON DRAWING");
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, height, 0,width);

	glutDisplayFunc(&Draw);
	glutMouseFunc(mouseCB);
	glutMotionFunc(mouseMotionCB);

	glutKeyboardFunc(myKeyboard);//键盘监听

	glutMainLoop();
	return 0;
}