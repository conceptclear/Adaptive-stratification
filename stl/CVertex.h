#pragma once

#include <iostream>
using namespace std;
class CVertex
{
public:
	CVertex(int PointIndex = 0, float Point1 = 0, float Point2 = 0, float Point3 = 0) :m_PointIndex(PointIndex)
	{
		m_Point[0] = Point1;
		m_Point[1] = Point2;
		m_Point[2] = Point3;
	}
	bool operator < (const CVertex &a) const
	{
		//��z,y,x����
		if (a.m_Point[2] < m_Point[2])
			return true;
		else if (a.m_Point[2] == m_Point[2])
		{
			if (a.m_Point[1] < m_Point[1])
				return true;
			else if (a.m_Point[1] == m_Point[1])
			{
				if (a.m_Point[0] < m_Point[0])
					return true;
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}
	friend class STLmodel;
    friend class Octree;
	friend class LessPointIndex; //�Ƚ�PointIndex��С
	friend class LessPointx; //�Ƚ�Pointx��С
	friend class LessPointy; //�Ƚ�Pointy��С
	friend class LessPointz; //�Ƚ�Pointz��С
private:
	int m_PointIndex;  //����������
	float m_Point[3];  //������ά����
};

class LessPointIndex
{
public:
	bool operator()(const CVertex& s1, const CVertex& s2)
	{
		return s1.m_PointIndex < s2.m_PointIndex; //�Ƚ������Ŵ�С
	}
};

class LessPointx
{
public:
	bool operator()(const CVertex& s1, const CVertex& s2)
	{
		return s1.m_Point[0] < s2.m_Point[0]; //�Ƚ�x��С
	}
};

class LessPointy
{
public:
	bool operator()(const CVertex& s1, const CVertex& s2)
	{
		return s1.m_Point[1] < s2.m_Point[1]; //�Ƚ�y��С
	}
};

class LessPointz
{
public:
	bool operator()(const CVertex& s1, const CVertex& s2)
	{
		return s1.m_Point[2] < s2.m_Point[2]; //�Ƚ�z��С
	}
};
