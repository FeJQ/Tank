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
	黑色,
	蓝色,
	绿色,
	浅绿色,
	红色,
	紫色,
	黄色,
	白色,
	灰色,
	淡蓝色,
	淡绿色,
	淡浅绿色,
	淡红色,
	淡紫色,
	淡黄色,
	亮白色
};


static class Tool
{
public:
	Tool();
	~Tool();
	static	void setChar(short x, short y, WORD backColor, WORD frontColor, double mode);
	//打印字符
	static	void putChar(short x, short y, WORD backColor = Color::黑色, WORD frontColor = Color::亮白色, double mode = 1);
	static	void putChar(short x, short y, char*str, WORD backColor = Color::黑色, WORD frontColor = Color::亮白色, double mode = 1);
	//十六进制转二进制
	static	void HextoBin(int num, string &str);
	//检测键盘输入
	static int waitKey();
	//检测按键状态(是否被按下)
	static  bool getKeyState(int key);
	//制作关卡
	static void makeLevels();
	//加载关卡
	static bool loadLevels(int lv=1);
	//存档
	static bool writeData();
	//读档
	static bool readData(bool isLoad);
	//播放音效
	static void sound(int soundNumber);
};

