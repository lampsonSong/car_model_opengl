// testOpenGL.cpp : model design of a car using openGL
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <gl\glut.h>   
#include <GL/glut.h>  


static int shoulder = 0,elbow = 0,num,num2,checkImageWidth,checkImageHeight,texName;

void LoadTex();

// points for Bezier curves
GLfloat forepoints[4][4][3] = {
	{{0.0,0.0,0.0},{0.3,0.0,0.0},{0.6,0.0,0.0},{1.0,0.0,0.0}},
	{{0.0,0.3,0.0},{0.3,0.3,-0.05},{0.6,0.3,-0.05},{0.95,0.3,-0.05}},
	{{0.0,0.4,0.0},{0.3,0.4,-0.07},{0.6,0.4,-0.07},{0.93,0.4,-0.07}},
	{{0.0,0.8,0.0},{0.3,0.7,-0.1},{0.6,0.6,-0.2},{0.8,0.5,-0.3}}
};

GLfloat frontPoints[4][4][3] = {
	{{1.0,0.0,0.0},{1.0,0.0,-0.5},{1.0,0.0,-1.0},{1.0,0.0,-1.5}},
	{{0.95,0.3,-0.03},{0.95,0.3,-0.5},{0.95,0.3,-1.0},{0.95,0.3,-1.5}},
	{{0.93,0.4,-0.07},{0.93,0.4,-0.5},{0.93,0.4,-1.0},{0.93,0.4,-1.5}},
	{{0.8,0.5,-0.3},{0.8,0.5,-0.5},{0.8,0.5,-1.0},{0.8,0.5,-1.2}}
};

GLfloat depthPoints[4][4][3] = {
	{{0.0,0.0,0.0},{0.3,0.0,0.0},{0.6,0.0,0.0},{1.0,0.0,0.0}},
	{{0.0,0.3,0.0},{0.3,0.3,0.05},{0.6,0.3,0.05},{0.95,0.3,0.05}},
	{{0.0,0.4,0.0},{0.3,0.4,0.07},{0.6,0.4,0.07},{0.93,0.4,0.07}},
	{{0.0,0.8,0.0},{0.3,0.7,0.1},{0.6,0.6,0.2},{0.8,0.5,0.3}}
};

GLfloat topPoints[4][4][3] = {
	{{0.0,0.8,0.0},{0.3,0.7,-0.1},{0.6,0.6,-0.2},{0.8,0.5,-0.3}},
	{{0.1,0.8,-0.5},{0.3,0.7,-0.5},{0.6,0.6,-0.5},{0.8,0.5,-0.5}},
	{{0.1,0.8,-1.0},{0.3,0.7,-1.0},{0.6,0.6,-1.0},{0.8,0.5,-1.5}},
	{{0.0,0.8,-1.5},{0.3,0.7,-1.4},{0.6,0.6,-1.3},{0.8,0.5,-1.2}}
};

GLfloat windGlass[6][4][3] = {
	{{0.0,0.0,0.0},{-0.3,0.3,0.0},{-0.7,0.6,0.0},{-1.0,0.8,0.0}},
	{{0.0,0.0,-0.3},{-0.3,0.4,-0.3},{-0.7,0.65,-0.3},{-1.0,0.83,-0.3}},
	{{0.0,0.0,-0.6},{-0.3,0.4,-0.6},{-0.7,0.65,-0.6},{-1.0,0.9,-0.6}},
	{{0.0,0.0,-0.9},{-0.3,0.4,-0.9},{-0.7,0.65,-0.9},{-1.0,0.85,-0.9}},
	{{0.0,0.0,-1.2},{-0.3,0.4,-1.2},{-0.7,0.65,-1.2},{-1.0,0.83,-1.2}},
	{{0.0,0.0,-1.5},{-0.3,0.3,-1.5},{-0.7,0.6,-1.5},{-1.0,0.8,-1.5}}
};

GLfloat backOne[5][5][3] = {
	{{0.0,0.0,0.0},{0.2,0.0,0.0},{0.4,0.0,0.0},{0.6,0.0,0.0},{0.8,0.0,0.0}},
	{{0.0,0.7,0.0},{0.2,0.7,0.0},{0.4,0.7,0.0},{0.6,0.7,0.0},{0.8,0.7,0.0}},
	{{0.0,0.78,0.0},{0.2,0.78,0.0},{0.4,0.78,0.0},{0.6,0.78,0.0},{0.8,0.78,0.0}},
	{{0.0,0.79,0.0},{0.2,0.79,0.0},{0.4,0.79,0.0},{0.6,0.79,0.0},{0.8,0.79,0.0}},
	{{0.0,0.8,-0.2},{0.2,0.8,-0.2},{0.4,0.8,-0.2},{0.6,0.8,-0.1},{0.8,0.8,0.0}}
};

