// testOpenGL.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <gl\glut.h>   
#include <GL/glut.h>
#include <string>

static int shoulder = 0,elbow = 0,num,num2,checkImageWidth,checkImageHeight,texName;

GLfloat innerRadius,outerRadius;
int nsides,rings,Texture;
bool left= false,right=false;
static GLdouble viewer[]= {0.0, 0.0, 2.0}; /* initial viewer location */

void LoadTex(std::string img_name);

//俩个灯的开关
int light0 = 0;
int light1 = 0;

static int angle = 5;

static GLfloat lightPosition[4];  //position for light0
GLfloat light_position[] = { 2.0, 2.0, 0.0, 1.0 };
static float lightangle_X = 0.0, lightHeight = 1; 
GLUquadricObj *pDisk;

float majorRadius=0.5f,minorRadius=0.2f;
    float PI=3.1415926f;
    int majorNum=40;
    int minorNum=10;
    float majorStep=2*PI/majorNum;
    float minorStep=2*PI/minorNum;


	//door part,外面门的点
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


//depth door,里面的门的点
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
	{{0.0,0.0,0.0},{0.0,0.0,0.2}},
	{{0.0,0.2,0.0},{0.0,0.2,0.2}},
	{{0.0,0.4,0.0},{0.0,0.4,0.2}},
	{{0.0,0.7,0.0},{0.0,0.7,0.2}},
	{{0.0,0.8,0.0},{0.0,0.8,0.0}}
};

GLfloat behindDoorBottom[2][5][3] = {
	{{0.0,0.0,-0.0},{0.2,0.0,-0.0},{0.4,0.0,-0.0},{0.6,0.0,-0.0},{0.8,0.0,-0.0}},
	{{0.0,0.0,0.2},{0.2,0.0,0.2},{0.4,0.0,0.2},{0.6,0.0,0.2},{0.8,0.0,0.0}}
};

/**
*   定义车头前面部分的点
*/
//外方的点
GLfloat forepoints[4][4][3] = {
	{{0.0,0.0,0.0},{0.3,0.0,0.0},{0.6,0.0,0.0},{1.0,0.0,0.0}},
	{{0.0,0.3,-0.0},{0.3,0.3,-0.05},{0.6,0.3,-0.05},{0.95,0.3,-0.05}},
	{{0.0,0.4,-0.0},{0.3,0.4,-0.07},{0.6,0.4,-0.07},{0.93,0.4,-0.07}},
	{{0.0,0.8,-0.0},{0.3,0.7,-0.1},{0.6,0.6,-0.2},{0.8,0.5,-0.3}}
};
//有车灯那一面的点
GLfloat frontPoints[4][4][3] = {
	{{1.0,0.0,0.0},{1.0,0.0,-0.5},{1.0,0.0,-1.0},{1.0,0.0,-1.5}},
	{{0.95,0.3,-0.03},{0.95,0.3,-0.5},{0.95,0.3,-1.0},{0.95,0.3,-1.5}},
	{{0.93,0.4,-0.07},{0.93,0.4,-0.5},{0.93,0.4,-1.0},{0.93,0.4,-1.5}},
	{{0.8,0.5,-0.3},{0.8,0.5,-0.5},{0.8,0.5,-1.0},{0.8,0.5,-1.2}}
};
//内方的点
GLfloat depthPoints[4][4][3] = {
	{{0.0,0.0,0.0},{0.3,0.0,0.0},{0.6,0.0,0.0},{1.0,0.0,0.0}},
	{{0.0,0.3,0.0},{0.3,0.3,0.05},{0.6,0.3,0.05},{0.95,0.3,0.05}},
	{{0.0,0.4,0.0},{0.3,0.4,0.07},{0.6,0.4,0.07},{0.93,0.4,0.07}},
	{{0.0,0.8,0.0},{0.3,0.7,0.1},{0.6,0.6,0.2},{0.8,0.5,0.3}}
};
//车头盖子的点
GLfloat topPoints[4][4][3] = {
	{{0.0,0.8,0.0},{0.3,0.7,-0.1},{0.6,0.6,-0.2},{0.8,0.5,-0.3}},
	{{0.1,0.8,-0.5},{0.3,0.7,-0.5},{0.6,0.6,-0.5},{0.8,0.5,-0.5}},
	{{0.1,0.8,-1.0},{0.3,0.7,-1.0},{0.6,0.6,-1.0},{0.8,0.5,-1.5}},
	{{0.0,0.8,-1.5},{0.3,0.7,-1.4},{0.6,0.6,-1.3},{0.8,0.5,-1.2}}
};

/**
*  车尾部分的点
*  分成四部分来看
*/
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
	{{0.0,0.8,-0.1},{0.0,0.8,-0.375},{0.0,0.8,-0.75},{0.0,0.8,-1.125},{0.0,0.8,-1.4}}
};

GLfloat backFour[5][5][3] = {
	{{0.0,0.8,-0.2},{0.0,0.8,-0.375},{0.0,0.8,-0.75},{0.0,0.8,-1.125},{0.0,0.8,-1.3}},
	{{0.2,0.8,0.0},{0.2,0.8,-0.375},{0.2,0.8,-0.75},{0.2,0.8,-1.125},{0.2,0.8,-1.5}},
	{{0.4,0.8,0.0},{0.4,0.8,-0.375},{0.4,0.8,-0.75},{0.4,0.8,-1.125},{0.4,0.8,-1.5}},
	{{0.5,0.8,0.0},{0.5,0.8,-0.375},{0.5,0.8,-0.75},{0.5,0.8,-1.125},{0.5,0.8,-1.5}},
	{{0.8,0.8,0.0},{0.65,0.8,-0.375},{0.5,0.8,-0.75},{0.65,0.8,-1.125},{0.8,0.8,-1.5}}
};


