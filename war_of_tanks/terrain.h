#pragma once
#include "point.h"
#include <easyx.h>
#include "terrainType.h"
#include "consoleGraphics.h"
#define cell 25
//��ͼ��Ԫʵ�ʴ�С

//��ͼ
extern int map[SCREEN_WIDTH / cell][SCREEN_HEIGHT / cell];


class terrain
{
public:
	terrain();
	virtual ~terrain();
	//�ϰ�����
	int width;
	//�ϰ���߶�
	int high;
	//�ϰ������Ͻ�����
	point origin;
	//�ϰ���ͼ��ָ��
	IMAGE  img;
	//�õ����ڵ�ͼ�е��±�
	static point getPointInMap(point p);
	static point getPointInMap(POINT &p);
	//����ϰ���(��ͼ�±�)
	static void addTerrain(int x, int y, Terrain ter);
	//���»���
	static  void reDraw(int x, int y);
	static void reDraw(int x, int y, Terrain t);
		//����������ͼ
		static void drawMap();
private:
	//�����ϰ���
	void drawTerrain(int x, int y, DWORD dwRop = SRCCOPY);


};

//��ש��
class terrain_clay :public terrain
{
public:
	terrain_clay(int x, int y);
	~terrain_clay();
};

//��ש��
class terrain_gold :public terrain
{
public:
	terrain_gold(int x, int y);
	~terrain_gold();
};

//����
class terrain_river :public terrain
{
public:
	terrain_river(int x, int y);
	~terrain_river();
};

//ɭ����
class terrain_forest :public terrain
{
public:
	terrain_forest(int x, int y);
	~terrain_forest();
};

//��Ӫ��
class terrain_basecamp :public terrain
{
public:
	terrain_basecamp(int x, int y, bool isAlive = true);
	~terrain_basecamp();
};