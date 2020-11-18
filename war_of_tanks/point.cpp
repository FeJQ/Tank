#include "pch.h"
#include "point.h"

point::point()
{
}

point::point(const point & p) :x(p.x), y(p.y)
{
	this->mark1 = 1;
	this->mark2 = 1;
	this->cboom1 = clock();
}

point::point(POINT p) :x(p.x), y(p.y)
{
	
	this->mark1 = 1;
	this->mark2 = 1;
	this->cboom1 = clock();
}

point::point(short  _x, short  _y)
{
	this->x = _x;
	this->y = _y;
	this->mark1 = 1;
	this->mark2 = 1;
	this->cboom1 = clock();
}

point::point(short int _x, short int _y, int _mark1,int _mark2)
{
	this->x = _x;
	this->y = _y;
	this->mark1 = _mark1;
	this->mark2 = _mark2;
	this->cboom1 = clock();
}


point::~point()
{
}

//拷贝数据
void point::copy(const point & p)
{
	this->cboom1 = p.cboom1;
	this->cboom2 = p.cboom2;
	this->mark1 = p.mark1;
	this->mark2 = p.mark2;
	this->x = p.x;
	this->y = p.y;
}

//重载赋值运算符
point & point::operator=(const point & p)
{
	this->x = p.x;
	this->y = p.y;
	return *this;
}
