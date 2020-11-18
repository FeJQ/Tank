#pragma once
#include "point.h"
#include <easyx.h>
#include "terrainType.h"
#include "consoleGraphics.h"
#define cell 25
//地图单元实际大小

//地图
extern int map[SCREEN_WIDTH / cell][SCREEN_HEIGHT / cell];


class terrain
{
public:
	terrain();
	virtual ~terrain();
	//障碍物宽度
	int width;
	//障碍物高度
	int high;
	//障碍物左上角坐标
	point origin;
	//障碍物图像指针
	IMAGE  img;
	//得到点在地图中的下标
	static point getPointInMap(point p);
	static point getPointInMap(POINT &p);
	//添加障碍物(地图下标)
	static void addTerrain(int x, int y, Terrain ter);
	//重新绘制
	static  void reDraw(int x, int y);
	static void reDraw(int x, int y, Terrain t);
		//绘制整个地图
		static void drawMap();
private:
	//绘制障碍物
	void drawTerrain(int x, int y, DWORD dwRop = SRCCOPY);


};

//土砖类
class terrain_clay :public terrain
{
public:
	terrain_clay(int x, int y);
	~terrain_clay();
};

//金砖类
class terrain_gold :public terrain
{
public:
	terrain_gold(int x, int y);
	~terrain_gold();
};

//河流
class terrain_river :public terrain
{
public:
	terrain_river(int x, int y);
	~terrain_river();
};

//森林类
class terrain_forest :public terrain
{
public:
	terrain_forest(int x, int y);
	~terrain_forest();
};

//大本营类
class terrain_basecamp :public terrain
{
public:
	terrain_basecamp(int x, int y, bool isAlive = true);
	~terrain_basecamp();
};