GLfloat backTwo[5][5][3] = {
	{{0.0,0.0,0.0},{0.2,0.0,0.0},{0.4,0.0,0.0},{0.6,0.0,0.0},{0.8,0.0,0.0}},
	{{0.0,0.7,0.0},{0.2,0.7,0.0},{0.4,0.7,0.0},{0.6,0.7,0.0},{0.8,0.7,0.0}},
	{{0.0,0.78,0.0},{0.2,0.78,0.0},{0.4,0.78,0.0},{0.6,0.78,0.0},{0.8,0.78,0.0}},
	{{0.0,0.79,0.0},{0.2,0.79,0.0},{0.4,0.79,0.0},{0.6,0.79,0.0},{0.8,0.79,0.0}},
	{{0.0,0.8,0.2},{0.2,0.8,0.2},{0.4,0.8,0.2},{0.6,0.8,0.1},{0.8,0.8,0.0}}
};

GLfloat backThree[5][5][3] = {
	{{0.0,0.0,0.0},{0.0,0.0,-0.375},{0.0,0.0,-0.75},{0.0,0.0,-1.125},{0.0,0.0,-1.5}},
	{{0.0,0.1,0.0},{-0.05,0.1,-0.375},{-0.05,0.1,-0.75},{-0.05,0.1,-1.125},{0.0,0.1,-1.5}},
	{{0.0,0.5,0.0},{-0.05,0.5,-0.375},{-0.05,0.5,-0.75},{-0.05,0.5,-1.125},{0.0,0.5,-1.5}},
	{{0.0,0.79,0.0},{-0.05,0.79,-0.375},{-0.05,0.79,-0.75},{-0.05,0.79,-1.125},{0.0,0.79,-1.5}},
	{{0.0,0.8,-0.2},{0.0,0.8,-0.375},{0.0,0.8,-0.75},{0.0,0.8,-1.125},{0.0,0.8,-1.3}}
};

GLfloat backFour[5][5][3] = {
	{{0.0,0.8,-0.2},{0.0,0.8,-0.375},{0.0,0.8,-0.75},{0.0,0.8,-1.125},{0.0,0.8,-1.3}},
	{{0.2,0.8,0.0},{0.2,0.8,-0.375},{0.2,0.8,-0.75},{0.2,0.8,-1.125},{0.2,0.8,-1.5}},
	{{0.4,0.8,0.0},{0.4,0.8,-0.375},{0.4,0.8,-0.75},{0.4,0.8,-1.125},{0.4,0.8,-1.5}},
	{{0.5,0.8,0.0},{0.5,0.8,-0.375},{0.5,0.8,-0.75},{0.5,0.8,-1.125},{0.5,0.8,-1.5}},
	{{0.8,0.8,0.0},{0.65,0.8,-0.375},{0.5,0.8,-0.75},{0.65,0.8,-1.125},{0.8,0.8,-1.5}}
};

GLfloat backAxis[2][5][3] = {
	{{0.0,0.8,-0.0},{-0.1,0.8,-0.375},{-0.2,0.8,-0.75},{-0.1,0.8,-1.125},{0.0,0.8,-1.5}},
	{{0.4,0.8,-0.0},{0.2,0.8,-0.375},{0.0,0.8,-0.75},{0.2,0.8,-1.125},{0.4,0.8,-1.5}}
};

//the part left of door
GLfloat frontDoor[5][5][3] = {
	{{0.0,0.0,0.0},{0.2,0.0,0.0},{0.4,0.0,0.0},{0.6,0.0,0.0},{0.8,0.0,0.0}},
	{{0.0,0.2,0.0},{0.2,0.2,0.0},{0.4,0.2,0.0},{0.6,0.2,0.0},{0.8,0.2,0.0}},
	{{0.0,0.4,0.0},{0.2,0.4,0.0},{0.4,0.4,0.0},{0.6,0.4,0.0},{0.8,0.4,0.0}},
	{{0.0,0.7,0.0},{0.2,0.7,0.0},{0.4,0.7,0.0},{0.6,0.7,0.0},{0.8,0.7,0.0}},
	{{0.0,0.8,-0.2},{0.2,0.8,-0.2},{0.4,0.8,-0.15},{0.6,0.8,-0.1},{0.8,0.8,0.0}}
};
//door part
GLfloat frontDoorSecond[5][5][3] = {
	{{0.0,0.0,0.0},{0.2,0.0,0.0},{0.4,0.0,0.0},{0.6,0.0,0.0},{0.8,0.0,0.0}},
	{{0.0,0.2,0.0},{0.2,0.2,0.0},{0.4,0.2,0.0},{0.6,0.2,0.0},{0.8,0.2,0.0}},
	{{0.0,0.4,0.0},{0.2,0.4,0.0},{0.4,0.4,0.0},{0.6,0.4,0.0},{0.8,0.4,0.0}},
	{{0.0,0.7,0.0},{0.2,0.7,0.0},{0.4,0.7,0.0},{0.6,0.7,0.0},{0.8,0.7,0.0}},
	{{0.0,0.8,-0.2},{0.2,0.8,-0.2},{0.4,0.8,-0.2},{0.6,0.8,-0.2},{0.8,0.8,-0.2}}
};

