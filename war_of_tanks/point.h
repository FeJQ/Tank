#pragma once
#include <Windows.h>
#include <time.h>
class point
{
public:
	point();
	point(const point &p); /****************复制构造和转换构造*************/
	point(POINT p);
	point(short  _x,short  _y);
	point(short int _x, short int _y,int _mark, int _mark2);
	//重载赋值运算符
	point & operator=(const point& p);
	 ~point();
	//坐标
	int x;
	int y;
	//标记1(爆炸标记)
	int mark1;
	//标记2(生成标记)
	int mark2;
	//爆炸clock
	clock_t cboom1, cboom2;
	//拷贝
	void copy(const point & p);
	
};

