#include "STLmodel.h"
#include "Octree/Octree.h"
#define PI 3.1415926
#include <cmath>
int WinWidth;
int WinHeight;
STLmodel p;
Octree tree("0");
static int oldmy=-1,oldmx=-1;
static int angle=90;
static float heightz=0.0f;
static int depth = 7;
void drawSTL(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    p.setperspective(sin(angle*PI/180),cos(angle*PI/180),heightz,0,0,0,0,0,1);
	p.drawSTL();
    p.drawAABB();
    glTranslatef(p.xmin(),p.ymin(),p.zmin());
    glScalef((p.xmax()-p.xmin())/pow(2,depth-1),(p.ymax()-p.ymin())/pow(2,depth-1),(p.zmax()-p.zmin())/pow(2,depth-1));
    tree.Traverse();
//	p.drawsliceequalllayers(30);
	//p.drawslicefacet();
    glutSwapBuffers();
}
void Reshape(int w, int h)
{
	WinWidth = w;
	WinHeight = h;
	// //改变显示区域，起始位置为客户端窗口左下角（非坐标原点）
	glViewport(0, 0, w, h);

	// 开启更新深度缓冲区的功能
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//宽高比改为当前值，视线区域与屏幕大小一致；
	gluPerspective(45, 1.0*WinWidth / WinHeight, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

void LeftMousePick( int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
            oldmx=x,oldmy=y;
    }
}

void onMouseMove( int x,int y)
{
    angle+=x-oldmx;
    heightz+=0.03f*(y-oldmy);
    oldmx=x,oldmy=y;
}

int main(int argc, char *argv[])
{
    if(argc<3)
    {
        cout<<"Please Input the file address and the depth"<<endl;
        return -1;
    }
	p.ReadSTLFile(argv[1]);//读取地址
    depth = atoi(argv[2]);
    cout<<"xmax:"<<p.xmax()<<"\n"<<"xmin:"<<p.xmin()<<"\n"<<"ymax:"<<p.ymax()<<"\n"<<"ymin:"<<p.ymin()<<"\n"<<"zmax:"<<p.zmax()<<"\n"<<"zmin:"<<p.zmin()<<endl;
//	p.sliceequalllayers(30);
//	p.slicefacet(90);
	tree.MakeOctree(depth);
    tree.PointToOctree(p.m_VectorPoint,p.xmax(),p.xmin(),p.ymax(),p.ymin(),p.zmax(),p.zmin());
//    tree.EdgeToOctree(p.m_VectorEdge,p.m_VectorPoint,p.xmax(),p.xmin(),p.ymax(),p.ymin(),p.zmax(),p.zmin());
    tree.FacetToOctree(p.m_VectorFacet,p.m_VectorPoint,p.xmax(),p.xmin(),p.ymax(),p.ymin(),p.zmax(),p.zmin());
    
    WinWidth = 800;
	WinHeight = 800;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE);
	//glutInitWindowPosition(100, 100);
	glutInitWindowSize(WinWidth, WinHeight);
	glutCreateWindow("ReadSTL");

	glEnable(GL_DEPTH_TEST);
	glutReshapeFunc(Reshape);
	glutDisplayFunc(drawSTL);
    glutIdleFunc(drawSTL);
    glutMouseFunc(LeftMousePick);
    glutMotionFunc(onMouseMove);
	glutMainLoop();
	return 0;
}

