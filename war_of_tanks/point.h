#pragma once
#include <Windows.h>
#include <time.h>
class point
{
public:
	point();
	point(const point &p); /****************���ƹ����ת������*************/
	point(POINT p);
	point(short  _x,short  _y);
	point(short int _x, short int _y,int _mark, int _mark2);
	//���ظ�ֵ�����
	point & operator=(const point& p);
	 ~point();
	//����
	int x;
	int y;
	//���1(��ը���)
	int mark1;
	//���2(���ɱ��)
	int mark2;
	//��ըclock
	clock_t cboom1, cboom2;
	//����
	void copy(const point & p);
	
};

