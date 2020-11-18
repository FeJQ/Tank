#include "pch.h"
#include "terrain.h"


//��ͼ
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
drawTerrain:�����ϰ���
x,y:ʵ������
*************************/
void terrain::drawTerrain(int x, int y, DWORD dwRop)
{
	putimage(x, y, &img, dwRop);
}

//�õ����ڵ�ͼ�е��±�
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


//����ϰ���
//p:�ڵ�ͼ�е��±�
//ter:�ϰ���ID,ö������
void terrain::addTerrain(int x, int y, Terrain ter)
{
	point realPos;
	realPos.x = cell * x;
	realPos.y = cell * y;

	switch (ter)
	{
	case �յ�:
		clearrectangle(
			realPos.x,
			realPos.y,
			realPos.x + cell,
			realPos.y + cell
		);
		map[x][y] = Terrain::�յ�;
		break;
	case ��ש:	map[x][y] = Terrain::��ש; break;
	case ��ש:	map[x][y] = Terrain::��ש; break;
	case ����:	map[x][y] = Terrain::����; break;
	case ɭ��:	map[x][y] = Terrain::ɭ��; break;
	case ��Ӫ:map[x][y] = Terrain::��Ӫ; break;
	case ռλ��:map[x][y] = Terrain::ռλ��; break;
	default:break;
	}
	reDraw(x, y);
}

/********************************
reDraw:���»���
x,y:��ͼ�±�
********************************/
void terrain::reDraw(int x, int y)
{
	Terrain ter = (Terrain)map[x][y];
    terrain t;
	switch (ter)
	{
	case �յ�:
		return;
	case ��ש:

		loadimage(&t.img, _T("IMG/big_terrain/walls.gif"), cell, cell, true);
		break;
	case ��ש:
		loadimage(&t.img, _T("IMG/big_terrain/steel.gif"), cell, cell, true);
		break;
	case ����:
		loadimage(&t.img, _T("IMG/big_terrain/water.gif"), cell, cell, true);
		break;
	case ɭ��:
		loadimage(&t.img, _T("IMG/big_terrain/forest.gif"), cell, cell, true);
		break;
	case ��Ӫ:
		loadimage(&t.img, _T("IMG/big_terrain/camp0.gif"), cell * 2 + 5, cell * 2 + 5, true);
		break;
	case �ñ�Ӫ:
		loadimage(&t.img, _T("IMG/big_terrain/camp1.gif"), cell * 2 + 5, cell * 2 + 5, true);
	case ռλ��:
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
	case �յ�:
		loadimage(&t.img, _T(""), cell*2, cell*2, true);
		break;
	case ��ש:
		loadimage(&t.img, _T("IMG/big_terrain/walls.gif"), cell*2, cell*2, true);
		break;
	case ��ש:
		loadimage(&t.img, _T("IMG/big_terrain/steel.gif"), cell*2, cell*2, true);
		break;
	case ����:
		loadimage(&t.img, _T("IMG/big_terrain/water.gif"), cell*2, cell*2, true);
		break;
	case ɭ��:
		loadimage(&t.img, _T("IMG/big_terrain/forest.gif"), cell*2, cell*2, true);
		break;
	}
	t.drawTerrain(x, y);
}

/*********************
����������ͼ
*********************/
void terrain::drawMap()
{
	map[0][0] = �յ�;
	map[0][1] = �յ�;
	map[1][0] = �յ�;
	map[1][1] = �յ�;

	map[SCREEN_WIDTH / cell / 2 - 1][0] = �յ�;
	map[SCREEN_WIDTH / cell / 2 - 1][1] = �յ�;
	map[SCREEN_WIDTH / cell / 2][0] = �յ�;
	map[SCREEN_WIDTH / cell / 2][1] = �յ�;

	map[SCREEN_WIDTH / cell - 2][0] = �յ�;
	map[SCREEN_WIDTH / cell - 2][1] = �յ�;
	map[SCREEN_WIDTH / cell - 1][0] = �յ�;
	map[SCREEN_WIDTH / cell - 1][1] = �յ�;

	map[SCREEN_WIDTH / cell / 2 - 1][SCREEN_HEIGHT / cell - 2] = ��Ӫ;
	map[SCREEN_WIDTH / cell / 2 - 1][SCREEN_HEIGHT / cell - 1] = ��Ӫ����;
	map[SCREEN_WIDTH / cell / 2][SCREEN_HEIGHT / cell - 2] = ��Ӫ����;
	map[SCREEN_WIDTH / cell / 2][SCREEN_HEIGHT / cell - 1] = ��Ӫ����;
	for (int x = 0; x < SCREEN_WIDTH / cell; x++)
	{
		for (int y = 0; y < SCREEN_HEIGHT / cell; y++)
		{
			if (map[x][y] != �յ�)
			{
				reDraw(x, y);
			}
		}
	}
}


/***************************
terrain_clay:��ש�๹�캯��
***************************/
terrain_clay::terrain_clay(int x, int y)
{
	loadimage(&img, _T("IMG/big_terrain/walls.gif"), this->width, this->high, true);
	addTerrain(x, y, Terrain::��ש);
}

terrain_clay::~terrain_clay()
{
}


/***************************
terrain_gold:��ש�๹�캯��
***************************/
terrain_gold::terrain_gold(int x, int y)
{
	loadimage(&img, _T("IMG/big_terrain/steel.gif"), this->width, this->high, true);
	addTerrain(x, y, Terrain::��ש);
}

terrain_gold::~terrain_gold()
{
}


/***************************
terrain_river:�����๹�캯��
***************************/
terrain_river::terrain_river(int x, int y)
{
	loadimage(&img, _T("IMG/big_terrain/water.gif"), this->width, this->high, true);
	addTerrain(x, y, Terrain::����);
}

terrain_river::~terrain_river()
{
}

/***************************
terrain_forest:ɭ���๹�캯��
***************************/
terrain_forest::terrain_forest(int x, int y)
{
	loadimage(&img, _T("IMG/big_terrain/forest.gif"), this->width, this->high, true);
	addTerrain(x, y, Terrain::ɭ��);
}

terrain_forest::~terrain_forest()
{
}

/********************************
terrain_Basecamp:��Ӫ�๹�캯��
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
	addTerrain(x, y, Terrain::��Ӫ);
}

terrain_basecamp::~terrain_basecamp()
{
}
