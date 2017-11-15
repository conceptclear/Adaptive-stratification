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
		//按z,y,x排序
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
	friend class LessPointIndex; //比较PointIndex大小
	friend class LessPointx; //比较Pointx大小
	friend class LessPointy; //比较Pointy大小
	friend class LessPointz; //比较Pointz大小
private:
	int m_PointIndex;  //顶点索引号
	float m_Point[3];  //顶点三维坐标
};

class LessPointIndex
{
public:
	bool operator()(const CVertex& s1, const CVertex& s2)
	{
		return s1.m_PointIndex < s2.m_PointIndex; //比较索引号大小
	}
};

class LessPointx
{
public:
	bool operator()(const CVertex& s1, const CVertex& s2)
	{
		return s1.m_Point[0] < s2.m_Point[0]; //比较x大小
	}
};

class LessPointy
{
public:
	bool operator()(const CVertex& s1, const CVertex& s2)
	{
		return s1.m_Point[1] < s2.m_Point[1]; //比较y大小
	}
};

class LessPointz
{
public:
	bool operator()(const CVertex& s1, const CVertex& s2)
	{
		return s1.m_Point[2] < s2.m_Point[2]; //比较z大小
	}
};
