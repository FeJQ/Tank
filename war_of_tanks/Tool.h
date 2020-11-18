#pragma once
#include <Windows.h>
#include <string>
#include "terrain.h"
#include <time.h>
#include "direction.h"
#include "bullet.h"
#include "tankType.h"
#include "tank.h"
#include "point.h"
using namespace std;
enum MessageBoxButtons
{
	OK,
	OKCancel,
	RetryCancel,
	YesNo
};
enum Color
{
	��ɫ,
	��ɫ,
	��ɫ,
	ǳ��ɫ,
	��ɫ,
	��ɫ,
	��ɫ,
	��ɫ,
	��ɫ,
	����ɫ,
	����ɫ,
	��ǳ��ɫ,
	����ɫ,
	����ɫ,
	����ɫ,
	����ɫ
};


static class Tool
{
public:
	Tool();
	~Tool();
	static	void setChar(short x, short y, WORD backColor, WORD frontColor, double mode);
	//��ӡ�ַ�
	static	void putChar(short x, short y, WORD backColor = Color::��ɫ, WORD frontColor = Color::����ɫ, double mode = 1);
	static	void putChar(short x, short y, char*str, WORD backColor = Color::��ɫ, WORD frontColor = Color::����ɫ, double mode = 1);
	//ʮ������ת������
	static	void HextoBin(int num, string &str);
	//����������
	static int waitKey();
	//��ⰴ��״̬(�Ƿ񱻰���)
	static  bool getKeyState(int key);
	//�����ؿ�
	static void makeLevels();
	//���عؿ�
	static bool loadLevels(int lv=1);
	//�浵
	static bool writeData();
	//����
	static bool readData(bool isLoad);
	//������Ч
	static void sound(int soundNumber);
};

