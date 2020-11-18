#include "pch.h"
#include "terrain.h"


//地图
int map[SCREEN_WIDTH / cell][SCREEN_HEIGHT / cell] = { 0 };

terrain::terrain()
{
	this->width = cell;
	this->high = cell;
}


terrain::~terrain()
{
}


/*************************
drawTerrain:绘制障碍物
x,y:实际坐标
*************************/
void terrain::drawTerrain(int x, int y, DWORD dwRop)
{
	putimage(x, y, &img, dwRop);
}

//得到点在地图中的下标
point terrain::getPointInMap(point p)
{
	point _valp;
	_valp.x = p.x / cell;
	_valp.y = p.y / cell;
	return _valp;
}

point terrain::getPointInMap(POINT &p)
{
	point _valp;
	_valp.x = p.x / cell;
	_valp.y = p.y / cell;
	return _valp;
}


//添加障碍物
//p:在地图中的下标
//ter:障碍物ID,枚举类型
void terrain::addTerrain(int x, int y, Terrain ter)
{
	point realPos;
	realPos.x = cell * x;
	realPos.y = cell * y;

	switch (ter)
	{
	case 空地:
		clearrectangle(
			realPos.x,
			realPos.y,
			realPos.x + cell,
			realPos.y + cell
		);
		map[x][y] = Terrain::空地;
		break;
	case 土砖:	map[x][y] = Terrain::土砖; break;
	case 金砖:	map[x][y] = Terrain::金砖; break;
	case 河流:	map[x][y] = Terrain::河流; break;
	case 森林:	map[x][y] = Terrain::森林; break;
	case 大本营:map[x][y] = Terrain::大本营; break;
	case 占位格:map[x][y] = Terrain::占位格; break;
	default:break;
	}
	reDraw(x, y);
}

/********************************
reDraw:重新绘制
x,y:地图下标
********************************/
void terrain::reDraw(int x, int y)
{
	Terrain ter = (Terrain)map[x][y];
    terrain t;
	switch (ter)
	{
	case 空地:
		return;
	case 土砖:

		loadimage(&t.img, _T("IMG/big_terrain/walls.gif"), cell, cell, true);
		break;
	case 金砖:
		loadimage(&t.img, _T("IMG/big_terrain/steel.gif"), cell, cell, true);
		break;
	case 河流:
		loadimage(&t.img, _T("IMG/big_terrain/water.gif"), cell, cell, true);
		break;
	case 森林:
		loadimage(&t.img, _T("IMG/big_terrain/forest.gif"), cell, cell, true);
		break;
	case 大本营:
		loadimage(&t.img, _T("IMG/big_terrain/camp0.gif"), cell * 2 + 5, cell * 2 + 5, true);
		break;
	case 烂本营:
		loadimage(&t.img, _T("IMG/big_terrain/camp1.gif"), cell * 2 + 5, cell * 2 + 5, true);
	case 占位格:
		return;
	default:
		break;
	}
	t.drawTerrain(x*cell, y*cell);
}
void terrain::reDraw(int x, int y,Terrain ter)
{
	terrain t;
	switch (ter)
	{
	case 空地:
		loadimage(&t.img, _T(""), cell*2, cell*2, true);
		break;
	case 土砖:
		loadimage(&t.img, _T("IMG/big_terrain/walls.gif"), cell*2, cell*2, true);
		break;
	case 金砖:
		loadimage(&t.img, _T("IMG/big_terrain/steel.gif"), cell*2, cell*2, true);
		break;
	case 河流:
		loadimage(&t.img, _T("IMG/big_terrain/water.gif"), cell*2, cell*2, true);
		break;
	case 森林:
		loadimage(&t.img, _T("IMG/big_terrain/forest.gif"), cell*2, cell*2, true);
		break;
	}
	t.drawTerrain(x, y);
}

/*********************
绘制整个地图
*********************/
void terrain::drawMap()
{
	map[0][0] = 空地;
	map[0][1] = 空地;
	map[1][0] = 空地;
	map[1][1] = 空地;

	map[SCREEN_WIDTH / cell / 2 - 1][0] = 空地;
	map[SCREEN_WIDTH / cell / 2 - 1][1] = 空地;
	map[SCREEN_WIDTH / cell / 2][0] = 空地;
	map[SCREEN_WIDTH / cell / 2][1] = 空地;

	map[SCREEN_WIDTH / cell - 2][0] = 空地;
	map[SCREEN_WIDTH / cell - 2][1] = 空地;
	map[SCREEN_WIDTH / cell - 1][0] = 空地;
	map[SCREEN_WIDTH / cell - 1][1] = 空地;

	map[SCREEN_WIDTH / cell / 2 - 1][SCREEN_HEIGHT / cell - 2] = 大本营;
	map[SCREEN_WIDTH / cell / 2 - 1][SCREEN_HEIGHT / cell - 1] = 大本营副本;
	map[SCREEN_WIDTH / cell / 2][SCREEN_HEIGHT / cell - 2] = 大本营副本;
	map[SCREEN_WIDTH / cell / 2][SCREEN_HEIGHT / cell - 1] = 大本营副本;
	for (int x = 0; x < SCREEN_WIDTH / cell; x++)
	{
		for (int y = 0; y < SCREEN_HEIGHT / cell; y++)
		{
			if (map[x][y] != 空地)
			{
				reDraw(x, y);
			}
		}
	}
}


/***************************
terrain_clay:土砖类构造函数
***************************/
terrain_clay::terrain_clay(int x, int y)
{
	loadimage(&img, _T("IMG/big_terrain/walls.gif"), this->width, this->high, true);
	addTerrain(x, y, Terrain::土砖);
}

terrain_clay::~terrain_clay()
{
}


/***************************
terrain_gold:金砖类构造函数
***************************/
terrain_gold::terrain_gold(int x, int y)
{
	loadimage(&img, _T("IMG/big_terrain/steel.gif"), this->width, this->high, true);
	addTerrain(x, y, Terrain::金砖);
}

terrain_gold::~terrain_gold()
{
}


/***************************
terrain_river:河流类构造函数
***************************/
terrain_river::terrain_river(int x, int y)
{
	loadimage(&img, _T("IMG/big_terrain/water.gif"), this->width, this->high, true);
	addTerrain(x, y, Terrain::河流);
}

terrain_river::~terrain_river()
{
}

/***************************
terrain_forest:森林类构造函数
***************************/
terrain_forest::terrain_forest(int x, int y)
{
	loadimage(&img, _T("IMG/big_terrain/forest.gif"), this->width, this->high, true);
	addTerrain(x, y, Terrain::森林);
}

terrain_forest::~terrain_forest()
{
}

/********************************
terrain_Basecamp:大本营类构造函数
********************************/
terrain_basecamp::terrain_basecamp(int x, int y, bool isAlive)
{
	this->width = cell * 2 - 30;
	this->high = cell * 2 - 30;
	if (isAlive)
	{
		loadimage(&img, _T("IMG/big_terrain/camp0.gif"), this->width, this->high, true);
	}
	else
	{
		loadimage(&img, _T("IMG/big_terrain/camp1.gif"), this->width, this->high, true);
	}
	addTerrain(x, y, Terrain::大本营);
}

terrain_basecamp::~terrain_basecamp()
{
}
