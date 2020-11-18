#pragma once
#include "pch.h"
#include "point.h"
#include <time.h>
#include "direction.h"
#include "bullet.h"
#include "tankType.h"
#include "consoleGraphics.h"
#include "terrain.h"

class tank;

struct _STANK
{
	clock_t aits_1;
	clock_t aits_2;
	clock_t cborn1;
	clock_t cborn2;
	Direction d;
	Direction dir;

	int ID;
	bool isPlayer;

	int m_blood;

	int bulletCount;
	bullet m_bulletList[50];

	int m_bulletSpeed;
	point m_centre;
	int m_model;
	int m_moveSpeed;
	int m_shootInterval;

	int leftKey;
	int downKey;
	int upKey;
	int rightKey;
	int shootKey;

	int score;
	int step;

	Tank tankType;
	clock_t tb_1;
	clock_t tb_2;
	clock_t ts_1;
	clock_t ts_2;
	clock_t tt_1;
	clock_t tt_2;

	void copy(tank *t);
	_STANK & operator=(const _STANK &t);
};
//´æµµ½á¹¹Ìå
struct _SWRITE
{
	int s_totalScore;
	int s_isPass;
	int s_currLv;
	bool s_isGameOver;
	int s_passScore;
	bool s_isTwo;
	bool s_isCustomMap;
	int s_map[SCREEN_WIDTH / cell][SCREEN_HEIGHT / cell];
	int tankCount;
	_STANK ttank[50];
	int bornCount;
	_STANK tborn[50];
	int boomCount;
	point tboom[50];
};