GLfloat frontDoorSecondBack[5][5][3] = {
	{{0.0,0.0,-0.2},{0.2,0.0,-0.2},{0.4,0.0,-0.2},{0.6,0.0,-0.2},{0.8,0.0,-0.0}},
	{{0.0,0.2,-0.2},{0.2,0.2,-0.2},{0.4,0.2,-0.2},{0.6,0.2,-0.2},{0.8,0.2,-0.0}},
	{{0.0,0.4,-0.2},{0.2,0.4,-0.2},{0.4,0.4,-0.2},{0.6,0.4,-0.2},{0.8,0.4,-0.0}},
	{{0.0,0.7,-0.2},{0.2,0.7,-0.2},{0.4,0.7,-0.2},{0.6,0.7,-0.2},{0.8,0.7,-0.0}},
	{{0.0,0.8,-0.2},{0.2,0.8,-0.2},{0.4,0.8,-0.2},{0.6,0.8,-0.2},{0.8,0.8,-0.2}}
};

GLfloat frontDoorSide[5][2][3] = {
	{{0.0,0.0,-0.0},{0.0,0.0,-0.2}},
	{{0.0,0.2,-0.0},{0.0,0.2,-0.2}},
	{{0.0,0.4,-0.0},{0.0,0.4,-0.2}},
	{{0.0,0.7,-0.0},{0.0,0.7,-0.2}},
	{{0.0,0.8,-0.0},{0.0,0.8,-0.0}}
};

GLfloat frontDoorBottom[2][5][3] = {
	{{0.0,0.0,-0.0},{0.2,0.0,-0.0},{0.4,0.0,-0.0},{0.6,0.0,-0.0},{0.8,0.0,-0.0}},
	{{0.0,0.0,-0.2},{0.2,0.0,-0.2},{0.4,0.0,-0.2},{0.6,0.0,-0.2},{0.8,0.0,-0.0}}
};


//the part left behind door
GLfloat behindDoor[5][5][3] = {
	{{0.0,0.0,0.0},{0.2,0.0,0.0},{0.4,0.0,0.0},{0.6,0.0,0.0},{0.8,0.0,0.0}},
	{{0.0,0.2,0.0},{0.2,0.2,0.0},{0.4,0.2,0.0},{0.6,0.2,0.0},{0.8,0.2,0.0}},
	{{0.0,0.4,0.0},{0.2,0.4,0.0},{0.4,0.4,0.0},{0.6,0.4,0.0},{0.8,0.4,0.0}},
	{{0.0,0.7,0.0},{0.2,0.7,0.0},{0.4,0.7,0.0},{0.6,0.7,0.0},{0.8,0.7,0.0}},
	{{0.0,0.8,0.2},{0.2,0.8,0.2},{0.4,0.8,0.15},{0.6,0.8,0.1},{0.8,0.8,0.0}}
};
//behind door
GLfloat behindDoorSecond[5][5][3] = {
	{{0.0,0.0,0.0},{0.2,0.0,0.0},{0.4,0.0,0.0},{0.6,0.0,0.0},{0.8,0.0,0.0}},
	{{0.0,0.2,0.0},{0.2,0.2,0.0},{0.4,0.2,0.0},{0.6,0.2,0.0},{0.8,0.2,0.0}},
	{{0.0,0.4,0.0},{0.2,0.4,0.0},{0.4,0.4,0.0},{0.6,0.4,0.0},{0.8,0.4,0.0}},
	{{0.0,0.7,0.0},{0.2,0.7,0.0},{0.4,0.7,0.0},{0.6,0.7,0.0},{0.8,0.7,0.0}},
	{{0.0,0.8,0.2},{0.2,0.8,0.2},{0.4,0.8,0.2},{0.6,0.8,0.2},{0.8,0.8,0.2}}
};

GLfloat behindDoorSecondBack[5][5][3] = {
	{{0.0,0.0,0.2},{0.2,0.0,0.2},{0.4,0.0,0.2},{0.6,0.0,0.2},{0.8,0.0,0.0}},
	{{0.0,0.2,0.2},{0.2,0.2,0.2},{0.4,0.2,0.2},{0.6,0.2,0.2},{0.8,0.2,0.0}},
	{{0.0,0.4,0.2},{0.2,0.4,0.2},{0.4,0.4,0.2},{0.6,0.4,0.2},{0.8,0.4,0.0}},
	{{0.0,0.7,0.2},{0.2,0.7,0.2},{0.4,0.7,0.2},{0.6,0.7,0.2},{0.8,0.7,0.0}},
	{{0.0,0.8,0.2},{0.2,0.8,0.2},{0.4,0.8,0.2},{0.6,0.8,0.2},{0.8,0.8,0.2}}
};

