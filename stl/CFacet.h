#pragma once
#include <iostream>
using namespace std;

class CFacet
{
public:
	bool operator < (const CFacet &a) const
	{
		//按索引号从大到小排列
		return a.m_FacetIndex < m_FacetIndex;
	}
	friend class STLmodel;
    friend class Octree;
private:
	int m_FacetIndex; //面的索引号
	int PointIndex[3];  //构成面片三个顶点的索引号
	int EdgeIndex[3];  //构成面片三条边的索引号
	int FacetIndex[3];  //相邻三个三角面片
	float m_Normal[3];  //三角面片的法向量
};