/**
*挡风玻璃的点
**/
GLfloat windGlass[6][4][3] = {
	{{0.0,0.0,0.0},{-0.3,0.3,0.0},{-0.7,0.6,0.0},{-1.0,0.8,0.0}},
	{{0.0,0.0,-0.3},{-0.3,0.4,-0.3},{-0.7,0.65,-0.3},{-1.0,0.83,-0.3}},
	{{0.0,0.0,-0.6},{-0.3,0.4,-0.6},{-0.7,0.65,-0.6},{-1.0,0.9,-0.6}},
	{{0.0,0.0,-0.9},{-0.3,0.4,-0.9},{-0.7,0.65,-0.9},{-1.0,0.85,-0.9}},
	{{0.0,0.0,-1.2},{-0.3,0.4,-1.2},{-0.7,0.65,-1.2},{-1.0,0.83,-1.2}},
	{{0.0,0.0,-1.5},{-0.3,0.3,-1.5},{-0.7,0.6,-1.5},{-1.0,0.8,-1.5}}
};

/**
*  后面那个杠的点
**/
GLfloat backAxis[2][5][3] = {
	{{0.0,0.8,-0.0},{-0.1,0.8,-0.375},{-0.2,0.8,-0.75},{-0.1,0.8,-1.125},{0.0,0.8,-1.5}},
	{{0.4,0.8,-0.0},{0.2,0.8,-0.375},{0.0,0.8,-0.75},{0.2,0.8,-1.125},{0.4,0.8,-1.5}}
};


/**
*   连接层
**/
//the part left of door
GLfloat frontDoor[5][5][3] = {
	{{0.0,0.0,0.0},{0.2,0.0,0.0},{0.4,0.0,0.0},{0.6,0.0,0.0},{0.8,0.0,0.0}},
	{{0.0,0.2,0.0},{0.2,0.2,0.0},{0.4,0.2,0.0},{0.6,0.2,0.0},{0.8,0.2,0.0}},
	{{0.0,0.4,0.0},{0.2,0.4,0.0},{0.4,0.4,0.0},{0.6,0.4,0.0},{0.8,0.4,0.0}},
	{{0.0,0.7,0.0},{0.2,0.7,0.0},{0.4,0.7,0.0},{0.6,0.7,0.0},{0.8,0.7,0.0}},
	{{0.0,0.8,-0.2},{0.2,0.8,-0.2},{0.4,0.8,-0.15},{0.6,0.8,-0.1},{0.8,0.8,0.0}}
};
//the part left behind door
GLfloat behindDoor[5][5][3] = {
	{{0.0,0.0,0.0},{0.2,0.0,0.0},{0.4,0.0,0.0},{0.6,0.0,0.0},{0.8,0.0,0.0}},
	{{0.0,0.2,0.0},{0.2,0.2,0.0},{0.4,0.2,0.0},{0.6,0.2,0.0},{0.8,0.2,0.0}},
	{{0.0,0.4,0.0},{0.2,0.4,0.0},{0.4,0.4,0.0},{0.6,0.4,0.0},{0.8,0.4,0.0}},
	{{0.0,0.7,0.0},{0.2,0.7,0.0},{0.4,0.7,0.0},{0.6,0.7,0.0},{0.8,0.7,0.0}},
	{{0.0,0.8,0.2},{0.2,0.8,0.2},{0.4,0.8,0.15},{0.6,0.8,0.1},{0.8,0.8,0.0}}
};

void lightInit(void)
{
	GLfloat mat_specular[] = { 3000.0, 3000.0, 3000.0, 3000.0 };
	GLfloat mat_shininess[] = { 100.0 };
    GLfloat mat_ambient[] = { 2.0, 2.0, 1.0, 0.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	 GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    //Initialize light source
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

	GLfloat light_position[] = { 1.0, 1.0, 0.5, 0.0 };   //positional light source
	GLfloat light_position1[] = { 2.0, 0.0, 0.5, 0.0 };  //directional light source
		
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

    glEnable(GL_LIGHTING);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);
}


//加载图片的方法
void LoadTex(std::string strFile)
{

    unsigned int Texture;

                FILE* img = NULL;
                img = fopen(strFile.c_str(),"rb");
	
   
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
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 4, checkImageWidth, checkImageHeight, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	
    if (data)
        free(data);

}


//轮胎内圈圆纹理
void tyreCircle()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

	LoadTex("imgs/tyre.bmp");
	glBindTexture(GL_TEXTURE_2D,Texture);

	glShadeModel(GL_FLAT);
}

/**
*  外车门的求值器
**/

//外车门，第一部分，前面
void DoorFrontSecond(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,5,&frontDoorSecond[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	GLfloat tex[8] = {0.0,0.0,1.0,0.0,0.0, 1.0, 1.0, 1.0};
	LoadTex("imgs/carSkin.bmp");
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0,1,2,2,0,1,4,2,
		&tex[0]);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}
