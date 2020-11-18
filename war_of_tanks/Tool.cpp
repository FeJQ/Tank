#include "pch.h"
#include "Tool.h"
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <iostream>
#include "terrain.h"
#include <vector>
#include  "tank.h"
#include "game.h"
#include "tankType.h"
#include "TankArchiveStruct.h"
#pragma comment(lib,"winmm.lib")
using namespace std;


Tool::Tool()
{
}


Tool::~Tool()
{
}
void Tool::setChar(short x, short y, WORD backColor, WORD frontColor, double mode)
{
	backColor &= 0xF;
	frontColor &= 0xF;
	backColor <<= 4;
	int color = backColor | frontColor;
	if (mode != 1 && mode != 2 && mode != 0.5) return;
	COORD pos = { x * 2 / mode,y };
	HANDLE hOutStd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutStd, pos);
	SetConsoleTextAttribute(hOutStd, color);
}
void Tool::putChar(short x, short y, WORD backColor, WORD frontColor, double mode)
{
	setChar(x, y, backColor, frontColor, mode);
}
void Tool::putChar(short x, short y, char*str, WORD backColor, WORD frontColor, double mode)
{
	setChar(x, y, backColor, frontColor, mode);
	printf(str);
}

void Tool::HextoBin(int num, string &str)
{
	int remainder;
	char buf[16][5] = { "0000","0001","0010","0011",\
						"0100","0101","0110","0111",\
						"1000","1001","1010","1011",\
						"1100","1101","1110","1111" };
	if (0 == num)
		return;

	remainder = num % 16;
	HextoBin(num >> 4, str);
	str += buf[remainder];
	//printf("%s ", buf[remainder]);
}
//检测键盘输入
int Tool::waitKey()
{
	if (_kbhit())
		return _getch();
	return 0;
}
bool  Tool::getKeyState(int key)
{
	//bool state = false;	
	if (::GetKeyState(key) < 0)
	{
		return true;
	}
	return false;
}

/*********************
功能:制作关卡
*********************/
void Tool::makeLevels()
{
	//供写使用，文件不存在则创建，存在则清空原内容
	ofstream f("MAP/5.data", ios::out);
	for (int i = 0; i < SCREEN_WIDTH / cell; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT / cell; j++)
		{
			f << map[i][j] << " ";
		}
	}
	//关闭文件以使其重新变为可访问，函数一旦调用，原先的流对象就可以被用来打开其它的文件
	f.close();
}



/*********************
功能:加载关卡
返回值:文件是否读取成功
*********************/
bool Tool::loadLevels(int lv)
{
	int c;
	char str[50];
	sprintf_s(str, sizeof(str), "MAP/%d.data", lv);
	ifstream f(str);
	if (f.is_open())
	{
		for (int i = 0; i < SCREEN_WIDTH / cell; i++)
		{
			for (int j = 0; j < SCREEN_HEIGHT / cell; j++)
			{
				if (!f.eof())
				{
					//f >> c;
					f >> map[i][j];
				}
			}
		}
		//关闭文件以使其重新变为可访问，函数一旦调用，原先的流对象就可以被用来打开其它的文件
		f.close();
		return true;
	}
	return false;
}



/********************
存档
********************/
bool Tool::writeData()
{
	_SWRITE wfile;
	for (int i = 0; i < boom.size(); i++)
	{
		if (i == _countof(wfile.tboom))
			break;
		point p;
		p.copy(boom[i]);
		wfile.tboom[i].copy(p);
	}
	wfile.s_currLv = currLv;
	wfile.s_isCustomMap = isCustomMap;
	wfile.s_isGameOver = isGameOver;
	wfile.s_isPass = isPass;
	wfile.s_isTwo = isTwo;
	wfile.tankCount = tanks.size();
	wfile.bornCount = tborn.size();
	wfile.boomCount = boom.size();
	for (int i = 0; i < SCREEN_WIDTH / cell; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT / cell; j++)
		{
			wfile.s_map[i][j] = map[i][j];
		}
	}
	wfile.s_passScore = passScore;

	for (int i = 0; i < tanks.size(); i++)
	{
		if (i == _countof(wfile.ttank))
			break;
		_STANK t;
		t.copy(tanks[i]);
		wfile.ttank[i] = t;
	}
	for (int i = 0; i < tborn.size(); i++)
	{
		if (i == _countof(wfile.tboom))
			break;
		_STANK t;
		t.copy(tborn[i]);
		wfile.tborn[i] = t;
	}
	wfile.s_totalScore = totalScore;
	//供写使用，文件不存在则创建，存在则清空原内容
	ofstream f("MAP/archive.data", ios::out | ios_base::binary);
	f.write(reinterpret_cast<char *>(&wfile), sizeof(wfile));
	//关闭文件以使其重新变为可访问，函数一旦调用，原先的流对象就可以被用来打开其它的文件
	f.close();
	return true;
}

