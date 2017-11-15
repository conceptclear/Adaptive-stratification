#pragma once

#include "stl/CVertex.h"
#include "stl/CEdge.h"
#include "stl/CFacet.h"
#include "slice/point.h"
#include <string>
#include <fstream>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>

class STLmodel
{
public:
	bool ReadASCII(const char *cfilename);//读取ASCII码格式
	bool ReadBinary(const char *cfilename);//读取二进制形式
	bool ReadSTLFile(const char *cfilename);//读取STL文件数据
	void drawSTL(void);
	bool slice(float z); //切片函数
	void drawslice(float z); //绘制切片
	void setperspective(double eyex,double eyey,double eyez,double centrex,double centrey,double centrez,double upx,double upy,double upz); //设置视角
	bool sliceequalllayers(int layernumber); //等层厚切片
	void drawsliceequalllayers(int layernumber); //绘制等层厚切片
	bool slicefacet(unsigned long layernumber); //计算某一层的被切面片
	void drawslicefacet(void); //绘制被切面
    void drawAABB(void); //draw AABB box
    void VoxelizePoint(void); //voxelize the point
    float xmax(void); //return x_max
    float ymax(void); //return y_max
    float zmax(void); //return z_max
    float xmin(void); //return x_min
    float ymin(void); //return y_min
    float zmin(void); //return z_min
	vector<CVertex> m_VectorPoint; //声明顶点的vector容器
	vector<CEdge> m_VectorEdge; //声明边的vector容器
	vector<CFacet> m_VectorFacet; //声明面的vector容器
private:
	set<CVertex> m_SetPoint; //声明顶点的set容器
	set<CEdge> m_SetEdge; //声明边的set容器
	CFacet m_Facet; //声明CFacet变量
	vector<vector<point> > z_point; //声明轮廓点的容器
	vector<vector<vector<point> > > slicingdata; //声明多层轮廓容器
	vector<set<int> > slicefacetnumber; //声明被切面片号的容器

	//坐标范围
	float x_max;
	float x_min;
	float y_max;
	float y_min;
	float z_max;
	float z_min;
};