//外车门，第二部分，侧边
void DoorFrontSide(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,2,
		0,1,6,5,&frontDoorSide[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	GLfloat tex[8] = {0.0,0.0,1.0,0.0,0.0, 1.0, 1.0, 1.0};
	LoadTex("imgs/carSkin.bmp");
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0,1,2,2,0,1,4,2,
		&tex[0]);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

//外车门，第三部分，底部
void DoorFrontBottom(void){
	glClearColor(0.0,0.0,0.0,0.0);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,2,&frontDoorBottom[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	GLfloat tex[8] = {0.0,0.0,1.0,0.0,0.0, 1.0, 1.0, 1.0};
	LoadTex("imgs/carSkin.bmp");
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0,1,2,2,0,1,4,2,
		&tex[0]);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}
//外车门，第四部分，背部
void DoorFrontSecondBack(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,5,&frontDoorSecondBack[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	GLfloat tex[8] = {0.0,0.0,1.0,0.0,0.0, 1.0, 1.0, 1.0};
	LoadTex("imgs/doorBack.bmp");
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0,1,2,2,0,1,4,2,
		&tex[0]);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}


/**
*  内车门的求值器
**/

//the first part of depth door,里面车门第一部分
void DoorBehindSecond(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,5,&behindDoorSecond[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	GLfloat tex[8] = {0.0,0.0,1.0,0.0,0.0, 1.0, 1.0, 1.0};
	LoadTex("imgs/carSkin.bmp");
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0,1,2,2,0,1,4,2,
		&tex[0]);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}
//the second part of depth door, 里面车门第二部分
void DoorBehindSecondBack(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,5,&behindDoorSecondBack[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	GLfloat tex[8] = {0.0,0.0,1.0,0.0,0.0, 1.0, 1.0, 1.0};
	LoadTex("imgs/doorBack.bmp");
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0,1,2,2,0,1,4,2,
		&tex[0]);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

//the third part of depth door, 里面车门第三部分
void DoorBehindBottom(void){
	glClearColor(0.0,0.0,0.0,0.0);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,2,&behindDoorBottom[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	GLfloat tex[8] = {0.0,0.0,1.0,0.0,0.0, 1.0, 1.0, 1.0};
	LoadTex("imgs/carSkin.bmp");
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0,1,2,2,0,1,4,2,
		&tex[0]);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

//the fourth part of depth part ,里面车门第四部分
void DoorBehindSide(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,2,
		0,1,6,5,&behindDoorSide[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	GLfloat tex[8] = {0.0,0.0,1.0,0.0,0.0, 1.0, 1.0, 1.0};
	LoadTex("imgs/carSkin.bmp");
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0,1,2,2,0,1,4,2,
		&tex[0]);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}


/**
*   画车头部分
**/
//外方向的面
void init(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE); 
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,4,
		0,1,12,4,&forepoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	GLfloat tex[8] = {0.0,0.0,1.0,0.0,0.0, 1.0, 1.0, 1.0};
	LoadTex("imgs/carSkin.bmp");
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0,1,2,2,0,1,4,2,
		&tex[0]);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

//有车灯的面
void foreCover(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,4,
		0,1,12,4,&frontPoints[0][0][0]);
	
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glEnable(GL_MAP2_VERTEX_3);
	GLfloat tex[8] = {0.0,0.0,1.0,0.0,0.0, 1.0, 1.0, 1.0};
	LoadTex("imgs/carSkin.bmp");
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0,1,2,2,0,1,4,2,
		&tex[0]);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}
//内方的面
void depthCover(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,4,
		0,1,12,4,&depthPoints[0][0][0]);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glEnable(GL_MAP2_VERTEX_3);
	GLfloat tex[8] = {0.0,0.0,1.0,0.0,0.0, 1.0, 1.0, 1.0};
	LoadTex("imgs/carSkin.bmp");
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0,1,2,2,0,1,4,2,
		&tex[0]);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEvalMesh2(GL_FILL,0,20,0,20);
	//glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

//顶上的面
void topCover(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,4,
		0,1,12,4,&topPoints[0][0][0]);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glEnable(GL_MAP2_VERTEX_3);
	GLfloat tex[8] = {0.0,0.0,1.0,0.0,0.0, 1.0, 1.0, 1.0};
	LoadTex("imgs/carSkin.bmp");
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0,1,2,2,0,1,4,2,
		&tex[0]);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEvalMesh2(GL_FILL,0,20,0,20);
	//glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}


/**
*   车尾部分的求值器
*/
//外方
void backFront(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,5,&backOne[0][0][0]);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glEnable(GL_MAP2_VERTEX_3);
	GLfloat tex[8] = {0.0,0.0,1.0,0.0,0.0, 1.0, 1.0, 1.0};
	LoadTex("imgs/carSkin.bmp");
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0,1,2,2,0,1,4,2,
		&tex[0]);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}
//内方
void backDepth(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,5,&backTwo[0][0][0]);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glEnable(GL_MAP2_VERTEX_3);
	GLfloat tex[8] = {0.0,0.0,1.0,0.0,0.0, 1.0, 1.0, 1.0};
	LoadTex("imgs/carSkin.bmp");
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0,1,2,2,0,1,4,2,
		&tex[0]);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}
//后车有车牌的部分
void backBack(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,5,&backThree[0][0][0]);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glEnable(GL_MAP2_VERTEX_3);
	GLfloat tex[8] = {0.0,0.0,1.0,0.0,0.0, 1.0, 1.0, 1.0};
	LoadTex("imgs/carSkin.bmp");
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0,1,2,2,0,1,4,2,
		&tex[0]);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}
//后车盖子
void backCover(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,5,&backFour[0][0][0]);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glEnable(GL_MAP2_VERTEX_3);
	GLfloat tex[8] = {0.0,0.0,1.0,0.0,0.0, 1.0, 1.0, 1.0};
	LoadTex("imgs/carSkin.bmp");
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0,1,2,2,0,1,4,2,
		&tex[0]);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}