GLfloat behindDoorSide[5][2][3] = {
	{{0.0,0.0,-0.0},{0.0,0.0,0.2}},
	{{0.0,0.2,-0.0},{0.0,0.2,0.2}},
	{{0.0,0.4,-0.0},{0.0,0.4,0.2}},
	{{0.0,0.7,-0.0},{0.0,0.7,0.2}},
	{{0.0,0.8,-0.0},{0.0,0.8,0.0}}
};

GLfloat behindDoorBottom[2][5][3] = {
	{{0.0,0.0,-0.0},{0.2,0.0,-0.0},{0.4,0.0,-0.0},{0.6,0.0,-0.0},{0.8,0.0,-0.0}},
	{{0.0,0.0,0.2},{0.2,0.0,0.2},{0.4,0.0,0.2},{0.6,0.0,0.2},{0.8,0.0,0.0}}
};

GLfloat innerRadius,outerRadius;
int nsides,rings;
bool left= false,right=false;
static GLdouble viewer[]= {0.0, 0.0, 2.0}; /* initial viewer location */

//车头部分右侧面
void init(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,4,
		0,1,12,4,&forepoints[0][0][0]);

	glEnable(GL_MAP2_VERTEX_3);

	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEvalMesh2(GL_FILL,0,20,0,20);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	//glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,4,&ctrlpoints[0][0]);
	//glEnable(GL_MAP1_VERTEX_3);

}

