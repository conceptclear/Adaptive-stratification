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
	bool ReadASCII(const char *cfilename);//��ȡASCII���ʽ
	bool ReadBinary(const char *cfilename);//��ȡ��������ʽ
	bool ReadSTLFile(const char *cfilename);//��ȡSTL�ļ�����
	void drawSTL(void);
	bool slice(float z); //��Ƭ����
	void drawslice(float z); //������Ƭ
	void setperspective(double eyex,double eyey,double eyez,double centrex,double centrey,double centrez,double upx,double upy,double upz); //�����ӽ�
	bool sliceequalllayers(int layernumber); //�Ȳ����Ƭ
	void drawsliceequalllayers(int layernumber); //���ƵȲ����Ƭ
	bool slicefacet(unsigned long layernumber); //����ĳһ��ı�����Ƭ
	void drawslicefacet(void); //���Ʊ�����
    void drawAABB(void); //draw AABB box
    void VoxelizePoint(void); //voxelize the point
    float xmax(void); //return x_max
    float ymax(void); //return y_max
    float zmax(void); //return z_max
    float xmin(void); //return x_min
    float ymin(void); //return y_min
    float zmin(void); //return z_min
	vector<CVertex> m_VectorPoint; //���������vector����
	vector<CEdge> m_VectorEdge; //�����ߵ�vector����
	vector<CFacet> m_VectorFacet; //�������vector����
private:
	set<CVertex> m_SetPoint; //���������set����
	set<CEdge> m_SetEdge; //�����ߵ�set����
	CFacet m_Facet; //����CFacet����
	vector<vector<point> > z_point; //���������������
	vector<vector<vector<point> > > slicingdata; //���������������
	vector<set<int> > slicefacetnumber; //����������Ƭ�ŵ�����

	//���귶Χ
	float x_max;
	float x_min;
	float y_max;
	float y_min;
	float z_max;
	float z_min;
};