/**
*   挡风玻璃的求值器
**/
void foreGlass(void)
{
	//glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,4,
		0,1,12,6,&windGlass[0][0][0]);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glEnable(GL_MAP2_VERTEX_3);
	GLfloat tex[8] = {0.0,0.0,1.0,0.0,0.0, 1.0, 1.0, 1.0};
	LoadTex("imgs/glass.bmp");
	
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0,1,2,2,0,1,4,2,
		&tex[0]);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}


/**
*   后面那个杠
**/
void AxisBack(void){
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,2,&backAxis[0][0][0]);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glEnable(GL_MAP2_VERTEX_3);
	GLfloat tex[8] = {0.0,0.0,1.0,0.0,0.0, 1.0, 1.0, 1.0};
	LoadTex("imgs/carSkin.bmp");
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0,1,2,2,0,1,4,2,
		&tex[0]);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}


/**
*   中间连接层求值器
**/
void DoorFront(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,5,&frontDoor[0][0][0]);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glEnable(GL_MAP2_VERTEX_3);
	GLfloat tex[8] = {0.0,0.0,1.0,0.0,0.0, 1.0, 1.0, 1.0};
	LoadTex("imgs/carSkin.bmp");
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0,1,2,2,0,1,4,2,
		&tex[0]);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}

void DoorBehind(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,5,
		0,1,15,5,&behindDoor[0][0][0]);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glEnable(GL_MAP2_VERTEX_3);
	GLfloat tex[8] = {0.0,0.0,1.0,0.0,0.0, 1.0, 1.0, 1.0};
	LoadTex("imgs/carSkin.bmp");
	glMap2f(GL_MAP2_TEXTURE_COORD_2,0,1,2,2,0,1,4,2,
		&tex[0]);
	glMapGrid2f(20,0.0,1.0,20,0.0,1.0);
	//glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}