//车头前面的部分
void foreCover(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,4,
		0,1,12,4,&frontPoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEvalMesh2(GL_FILL,0,20,0,20);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void depthCover(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,4,
		0,1,12,4,&depthPoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEvalMesh2(GL_FILL,0,20,0,20);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void topCover(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,4,
		0,1,12,4,&topPoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEvalMesh2(GL_FILL,0,20,0,20);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void foreGlass(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,4,
		0,1,12,6,&windGlass[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void backFront(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,5,&backOne[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void backDepth(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,5,&backTwo[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void backBack(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,5,&backThree[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void backCover(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,5,&backFour[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}


void DoorFront(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,5,&frontDoor[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void DoorFrontSecond(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,5,&frontDoorSecond[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void DoorFrontSecondBack(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,5,&frontDoorSecondBack[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void DoorFrontBottom(void){
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,2,&frontDoorBottom[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void DoorFrontSide(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,2,
		0,1,6,5,&frontDoorSide[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void DoorBehind(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,5,&behindDoor[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void DoorBehindSecond(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,5,&behindDoorSecond[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void DoorBehindSecondBack(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,5,&behindDoorSecondBack[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void DoorBehindBottom(void){
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,2,&behindDoorBottom[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void DoorBehindSide(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,2,
		0,1,6,5,&behindDoorSide[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void AxisBack(void){
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,2,&backAxis[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

static GLfloat lightPosition[4];  //position for light0
GLfloat light_position[] = { 2.0, 2.0, 0.0, 1.0 };
static float lightangle_X = 0.0, lightHeight = 1; 

void lightInit(void)
{
	//Initialize material property
    GLfloat mat_specular[] = { 3000.0, 3000.0, 3000.0, 3000.0 };
    GLfloat mat_shininess[] = { 100.0 };
    GLfloat mat_ambient[] = { 1.0, 1.0, 0.0, 0.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    //Initialize light source
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);

    glEnable(GL_LIGHTING);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
}


//加载图片的方法
void LoadTex()
{

    unsigned int Texture;

                FILE* img = NULL;
                img = fopen("headfront.bmp","rb");
	
   
    int size = 0;    

    fseek(img,18,SEEK_SET);
    fread(&checkImageWidth,4,1,img);
    fread(&checkImageHeight,4,1,img);
    fseek(img,0,SEEK_END);
    size = ftell(img) - 54;
	
    unsigned char *data = (unsigned char*)malloc(size);

    fseek(img,54,SEEK_SET);    // image data
    fread(data,size,1,img);

    fclose(img);
	
    glGenTextures(1, &Texture);
    glBindTexture(GL_TEXTURE_2D, Texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, checkImageWidth, checkImageHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	
    if (data)
        free(data);

}



void display(void)   
{   
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	innerRadius = 0.1;
	outerRadius = 0.5;
	nsides = 18;
	rings = 18;
	int i,n = 300;
	GLfloat Pi = 3.1415,R = 0.1;

	glClear(GL_COLOR_BUFFER_BIT);
	

	//New position for light0 changed by mouse motion
	lightPosition[0] = 2*cos(lightangle_X);
	lightPosition[1] = lightHeight;
	lightPosition[2] = 2*sin(lightangle_X);
	lightPosition[3] = 1;

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_LIGHT0);

	glPushMatrix();
	gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0,-1.0,0.0);
	glRotatef(shoulder,0.0,1.0,0.0);
	

	

	//glutSolidTeapot (1.00);
	//glutWireTeapot(1.0);

	//forward back tyre,前端里面的轮胎
	glPushMatrix();
	glTranslatef(-1.5,0.15,0.0);
	glutSolidTorus(innerRadius,outerRadius,nsides,rings);
	
	glBegin(GL_LINE_STRIP);
		 for(i=0; i<n; ++i)
         glVertex2f(R*cos(2*Pi/n*i), R*sin(2*Pi/n*i));
	glEnd();
	glPopMatrix();
	//forward head tyre,radius of circle is 0.1， 前端外面的轮胎
	glPushMatrix();
	glTranslatef(1.5,0.15,0.0);
	glutSolidTorus(innerRadius,outerRadius,nsides,rings);
			//画一个圆，盖住内胎
	glBegin(GL_LINE_STRIP);
		 for(i=0; i<n; ++i)
         glVertex2f(R*cos(2*Pi/n*i), R*sin(2*Pi/n*i));
	glEnd();
	glPopMatrix();
	//backward back tyre ， 后端里面的轮胎
	glPushMatrix();
	glTranslatef(-1.5,0.15,-1.5);
	glutSolidTorus(innerRadius,outerRadius,nsides,rings);
	glBegin(GL_LINE_STRIP);
		 for(i=0; i<n; ++i)
         glVertex2f(R*cos(2*Pi/n*i), R*sin(2*Pi/n*i));
	glEnd();
	glPopMatrix();
	//backward head tyre， 后端外面的轮胎
	glPushMatrix();
	glTranslatef(1.5,0.15,-1.5);
	glutSolidTorus(innerRadius,outerRadius,nsides,rings);
	glBegin(GL_LINE_STRIP);
		 for(i=0; i<n; ++i)
         glVertex2f(R*cos(2*Pi/n*i), R*sin(2*Pi/n*i));
	glEnd();
	glPopMatrix();
	//back bearing ， 后轴承
	glPushMatrix();
	GLUquadricObj *backBearing;  
	backBearing = gluNewQuadric();
	glTranslatef(-1.5,0.15,-1.5);
	gluCylinder(backBearing,0.1,0.1,1.5,18,4);
	glPopMatrix();
	//forward bearing， 前轴承
	glPushMatrix();
	GLUquadricObj *forwardBearing;  
	forwardBearing = gluNewQuadric();
	glTranslatef(1.5,0.15,-1.5);
	gluCylinder(forwardBearing,0.1,0.1,1.5,18,4);
	glPopMatrix();
	
	
	//forward bottom of the whole car
	glPushMatrix();
	glTranslatef(-2.5,0.0,0.0);
	//back part from 0 point is 2.5, front part is 1.5, forward convex is 1.3
	glScalef((2.5+1.5+1.3)/0.8,1.0,1.0);
	//glutWireCube(1.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(0.8,0.0,0.0);
	glVertex3f(0.0,0.0,-1.5);
	glVertex3f(0.8,0.0,-1.5);
	glEnd();
	glPopMatrix();



	//开始贝塞尔曲线部分

	
	// 车前半部分
	glPushMatrix();
		
		glTranslatef(1.5,0.0,0.0);
		glScalef(1.3,1.0,1.0);
			//curves
			int iCurve,jCurve;
			//glTranslatef(3.0,0.0,0.0);
			//glRotatef(90,0.0,1.0,0.0);
	
			//车头部分右侧面
			init();
			glPushMatrix();
			//glEvalMesh2(GL_FILL,0,20,0,20);
			for(jCurve=0; jCurve<=8; jCurve++)
			{
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve<= 30;iCurve++)
					glEvalCoord2f((GLfloat)iCurve/30.0,(GLfloat)jCurve/8.0);
				glEnd();
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve <= 30;iCurve++)
					glEvalCoord2f((GLfloat)jCurve/8.0,(GLfloat)iCurve/30.0);
				glEnd();
			}
			glPopMatrix();
			glDisable(GL_DEPTH_TEST);
			
			//车头部分前面
			foreCover();
			glPushMatrix();
			//glEvalMesh2(GL_FILL,0,20,0,20);
			for(jCurve=0; jCurve<=8; jCurve++)
			{
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve<= 30;iCurve++)
					glEvalCoord2f((GLfloat)iCurve/30.0,(GLfloat)jCurve/8.0);
				glEnd();
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve <= 30;iCurve++)
					glEvalCoord2f((GLfloat)jCurve/8.0,(GLfloat)iCurve/30.0);
				glEnd();
			}
			glPopMatrix();

			glDisable(GL_TEXTURE_2D);
			//glDisable(GL_MAP2_VERTEX_3);
			glDisable(GL_MAP2_TEXTURE_COORD_1);
			glDisable(GL_MAP2_TEXTURE_COORD_2);
			glDisable(GL_DEPTH_TEST);
			
			//depth , inside cover
			depthCover();
			glPushMatrix();
			glTranslatef(0.0,0.0,-1.5);
			//glRotatef(85.0,1.0,1.0,1.0);
			//glEvalMesh2(GL_FILL,0,20,0,20);
			for(jCurve=0; jCurve<=8; jCurve++)
			{
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve<= 30;iCurve++)
					glEvalCoord2f((GLfloat)iCurve/30.0,(GLfloat)jCurve/8.0);
				glEnd();
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve <= 30;iCurve++)
					glEvalCoord2f((GLfloat)jCurve/8.0,(GLfloat)iCurve/30.0);
				glEnd();
			}
			glPopMatrix();
			glDisable(GL_DEPTH_TEST);

			//top cover
			topCover();
			glPushMatrix();
			//glTranslatef(1.5,0.0,0.0);
			//glRotatef(85.0,1.0,1.0,1.0);
			for(jCurve=0; jCurve<=8; jCurve++)
			{
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve<= 30;iCurve++)
					glEvalCoord2f((GLfloat)iCurve/30.0,(GLfloat)jCurve/8.0);
				glEnd();
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve <= 30;iCurve++)
					glEvalCoord2f((GLfloat)jCurve/8.0,(GLfloat)iCurve/30.0);
				glEnd();
			}
			glPopMatrix();
			glDisable(GL_DEPTH_TEST);
	glPopMatrix();
			//wind glasses
			foreGlass();
			glPushMatrix();
			glTranslatef(1.5,0.8,0.0);
			glRotatef(15.0,0.0,0.0,1.0);
			for(jCurve=0; jCurve<=8; jCurve++)
			{
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve<= 30;iCurve++)
					glEvalCoord2f((GLfloat)iCurve/30.0,(GLfloat)jCurve/8.0);
				glEnd();
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve <= 30;iCurve++)
					glEvalCoord2f((GLfloat)jCurve/8.0,(GLfloat)iCurve/30.0);
				glEnd();
			}
			glPopMatrix();
			glDisable(GL_DEPTH_TEST);


	//the back of the car
	glPushMatrix();

	
	glTranslatef(-2.5,0.0,0.0);
	glScalef(2.0,1.0,1.0);
			//backFront
			backFront();
			glPushMatrix();
			//glTranslatef(1.5,0.8,0.0);
			//glRotatef(15.0,0.0,0.0,1.0);
			for(jCurve=0; jCurve<=8; jCurve++)
			{
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve<= 30;iCurve++)
					glEvalCoord2f((GLfloat)iCurve/30.0,(GLfloat)jCurve/8.0);
				glEnd();
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve <= 30;iCurve++)
					glEvalCoord2f((GLfloat)jCurve/8.0,(GLfloat)iCurve/30.0);
				glEnd();
			}
			glPopMatrix();
			glDisable(GL_DEPTH_TEST);


			//backDepth
			backDepth();
			glPushMatrix();
			glTranslatef(0.0,0.0,-1.5);
			//glRotatef(15.0,0.0,0.0,1.0);
			for(jCurve=0; jCurve<=8; jCurve++)
			{
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve<= 30;iCurve++)
					glEvalCoord2f((GLfloat)iCurve/30.0,(GLfloat)jCurve/8.0);
				glEnd();
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve <= 30;iCurve++)
					glEvalCoord2f((GLfloat)jCurve/8.0,(GLfloat)iCurve/30.0);
				glEnd();
			}
			glPopMatrix();
			glDisable(GL_DEPTH_TEST);


			//backBack
			backBack();
			glPushMatrix();
			for(jCurve=0; jCurve<=8; jCurve++)
			{
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve<= 30;iCurve++)
					glEvalCoord2f((GLfloat)iCurve/30.0,(GLfloat)jCurve/8.0);
				glEnd();
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve <= 30;iCurve++)
					glEvalCoord2f((GLfloat)jCurve/8.0,(GLfloat)iCurve/30.0);
				glEnd();
			}
			glPopMatrix();
			glDisable(GL_DEPTH_TEST);

			//backCover
			backCover();
			glPushMatrix();
			for(jCurve=0; jCurve<=8; jCurve++)
			{
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve<= 30;iCurve++)
					glEvalCoord2f((GLfloat)iCurve/30.0,(GLfloat)jCurve/8.0);
				glEnd();
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve <= 30;iCurve++)
					glEvalCoord2f((GLfloat)jCurve/8.0,(GLfloat)iCurve/30.0);
				glEnd();
			}
			glPopMatrix();
			glDisable(GL_DEPTH_TEST);
	glPopMatrix();


	AxisBack();
	glPushMatrix();
		glTranslatef(-2.5,0.2,0.0);
		glRotatef(-10.0,0.0,0.0,1.0);
		glScalef(1.0,1.0,1.0);
		for(jCurve=0; jCurve<=8; jCurve++)
			{
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve<= 30;iCurve++)
					glEvalCoord2f((GLfloat)iCurve/30.0,(GLfloat)jCurve/8.0);
				glEnd();
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve <= 30;iCurve++)
					glEvalCoord2f((GLfloat)jCurve/8.0,(GLfloat)iCurve/30.0);
				glEnd();
			}
	
	glPopMatrix();
		glDisable(GL_DEPTH_TEST);




	//front Door				the width of door is 3.2, for the front part is 1.5 x and the back part is 2.5 - 0.8 = 1.7
	glPushMatrix();
	DoorFront();
	glTranslatef(0.8,0.0,0.0);
	glScalef(0.9,1.0,1.0);
	for(jCurve=0; jCurve<=8; jCurve++)
			{
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve<= 30;iCurve++)
					glEvalCoord2f((GLfloat)iCurve/30.0,(GLfloat)jCurve/8.0);
				glEnd();
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve <= 30;iCurve++)
					glEvalCoord2f((GLfloat)jCurve/8.0,(GLfloat)iCurve/30.0);
				glEnd();
			}
	glPopMatrix();

	glPushMatrix();
		if(right == true)
		{
			glTranslatef(1.15/2,0.0,1.15*1.73/2);
			glRotatef(60.0,0.0,1.0,0.0);
		}
				glPushMatrix();
				DoorFrontSecond();
				glTranslatef(-0.9,0.0,0.0);
				glScalef(2.3,1.0,1.0);
				for(jCurve=0; jCurve<=8; jCurve++)
						{
							glBegin(GL_LINE_STRIP);
							for(iCurve = 0; iCurve<= 30;iCurve++)
								glEvalCoord2f((GLfloat)iCurve/30.0,(GLfloat)jCurve/8.0);
							glEnd();
							glBegin(GL_LINE_STRIP);
							for(iCurve = 0; iCurve <= 30;iCurve++)
								glEvalCoord2f((GLfloat)jCurve/8.0,(GLfloat)iCurve/30.0);
							glEnd();
						}
				glPopMatrix();

				glPushMatrix();
				DoorFrontSecondBack();
				glTranslatef(-0.9,0.0,0.0);
				glScalef(2.3,1.0,1.0);
				for(jCurve=0; jCurve<=8; jCurve++)
						{
							glBegin(GL_LINE_STRIP);
							for(iCurve = 0; iCurve<= 30;iCurve++)
								glEvalCoord2f((GLfloat)iCurve/30.0,(GLfloat)jCurve/8.0);
							glEnd();
							glBegin(GL_LINE_STRIP);
							for(iCurve = 0; iCurve <= 30;iCurve++)
								glEvalCoord2f((GLfloat)jCurve/8.0,(GLfloat)iCurve/30.0);
							glEnd();
						}
				glPopMatrix();

				glPushMatrix();
				DoorFrontSide();
				glTranslatef(-0.9,0.0,-0.2);
				//glScalef(2.3,1.0,1.0);
				glRotatef(180.0,0.0,1.0,0.0);
				for(jCurve=0; jCurve<=8; jCurve++)
						{
							glBegin(GL_LINE_STRIP);
							for(iCurve = 0; iCurve<= 30;iCurve++)
								glEvalCoord2f((GLfloat)iCurve/30.0,(GLfloat)jCurve/8.0);
							glEnd();
							glBegin(GL_LINE_STRIP);
							for(iCurve = 0; iCurve <= 30;iCurve++)
								glEvalCoord2f((GLfloat)jCurve/8.0,(GLfloat)iCurve/30.0);
							glEnd();
						}
				glPopMatrix();

				glPushMatrix();
				DoorFrontBottom();
				glTranslatef(-0.9,0.0,-0.0);
				glScalef(2.3,1.0,1.0);
				//glRotatef(180.0,0.0,1.0,0.0);
				for(jCurve=0; jCurve<=8; jCurve++)
						{
							glBegin(GL_LINE_STRIP);
							for(iCurve = 0; iCurve<= 30;iCurve++)
								glEvalCoord2f((GLfloat)iCurve/30.0,(GLfloat)jCurve/8.0);
							glEnd();
							glBegin(GL_LINE_STRIP);
							for(iCurve = 0; iCurve <= 30;iCurve++)
								glEvalCoord2f((GLfloat)jCurve/8.0,(GLfloat)iCurve/30.0);
							glEnd();
						}
				glPopMatrix();
	glPopMatrix();



	//behind Door				the width of door is 3.2, for the front part is 1.5 x and the back part is 2.5 - 0.8 = 1.7
	
	glPushMatrix();
	DoorBehind();
	
	glTranslatef(0.8,0.0,-1.5);
	glScalef(0.9,1.0,1.0);
	for(jCurve=0; jCurve<=8; jCurve++)
			{
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve<= 30;iCurve++)
					glEvalCoord2f((GLfloat)iCurve/30.0,(GLfloat)jCurve/8.0);
				glEnd();
				glBegin(GL_LINE_STRIP);
				for(iCurve = 0; iCurve <= 30;iCurve++)
					glEvalCoord2f((GLfloat)jCurve/8.0,(GLfloat)iCurve/30.0);
				glEnd();
			}
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0,0.0,-1.5);
		if(left == true)
		{
			glTranslatef(1.15/2,0.0,-1.15*1.73/2);
			glRotatef(-60.0,0.0,1.0,0.0);
		}
				glPushMatrix();
				DoorBehindSecond();
				glTranslatef(-0.9,0.0,0.0);
				glScalef(2.3,1.0,1.0);
				for(jCurve=0; jCurve<=8; jCurve++)
						{
							glBegin(GL_LINE_STRIP);
							for(iCurve = 0; iCurve<= 30;iCurve++)
								glEvalCoord2f((GLfloat)iCurve/30.0,(GLfloat)jCurve/8.0);
							glEnd();
							glBegin(GL_LINE_STRIP);
							for(iCurve = 0; iCurve <= 30;iCurve++)
								glEvalCoord2f((GLfloat)jCurve/8.0,(GLfloat)iCurve/30.0);
							glEnd();
						}
				glPopMatrix();

				glPushMatrix();
				DoorBehindSecondBack();
				glTranslatef(-0.9,0.0,0.0);
				glScalef(2.3,1.0,1.0);
				for(jCurve=0; jCurve<=8; jCurve++)
						{
							glBegin(GL_LINE_STRIP);
							for(iCurve = 0; iCurve<= 30;iCurve++)
								glEvalCoord2f((GLfloat)iCurve/30.0,(GLfloat)jCurve/8.0);
							glEnd();
							glBegin(GL_LINE_STRIP);
							for(iCurve = 0; iCurve <= 30;iCurve++)
								glEvalCoord2f((GLfloat)jCurve/8.0,(GLfloat)iCurve/30.0);
							glEnd();
						}
				glPopMatrix();

				glPushMatrix();
				DoorBehindSide();
				glTranslatef(-0.9,0.0,0.2);
				//glScalef(2.3,1.0,1.0);
				glRotatef(180.0,0.0,1.0,0.0);
				for(jCurve=0; jCurve<=8; jCurve++)
						{
							glBegin(GL_LINE_STRIP);
							for(iCurve = 0; iCurve<= 30;iCurve++)
								glEvalCoord2f((GLfloat)iCurve/30.0,(GLfloat)jCurve/8.0);
							glEnd();
							glBegin(GL_LINE_STRIP);
							for(iCurve = 0; iCurve <= 30;iCurve++)
								glEvalCoord2f((GLfloat)jCurve/8.0,(GLfloat)iCurve/30.0);
							glEnd();
						}
				glPopMatrix();

				glPushMatrix();
				DoorBehindBottom();
				glTranslatef(-0.9,0.0,-0.0);
				glScalef(2.3,1.0,1.0);
				//glRotatef(180.0,0.0,1.0,0.0);
				for(jCurve=0; jCurve<=8; jCurve++)
						{
							glBegin(GL_LINE_STRIP);
							for(iCurve = 0; iCurve<= 30;iCurve++)
								glEvalCoord2f((GLfloat)iCurve/30.0,(GLfloat)jCurve/8.0);
							glEnd();
							glBegin(GL_LINE_STRIP);
							for(iCurve = 0; iCurve <= 30;iCurve++)
								glEvalCoord2f((GLfloat)jCurve/8.0,(GLfloat)iCurve/30.0);
							glEnd();
						}
				glPopMatrix();
	glPopMatrix();



	glPopMatrix();
	glutSwapBuffers();

	
}



 void reshape(int w, int h)
 {
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0,(GLfloat)w/(GLfloat)h,1.0,20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0,0.0,-5.0);
 }

 void keyboard(unsigned char key, int x, int y)
 {
	 switch(key){
	 case 'w': /*s key rotates ar shoulder*/
		 shoulder = (shoulder+5)%360;
		 glutPostRedisplay();
		 break;
	 case 's':
		 shoulder = (shoulder-5)%360;
		 glutPostRedisplay();
		 break;
	 case 'd':/*e key rotate at elbow*/
		 elbow = (elbow+5)%360;
		 glutPostRedisplay();
		 break;
	 case 'a':
		 elbow = (elbow - 5)%360;
		 glutPostRedisplay();
		 break;
	 case 'l':
		 if(left == false)
			 left = true;
		 else
			 left = false;
		 break;
	 case 'r':
		 if(right == false)
			 right = true;
		 else
			 right = false;
		 break;
	 default:
		 break;
	 }

	 if(key == 'x') viewer[0]-= 1.0;
   if(key == 'X') viewer[0]+= 1.0;
   if(key == 'y') viewer[1]-= 1.0;
   if(key == 'Y') viewer[1]+= 1.0;
   if(key == 'z') viewer[2]-= 1.0;
   if(key == 'Z') viewer[2]+= 1.0;
   display();
 }

 int main(int argc, char *argv[])   
{   
    glutInit(&argc, argv);   
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);   
    glutInitWindowPosition(100, 100);   
    glutInitWindowSize(500, 500);   
    glutCreateWindow("Robot Arms");   
    lightInit();
	glutDisplayFunc(display);
    glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
    return 0;   
}
