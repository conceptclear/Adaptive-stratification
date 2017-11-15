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
		//���ն������������Ƚ�
		//if ((a.PointIndex[0] == PointIndex[0] && a.PointIndex[1] == PointIndex[1]) || (a.PointIndex[0] == PointIndex[1] && a.PointIndex[1] == PointIndex[0]))
		//return false;//��2�����ֱ�ӷ���false
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
	friend class LessEdgeIndex; //�Ƚ�EdgeIndex��С
private:
	int m_EdgeIndex;  //�ߵ�������
	int PointIndex[2];  //���ɱߵ����������������
	int FacetIndex[2];  //�ߵ������ڽ�������Ƭ������
};

class LessEdgeIndex
{
public:
	bool operator()(const CEdge& s1, const CEdge& s2)
	{
		return s1.m_EdgeIndex < s2.m_EdgeIndex; //�Ƚ������Ŵ�С
	}
};
