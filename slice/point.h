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
	float x, y; //ÿһ���ϵ������x��y
	//һ���պϵ������ߣ������ӵ�������ƬҲ�����������ģ���ȥֻ�ж���ͱ����غϵ��������ÿ��������Ƭ��ƽ��Ľ����Ϊ�������������������湲���ڼ���������Լ�һ����
	int edgenumber; //�ߺ�
};
