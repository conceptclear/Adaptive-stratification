#pragma once

#include <iostream>
using namespace std;

class point
{
public:
	point(float _x = 0, float _y = 0, int number = 0)
	{
		x = _x;
		y = _y;
		edgenumber = number;
	}
	friend class STLmodel;
private:
	float x, y; //每一层上点的坐标x，y
	//一个闭合的轮廓线，所连接的三角面片也是依次相连的，除去只有顶点和边线重合的情况，则每个三角面片与平面的交点必为两个，且与另外两个面共享，在计数中则可以记一个点
	int edgenumber; //边号
};