/*******************
读档
*******************/
bool Tool::readData(bool isLoad)
{
	//static _SWRITE wfile;
	_SWRITE wfile;
	ifstream f("MAP/archive.data", ios_base::in | ios_base::binary);
	if (!f)
		return false;

	f.read(reinterpret_cast<char *>(&wfile), sizeof(wfile));
	f.close();
	if (!isLoad)
	{
		return true;
	}
	for (int i = 0; i < wfile.boomCount; i++)
	{
		point p;
		p.copy(boom[i]);
		boom.push_back(p);
	}
	currLv = wfile.s_currLv;
	isCustomMap = wfile.s_isCustomMap;
	isGameOver = wfile.s_isGameOver;
	isPass = wfile.s_isPass;
	isTwo = wfile.s_isTwo;
	for (int i = 0; i < SCREEN_WIDTH / cell; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT / cell; j++)
		{
			map[i][j] = wfile.s_map[i][j];
		}
	}
	passScore = wfile.s_passScore;
	for (int i = 0; i < wfile.tankCount; i++)
	{
		tank *t = nullptr;
		if (wfile.ttank[i].isPlayer)
		{
			t = new tank_player(wfile.ttank[i].tankType);
		}
		else
		{
			t = new tank_computer(wfile.ttank[i].tankType);
		}
		t->copy(wfile.ttank[i]);
		tanks.push_back(t);
	}
	for (int i = 0; i < wfile.bornCount; i++)
	{
		tank *t = nullptr;
		if (wfile.tborn[i].isPlayer)
		{
			t = new tank_player(wfile.tborn[i].tankType);
		}
		else
		{
			t = new tank_computer(wfile.tborn[i].tankType);
		}
		t->copy(wfile.tborn[i]);
		tborn.push_back(t);
	}
	totalScore = wfile.s_totalScore;
	f.close();
	return true;
}

void _STANK::copy(tank*t)
{
	this->aits_1 = t->aits_1;
	this->aits_2 = t->aits_2;
	this->cborn1 = t->cborn1;
	this->cborn2 = t->cborn2;
	this->d = t->d;
	this->dir = t->dir;

	this->downKey = t->downKey;
	this->ID = t->ID;
	this->isPlayer = t->isPlayer;

	this->leftKey = t->leftKey;
	this->m_blood = t->m_blood;

	this->bulletCount = t->m_bulletList.size();
	for (int i = 0; i < t->m_bulletList.size(); i++)
	{
		if (i == _countof(this->m_bulletList))
			break;
		this->m_bulletList[i] = t->m_bulletList[i];
	}
	this->m_bulletSpeed = t->m_bulletSpeed;
	this->m_centre = t->m_centre;
	this->m_model = t->m_model;
	this->m_moveSpeed = t->m_moveSpeed;
	this->m_shootInterval = t->m_shootInterval;

	this->rightKey = t->rightKey;
	this->score = t->score;

	this->upKey = t->upKey;
	this->shootKey = t->shootKey;
	this->step = t->step;
	this->tankType = t->tankType;
	this->tb_1 = t->tb_1;
	this->tb_2 = t->tb_2;
	this->ts_1 = t->ts_1;
	this->ts_2 = t->ts_2;
	this->tt_1 = t->tt_1;
	this->tt_2 = t->tt_2;

	this->upKey = t->upKey;
}

_STANK & _STANK::operator=(const _STANK & t)
{
	for (int i = 0; i < t.bulletCount; i++)
	{
		this->m_bulletList[i] = t.m_bulletList[i];
	}
	this->aits_1 = t.aits_1;
	this->aits_2 = t.aits_2;
	this->cborn1 = t.cborn1;
	this->cborn2 = t.cborn2;
	this->d = t.d;
	this->dir = t.dir;

	this->ID = t.ID;
	this->isPlayer = t.isPlayer;

	this->m_blood = t.m_blood;

	this->m_bulletSpeed = t.m_bulletSpeed;
	this->m_centre.copy(t.m_centre);
	this->m_model = t.m_model;
	this->m_moveSpeed = t.m_moveSpeed;
	this->m_shootInterval = t.m_shootInterval;

	this->leftKey = t.leftKey;
	this->downKey = t.downKey;
	this->upKey = t.upKey;
	this->rightKey = t.rightKey;
	this->shootKey = t.shootKey;

	this->score = t.score;
	this->step = t.step;

	this->tankType = t.tankType;
	this->tb_1 = t.tb_1;
	this->tb_2 = t.tb_2;
	this->ts_1 = t.ts_1;
	this->ts_2 = t.ts_2;
	this->tt_1 = t.tt_1;
	this->tt_2 = t.tt_2;

	return*this;
}

//播放音效
void Tool::sound(int soundNumber)
{
	switch (soundNumber)
	{
	case 0:PlaySoundA("sound\\start.wav", NULL, SND_ASYNC | SND_NODEFAULT); break;
	case 1:PlaySoundA("sound\\bin.wav", NULL, SND_ASYNC | SND_NODEFAULT); break;
	case 2:PlaySoundA("sound\\OK.wav", NULL, SND_ASYNC | SND_NODEFAULT); break;
	case 3:PlaySoundA("sound\\shoot.wav", NULL, SND_ASYNC | SND_NODEFAULT); break;
	case 4:PlaySoundA("sound\\bomb.wav", NULL, SND_ASYNC | SND_NODEFAULT); break;
	case 5:PlaySoundA("sound\\fail.wav", NULL, SND_ASYNC | SND_NODEFAULT); break;
	default:break;
	}
}