void display(void)   
{   
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	 glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
	innerRadius = 0.1;
	outerRadius = 0.5;
	nsides = 18;
	rings = 18;
	int i,n = 300;
	GLfloat Pi = 3.1415,R = 0.4;




	glPushMatrix();
	gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glTranslatef(-2.0,-1.0,2.0);
	glRotatef(shoulder,0.0,1.0,0.0);
	

	//鼠标拖动光源
	//lightPosition[0] = 2*cos(lightangle_X);
	//lightPosition[1] = lightHeight;
	//lightPosition[2] = 2*sin(lightangle_X);
	//lightPosition[3] = 1;

	
	//开关灯
	/*
	if(light0 == 0)
	{
		printf("开\n");
	    glEnable(GL_LIGHT0);
	}
	else
		glDisable(GL_LIGHT0);

	if(light1 == 0)
	    glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);
		*/
			/**
			*  车头部分
			**/
			glPushMatrix();
				glTranslatef(1.0,-0.1,0.0);
				glScalef(2.0,1.0,1.6);

				// 深度测试设置为只读
				// glDepthMask(GL_FALSE);
					/**
					*  挡风玻璃
					**/
					glPushMatrix();
								glScalef(0.5,1.0,1.0);
								glTranslatef(2.05,0.78,0.0);
								glRotatef(15.0,0.0,0.0,1.0);								
								glEnable(GL_TEXTURE_2D);
								glEnable(GL_MAP2_VERTEX_3);
								glEnable(GL_MAP2_TEXTURE_COORD_1);
								glEnable(GL_MAP2_TEXTURE_COORD_2);
								foreGlass();
								glEvalMesh2(GL_FILL, 0, 20, 0, 20);
								glDisable(GL_TEXTURE_2D);
								glDisable(GL_MAP2_VERTEX_3);
								glDisable(GL_MAP2_TEXTURE_COORD_1);
								glDisable(GL_MAP2_TEXTURE_COORD_2);
								glEnable(GL_DEPTH_TEST);
					glPopMatrix();

					//画完，还原深度数据可写
					 // glDepthMask(GL_TRUE);
					
					//车头方向前面的面
					glPushMatrix();
								glTranslatef(1.0,0.0,0.0);
								glEnable(GL_TEXTURE_2D);
								glEnable(GL_MAP2_VERTEX_3);
								glEnable(GL_MAP2_TEXTURE_COORD_1);
								glEnable(GL_MAP2_TEXTURE_COORD_2);
								init();
								glEvalMesh2(GL_FILL, 0, 20, 0, 20);
								glDisable(GL_TEXTURE_2D);
								glDisable(GL_MAP2_VERTEX_3);
								glDisable(GL_MAP2_TEXTURE_COORD_1);
								glDisable(GL_MAP2_TEXTURE_COORD_2);
					glPopMatrix();
					//外方的面
					glPushMatrix();
								glTranslatef(1.0,0.0,0.0);
								glEnable(GL_TEXTURE_2D);
								glEnable(GL_MAP2_VERTEX_3);
								glEnable(GL_MAP2_TEXTURE_COORD_1);
								glEnable(GL_MAP2_TEXTURE_COORD_2);
								foreCover();
								glEvalMesh2(GL_FILL, 0, 20, 0, 20);
								glEnable(GL_BLEND);
								glDisable(GL_TEXTURE_2D);
								glDisable(GL_MAP2_VERTEX_3);
								glDisable(GL_MAP2_TEXTURE_COORD_1);
								glDisable(GL_MAP2_TEXTURE_COORD_2);
					glPopMatrix();
					//内方的面
					glPushMatrix();
								glTranslatef(1.0,0.0,-1.5);
								glEnable(GL_TEXTURE_2D);
								glEnable(GL_MAP2_VERTEX_3);
								glEnable(GL_MAP2_TEXTURE_COORD_1);
								glEnable(GL_MAP2_TEXTURE_COORD_2);
								depthCover();
								glEvalMesh2(GL_FILL, 0, 20, 0, 20);
								glDisable(GL_TEXTURE_2D);
								glDisable(GL_MAP2_VERTEX_3);
								glDisable(GL_MAP2_TEXTURE_COORD_1);
								glDisable(GL_MAP2_TEXTURE_COORD_2);
					glPopMatrix();
					//顶上的面
					glPushMatrix();
								glTranslatef(1.0,0.0,0.0);
								glEnable(GL_TEXTURE_2D);
								glEnable(GL_MAP2_VERTEX_3);
								glEnable(GL_MAP2_TEXTURE_COORD_1);
								glEnable(GL_MAP2_TEXTURE_COORD_2);
								topCover();
								glEvalMesh2(GL_FILL, 0, 20, 0, 20);
								glDisable(GL_TEXTURE_2D);
								glDisable(GL_MAP2_VERTEX_3);
								glDisable(GL_MAP2_TEXTURE_COORD_1);
								glDisable(GL_MAP2_TEXTURE_COORD_2);
					glPopMatrix();
			glPopMatrix();




			/**
			*   车尾部分
			*/
			glPushMatrix();
				glTranslatef(-0.5,-0.1,-0.1);
				glScalef(2.5,1.0,1.5);
						//车尾外方
						glPushMatrix();
								glEnable(GL_TEXTURE_2D);
								glEnable(GL_MAP2_VERTEX_3);
								glEnable(GL_MAP2_TEXTURE_COORD_1);
								glEnable(GL_MAP2_TEXTURE_COORD_2);
								backFront();
								glEvalMesh2(GL_FILL, 0, 20, 0, 20);
								glDisable(GL_TEXTURE_2D);
								glDisable(GL_MAP2_VERTEX_3);
								glDisable(GL_MAP2_TEXTURE_COORD_1);
								glDisable(GL_MAP2_TEXTURE_COORD_2);
						glPopMatrix();
						//车尾内方
						glPushMatrix();
								glTranslatef(0.0,0.0,-1.5);
								glEnable(GL_TEXTURE_2D);
								glEnable(GL_MAP2_VERTEX_3);
								glEnable(GL_MAP2_TEXTURE_COORD_1);
								glEnable(GL_MAP2_TEXTURE_COORD_2);
								backDepth();
								glEvalMesh2(GL_FILL, 0, 20, 0, 20);
								glDisable(GL_TEXTURE_2D);
								glDisable(GL_MAP2_VERTEX_3);
								glDisable(GL_MAP2_TEXTURE_COORD_1);
								glDisable(GL_MAP2_TEXTURE_COORD_2);
						glPopMatrix();
						//车尾有车牌的面
						glPushMatrix();
								glEnable(GL_TEXTURE_2D);
								glEnable(GL_MAP2_VERTEX_3);
								glEnable(GL_MAP2_TEXTURE_COORD_1);
								glEnable(GL_MAP2_TEXTURE_COORD_2);
								backBack();
								glEvalMesh2(GL_FILL, 0, 20, 0, 20);
								glDisable(GL_TEXTURE_2D);
								glDisable(GL_MAP2_VERTEX_3);
								glDisable(GL_MAP2_TEXTURE_COORD_1);
								glDisable(GL_MAP2_TEXTURE_COORD_2);
						glPopMatrix();
						//车尾盖子
						glPushMatrix();
								glEnable(GL_TEXTURE_2D);
								glEnable(GL_MAP2_VERTEX_3);
								glEnable(GL_MAP2_TEXTURE_COORD_1);
								glEnable(GL_MAP2_TEXTURE_COORD_2);
								backCover();
								glEvalMesh2(GL_FILL, 0, 20, 0, 20);
								glDisable(GL_TEXTURE_2D);
								glDisable(GL_MAP2_VERTEX_3);
								glDisable(GL_MAP2_TEXTURE_COORD_1);
								glDisable(GL_MAP2_TEXTURE_COORD_2);
						glPopMatrix();
			glPopMatrix();


			/**
			*   车最后那个杠
			**/
			glPushMatrix();
					glTranslatef(-0.5,0.2,0.0);
					glRotatef(-10.0,0.0,0.0,1.0);
					glScalef(1.0,1.0,1.6);
					glEnable(GL_TEXTURE_2D);
					glEnable(GL_MAP2_VERTEX_3);
					glEnable(GL_MAP2_TEXTURE_COORD_1);
					glEnable(GL_MAP2_TEXTURE_COORD_2);
					AxisBack();
					glEvalMesh2(GL_FILL, 0, 20, 0, 20);
					glDisable(GL_TEXTURE_2D);
					glDisable(GL_MAP2_VERTEX_3);
					glDisable(GL_MAP2_TEXTURE_COORD_1);
					glDisable(GL_MAP2_TEXTURE_COORD_2);
			glPopMatrix();


			/**
			*  竖杠
			**/
			glPushMatrix();
			glTranslatef(-0.4,0.65,-0.4);
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
			LoadTex("imgs/carSkin.bmp");
			glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0);glVertex3f(0.0,0.0,0.0);
			glTexCoord2f(0.0,1.0);glVertex3f(0.0,0.3,0.0);
			glTexCoord2f(1.0,1.0);glVertex3f(0.2,0.3,0.0);
			glTexCoord2f(1.0,0.0);glVertex3f(0.2,0.0,0.0);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-0.4,0.65,-2.0);
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
			LoadTex("imgs/carSkin.bmp");
			glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0);glVertex3f(0.0,0.0,0.0);
			glTexCoord2f(0.0,1.0);glVertex3f(0.0,0.3,0.0);
			glTexCoord2f(1.0,1.0);glVertex3f(0.2,0.3,0.0);
			glTexCoord2f(1.0,0.0);glVertex3f(0.2,0.0,0.0);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();

			/**
			*   连接层
			**/
			glPushMatrix();
					glTranslatef(2.4,-0.1,-0.02);
					glScalef(0.9,1.0,1.0);
					glEnable(GL_TEXTURE_2D);
					glEnable(GL_MAP2_VERTEX_3);
					glEnable(GL_MAP2_TEXTURE_COORD_1);
					glEnable(GL_MAP2_TEXTURE_COORD_2);
					DoorFront();
					glEvalMesh2(GL_FILL, 0, 20, 0, 20);
					glDisable(GL_TEXTURE_2D);
					glDisable(GL_MAP2_VERTEX_3);
					glDisable(GL_MAP2_TEXTURE_COORD_1);
					glDisable(GL_MAP2_TEXTURE_COORD_2);
			glPopMatrix();
			glPushMatrix();
					glTranslatef(2.4,-0.1,-2.38);
					glEnable(GL_TEXTURE_2D);
					glEnable(GL_MAP2_VERTEX_3);
					glEnable(GL_MAP2_TEXTURE_COORD_1);
					glEnable(GL_MAP2_TEXTURE_COORD_2);
					DoorBehind();
					glEvalMesh2(GL_FILL, 0, 20, 0, 20);
					glDisable(GL_TEXTURE_2D);
					glDisable(GL_MAP2_VERTEX_3);
					glDisable(GL_MAP2_TEXTURE_COORD_1);
					glDisable(GL_MAP2_TEXTURE_COORD_2);
			glPopMatrix();

			/**
			*  底盘
			**/
			glPushMatrix();
			glTranslatef(-0.4,0.0,-0.2);
			glScalef((5.3)/0.8,1.0,1.3);
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
			LoadTex("imgs/tyreSkin.bmp");
			glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0);glVertex3f(0.0,0.0,0.0);
			glTexCoord2f(0.0,1.0);glVertex3f(0.0,0.0,-1.5);
			glTexCoord2f(1.0,1.0);glVertex3f(0.8,0.0,-1.5);
			glTexCoord2f(1.0,0.0);glVertex3f(0.8,0.0,0.0);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();


			//前车门
			glPushMatrix();
			//开车门
			if(right == true)
			{
				glTranslatef(1.2,0.0,2.1);
				glRotatef(60.0,0.0,1.0,0.0);
			}
			glTranslatef(0.1,-0.1,0.0);
			glScalef(1.3,1.0,1.0);
						//前车门，第一部分
						glPushMatrix();
						glTranslatef(1.0,0.0,0.0);
						//glRotatef(180,0.0,1.0,0.0);
						glEnable(GL_TEXTURE_2D);
						glEnable(GL_MAP2_VERTEX_3);
						glEnable(GL_MAP2_TEXTURE_COORD_1);
						glEnable(GL_MAP2_TEXTURE_COORD_2);
						DoorFrontSecond();
						glEvalMesh2(GL_FILL, 0, 20, 0, 20);
						glDisable(GL_TEXTURE_2D);
						glDisable(GL_MAP2_VERTEX_3);
						glDisable(GL_MAP2_TEXTURE_COORD_1);
						glDisable(GL_MAP2_TEXTURE_COORD_2);
						glPopMatrix();
						//前车门，第二部分,侧边
						glPushMatrix();
						glTranslatef(1.0,0.0,-0.2);
						glRotatef(180.0,0.0,1.0,0.0);
						glEnable(GL_TEXTURE_2D);
						glEnable(GL_MAP2_VERTEX_3);
						glEnable(GL_MAP2_TEXTURE_COORD_1);
						glEnable(GL_MAP2_TEXTURE_COORD_2);
						DoorFrontSide();
						glEvalMesh2(GL_FILL, 0, 20, 0, 20);
						glDisable(GL_TEXTURE_2D);
						glDisable(GL_MAP2_VERTEX_3);
						glDisable(GL_MAP2_TEXTURE_COORD_1);
						glDisable(GL_MAP2_TEXTURE_COORD_2);
						glPopMatrix();

						//前车门，第三部分，底边
						glPushMatrix();
						glTranslatef(1.0,0.0,0.0);
						glEnable(GL_TEXTURE_2D);
						glEnable(GL_MAP2_VERTEX_3);
						glEnable(GL_MAP2_TEXTURE_COORD_1);
						glEnable(GL_MAP2_TEXTURE_COORD_2);
						DoorFrontBottom();
						glEvalMesh2(GL_FILL, 0, 20, 0, 20);
						glDisable(GL_TEXTURE_2D);
						glDisable(GL_MAP2_VERTEX_3);
						glDisable(GL_MAP2_TEXTURE_COORD_1);
						glDisable(GL_MAP2_TEXTURE_COORD_2);
						glPopMatrix();
	
						//前车门，第四部分，背部
						glPushMatrix();
						glTranslatef(1.0,0.0,0.0);
						glEnable(GL_TEXTURE_2D);
						glEnable(GL_MAP2_VERTEX_3);
						glEnable(GL_MAP2_TEXTURE_COORD_1);
						glEnable(GL_MAP2_TEXTURE_COORD_2);
						DoorFrontSecondBack();
						glEvalMesh2(GL_FILL, 0, 20, 0, 20);
						glDisable(GL_TEXTURE_2D);
						glDisable(GL_MAP2_VERTEX_3);
						glDisable(GL_MAP2_TEXTURE_COORD_1);
						glDisable(GL_MAP2_TEXTURE_COORD_2);
						glPopMatrix();
			glPopMatrix();

			//内车门
			glPushMatrix();
			//开车门
			if(left == true)
			{
				glTranslatef(-0.9,0.0,-3.3);
				glRotatef(-60.0,0.0,1.0,0.0);
			}
			glTranslatef(1.4,-0.1,-2.4);
			glScalef(1.3,1.0,1.0);
						//内车门，第一部分
						glPushMatrix();
						glTranslatef(0.0,0.0,0.0);
						//glRotatef(180,0.0,1.0,0.0);
						glEnable(GL_TEXTURE_2D);
						glEnable(GL_MAP2_VERTEX_3);
						glEnable(GL_MAP2_TEXTURE_COORD_1);
						glEnable(GL_MAP2_TEXTURE_COORD_2);
						DoorBehindSecond();
						glEvalMesh2(GL_FILL, 0, 20, 0, 20);
						glDisable(GL_TEXTURE_2D);
						glDisable(GL_MAP2_VERTEX_3);
						glDisable(GL_MAP2_TEXTURE_COORD_1);
						glDisable(GL_MAP2_TEXTURE_COORD_2);
						glPopMatrix();
						//内车门，第二部分,侧边
						glPushMatrix();
						glTranslatef(0.0,0.0,0.2);
						glRotatef(180.0,0.0,1.0,0.0);
						glEnable(GL_TEXTURE_2D);
						glEnable(GL_MAP2_VERTEX_3);
						glEnable(GL_MAP2_TEXTURE_COORD_1);
						glEnable(GL_MAP2_TEXTURE_COORD_2);
						DoorBehindSide();
						glEvalMesh2(GL_FILL, 0, 20, 0, 20);
						glDisable(GL_TEXTURE_2D);
						glDisable(GL_MAP2_VERTEX_3);
						glDisable(GL_MAP2_TEXTURE_COORD_1);
						glDisable(GL_MAP2_TEXTURE_COORD_2);
						glPopMatrix();

						//内车门，第三部分，底边
						glPushMatrix();
						glEnable(GL_TEXTURE_2D);
						glEnable(GL_MAP2_VERTEX_3);
						glEnable(GL_MAP2_TEXTURE_COORD_1);
						glEnable(GL_MAP2_TEXTURE_COORD_2);
						DoorBehindBottom();
						glEvalMesh2(GL_FILL, 0, 20, 0, 20);
						glDisable(GL_TEXTURE_2D);
						glDisable(GL_MAP2_VERTEX_3);
						glDisable(GL_MAP2_TEXTURE_COORD_1);
						glDisable(GL_MAP2_TEXTURE_COORD_2);
						glPopMatrix();
	
						//内车门，第四部分，背部
						glPushMatrix();
						glEnable(GL_TEXTURE_2D);
						glEnable(GL_MAP2_VERTEX_3);
						glEnable(GL_MAP2_TEXTURE_COORD_1);
						glEnable(GL_MAP2_TEXTURE_COORD_2);
						DoorBehindSecondBack();
						glEvalMesh2(GL_FILL, 0, 20, 0, 20);
						glDisable(GL_TEXTURE_2D);
						glDisable(GL_MAP2_VERTEX_3);
						glDisable(GL_MAP2_TEXTURE_COORD_1);
						glDisable(GL_MAP2_TEXTURE_COORD_2);
						glPopMatrix();
			glPopMatrix();


			//四个轮胎整体---------------------------------------------------四个轮胎整体
																			glPushMatrix();
																				glScalef(0.8,0.8,0.8);
																				glTranslatef(4.0,0.0,0.0);
																				//内方右轮
																				glPushMatrix();
																						glEnable(GL_TEXTURE_2D);
																						
																						glTranslatef(-3.0,0.0,0.0);
																						glRotatef(-angle,0.0,0.0,1.0);
																						LoadTex("imgs/tyreSkin.bmp");
																						glBegin(GL_QUAD_STRIP);
																						for(int i=0;i<majorNum;i++)
																						{
																							float a0=i*majorStep;
																							float a1=a0+majorStep;
																							float x0=cos(a0);
																							float y0=sin(a0);
																							float x1=cos(a1);
																							float y1=sin(a1);
																							for(int j=0;j<minorNum;j++)
																							{
																								float b=j*minorStep;
																								float r=majorRadius+minorRadius*cos(b);
																								float z= 0.25*sin(b);
																								glTexCoord2f(float(i)/majorNum,float(j)/minorNum);
																								glVertex3f(r*x0,r*y0,z);

																								glTexCoord2f(float(i+1)/majorNum,float(j)/minorNum);
																								glVertex3f(r*x1,r*y1,z);
																							}
																						}
																						glDisable(GL_TEXTURE_2D);
																						glEnd();

																						glEnable(GL_TEXTURE_2D);
																						pDisk = gluNewQuadric();
																						gluQuadricTexture(pDisk, GLU_TRUE);
																						glBindTexture(GL_TEXTURE_2D,Texture);
																						LoadTex("imgs/tyre.bmp");
																						gluDisk(pDisk,0.0,0.3,40,30);
																						glDisable(GL_TEXTURE_2D);
																				glPopMatrix();


																				//内方左轮
																				glPushMatrix();
																						glTranslatef(-3.0,0.0,-3.0);
																						//glScalef (1.5, 1.5, 1.5);
																						//glutSolidTorus(innerRadius,outerRadius,nsides,rings);
																						glRotatef(-angle,0.0,0.0,1.0);
																						glEnable(GL_TEXTURE_2D);
																						LoadTex("imgs/tyreSkin.bmp");
																						glBegin(GL_QUAD_STRIP);
																						for(int i=0;i<majorNum;i++)
																						{
																							float a0=i*majorStep;
																							float a1=a0+majorStep;
																							float x0=cos(a0);
																							float y0=sin(a0);
																							float x1=cos(a1);
																							float y1=sin(a1);
																							for(int j=0;j<minorNum;j++)
																							{
																								float b=j*minorStep;
																								float r=majorRadius+minorRadius*cos(b);
																								float z= 0.25*sin(b);
																								glTexCoord2f(float(i)/majorNum,float(j)/minorNum);
																								glVertex3f(r*x0,r*y0,z);

																								glTexCoord2f(float(i+1)/majorNum,float(j)/minorNum);
																								glVertex3f(r*x1,r*y1,z);
																							}
																						}
																						glDisable(GL_TEXTURE_2D);
																						glEnd();

																						glEnable(GL_TEXTURE_2D);
																						pDisk = gluNewQuadric();
																						gluQuadricTexture(pDisk, GLU_TRUE);
																						glBindTexture(GL_TEXTURE_2D,Texture);
																						LoadTex("imgs/tyre.bmp");
																						gluDisk(pDisk,0.0,0.3,40,30);
																						glDisable(GL_TEXTURE_2D);
																				glPopMatrix();


	
																				//外方右轮
																				glPushMatrix();
																						glTranslatef(0.0,0.0,0.0);
																						//glScalef (1.5, 1.5, 1.5);
																						//glutSolidTorus(innerRadius,outerRadius,nsides,rings);
																						glRotatef(-angle,0.0,0.0,1.0);
																						glEnable(GL_TEXTURE_2D);
																						LoadTex("imgs/tyreSkin.bmp");
																						glBegin(GL_QUAD_STRIP);
																						for(int i=0;i<majorNum;i++)
																						{
																							float a0=i*majorStep;
																							float a1=a0+majorStep;
																							float x0=cos(a0);
																							float y0=sin(a0);
																							float x1=cos(a1);
																							float y1=sin(a1);
																							for(int j=0;j<minorNum;j++)
																							{
																								float b=j*minorStep;
																								float r=majorRadius+minorRadius*cos(b);
																								float z= 0.25*sin(b);
																								glTexCoord2f(float(i)/majorNum,float(j)/minorNum);
																								glVertex3f(r*x0,r*y0,z);

																								glTexCoord2f(float(i+1)/majorNum,float(j)/minorNum);
																								glVertex3f(r*x1,r*y1,z);
																							}
																						}
																						glDisable(GL_TEXTURE_2D);
																						glEnd();

																						glEnable(GL_TEXTURE_2D);
																						pDisk = gluNewQuadric();
																						gluQuadricTexture(pDisk, GLU_TRUE);
																						glBindTexture(GL_TEXTURE_2D,Texture);
																						LoadTex("imgs/tyre.bmp");
																						gluDisk(pDisk,0.0,0.3,40,30);
																						glDisable(GL_TEXTURE_2D);
																				glPopMatrix();


																				//外方左轮
																				glPushMatrix();
																						glTranslatef(0.0,0.0,-3.0);
																						//glScalef (1.5, 1.5, 1.5);
																						//glutSolidTorus(innerRadius,outerRadius,nsides,rings);
																						glRotatef(-angle,0.0,0.0,1.0);
																						glEnable(GL_TEXTURE_2D);
																						LoadTex("imgs/tyreSkin.bmp");
																						glBegin(GL_QUAD_STRIP);
																						for(int i=0;i<majorNum;i++)
																						{
																							float a0=i*majorStep;
																							float a1=a0+majorStep;
																							float x0=cos(a0);
																							float y0=sin(a0);
																							float x1=cos(a1);
																							float y1=sin(a1);
																							for(int j=0;j<minorNum;j++)
																							{
																								float b=j*minorStep;
																								float r=majorRadius+minorRadius*cos(b);
																								float z= 0.25*sin(b);
																								glTexCoord2f(float(i)/majorNum,float(j)/minorNum);
																								glVertex3f(r*x0,r*y0,z);

																								glTexCoord2f(float(i+1)/majorNum,float(j)/minorNum);
																								glVertex3f(r*x1,r*y1,z);
																							}
																						}
																						glDisable(GL_TEXTURE_2D);
																						glEnd();

																						glEnable(GL_TEXTURE_2D);
																						pDisk = gluNewQuadric();
																						gluQuadricTexture(pDisk, GLU_TRUE);
																						glBindTexture(GL_TEXTURE_2D,Texture);
																						LoadTex("imgs/tyre.bmp");
																						gluDisk(pDisk,0.0,0.3,40,30);
																						glDisable(GL_TEXTURE_2D);
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

    if(key == '0')
   {
	   if(light0 == 1)
					light0 = 0;
				else
					light0 = 1;
   }
   if(key == '9')
   {
		if(light1 == 1)
				light1 = 0;
			else
				light1 = 1;
   }

   if(key == 'f')
   {
	   angle = (angle+5)%360;
   }

   display();
 }

 int main(int argc, char *argv[])   
{   
    glutInit(&argc, argv);   
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);   
    glutInitWindowPosition(100, 100);   
    glutInitWindowSize(500, 500);   
    glutCreateWindow("Car");   
    //lightInit();
	glutDisplayFunc(display);
    glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
    return 0;   
}
