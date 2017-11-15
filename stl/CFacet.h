#pragma once
#include <iostream>
using namespace std;

class CFacet
{
public:
	bool operator < (const CFacet &a) const
	{
		//�������ŴӴ�С����
		return a.m_FacetIndex < m_FacetIndex;
	}
	friend class STLmodel;
    friend class Octree;
private:
	int m_FacetIndex; //���������
	int PointIndex[3];  //������Ƭ���������������
	int EdgeIndex[3];  //������Ƭ�����ߵ�������
	int FacetIndex[3];  //��������������Ƭ
	float m_Normal[3];  //������Ƭ�ķ�����
};
