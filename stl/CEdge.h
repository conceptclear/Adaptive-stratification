#pragma once

#include <iostream>
using namespace std;
class CEdge
{
public:
	CEdge(int EdgeIndex = 0, int Point1 = 0, int Point2 = 0, int Facet1 = 0, int Facet2 = 0) :m_EdgeIndex(EdgeIndex)
	{
		PointIndex[0] = Point1;
		PointIndex[1] = Point2;
		FacetIndex[0] = Facet1;
		FacetIndex[1] = Facet2;
	}

	bool operator < (const CEdge &a) const
	{
		//按照顶点索引号来比较
		//if ((a.PointIndex[0] == PointIndex[0] && a.PointIndex[1] == PointIndex[1]) || (a.PointIndex[0] == PointIndex[1] && a.PointIndex[1] == PointIndex[0]))
		//return false;//若2者相等直接返回false
		if (a.PointIndex[0] < PointIndex[0])
			return true;
		else if (a.PointIndex[0] == PointIndex[0])
		{
			if (a.PointIndex[1] < PointIndex[1])
				return true;
			else
				return false;
		}
		else
			return false;
	}
	friend class STLmodel;
    friend class Octree;
	friend class LessEdgeIndex; //比较EdgeIndex大小
private:
	int m_EdgeIndex;  //边的索引号
	int PointIndex[2];  //构成边的两个顶点的索引号
	int FacetIndex[2];  //边的两个邻接三角面片索引号
};

class LessEdgeIndex
{
public:
	bool operator()(const CEdge& s1, const CEdge& s2)
	{
		return s1.m_EdgeIndex < s2.m_EdgeIndex; //比较索引号大小
	}
};
