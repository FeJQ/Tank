#pragma once
#include "tank.h"
#include <vector>
#include "point.h"
#include <time.h>
using namespace std;

//坦克列表
extern vector<tank*> tanks;
//生成坦克列表
extern vector<tank*> tborn;
//爆炸任务列表
extern vector<point> boom;
//游戏是否结束
extern bool isGameOver;
//是否存在自定义地图
extern bool isCustomMap ;

//游戏是否结束
extern bool isGameOver;
//当前关卡
extern int currLv;
//动画尺寸
extern int  animate ;
//过第一关所需要的分数
extern int const firstPassScore;
//当前关卡过关所需要的分数
extern int  passScore ;
//每加一关,过关所需分数的增长数
extern int const increaseScore ;

//总分(P1+P2)
extern int totalScore;

//是否过关
extern bool isPass;
extern clock_t time1;
//坦克列表
extern vector<tank*> tanks;

//生成坦克列表
extern vector<tank*> tborn;

//爆炸任务列表
extern vector<point> boom;

//存档消息
extern bool isShow_SWRITEMsg;
extern clock_t cwrtie1, cwrite2;

extern bool isTwo;

class game
{
public:
	game();
	~game();
	//进入游戏
	void start();
protected:
	//加载游戏
	void load(int option);
	//开始游戏
	void play();
	//自定义地图
	void customMap();
	//显示关卡信息
	void showStage();
	//游戏结束
	 void gameOver(bool isShow=true);
};

