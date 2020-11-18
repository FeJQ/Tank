#pragma once
#include "direction.h"
#include <vector>
#include "bullet.h"
#include <time.h>
#include "tankType.h"
#include "terrain.h"
#include <Windows.h>
#include "Tool.h"
#include "TankArchiveStruct.h"
#define STEP 2



using namespace std;
const int tank_terrain_distance = 1;

const int tank_model = cell- tank_terrain_distance-4;


//坦克基类
class tank
{
public:
	tank();
	virtual ~tank();

	//是否开启子弹追踪
	bool isEnableAutoFind;
	//子弹clock
	clock_t tb_1, tb_2;
	//坦克clock
	clock_t tt_1, tt_2;
	//玩家射击clock
	clock_t ts_1, ts_2;
	//AI射击clock
	clock_t aits_1, aits_2;
	//坦克生成clock
	clock_t cborn1, cborn2;
	//坦克血量
	int m_blood;
	//坦克移动速度
	int m_moveSpeed;
	//子弹速度
	int m_bulletSpeed;
	//射击间隔
	int m_shootInterval;
	//切换跟踪子弹键
	int switchBullet;
	//坦克中心点
	point m_centre;
	//坦克实际模型半径
	int m_model;
	//是否为玩家坦克
	bool isPlayer;
	//坦克类型
	Tank tankType;
	//坦克图形
	IMAGE UpImg, DownImg, LeftImg, RightImg;
	//计分板
	IMAGE scorecard_star0, scorecard_star1, scorecard_star2, scorecard_star3, scorecard_star4, scorecard_star5;
	//子弹颜色
	COLORREF m_bulletColor;
	
	//坦克编号
	int ID;
	//玩家得分

	int score;
	//虚拟按键码
	int upKey;
	int leftKey;
	int downKey;
	int rightKey;
	int shootKey;
	//坦克在当前方向剩余步数
	int step;
	//另一个方向
	Direction d;
	//更新分数
	void updateScore(int player);
	//改变方向
	virtual void changeDir(Direction dir);

	//坦克移动
	virtual void move(Direction dir);
	//子弹队列
	vector<bullet> m_bulletList;
	//发射子弹
	virtual void shoot(bool isAutoFind);
	//绘制子弹
	virtual void drawBullet(bullet b);
	//擦除子弹
	virtual void displayBullet(bullet b);
	
	//子弹移动
	virtual void bulletMove(bullet & b);
	virtual bool bulletMove(bullet & b, POINT p1, POINT p2);
	
	//绘制坦克
	void drawTank();
	void drawTank(point centre);
	//擦除坦克
	void displayTank();
	//构建子弹模型
	void  buildBullet(bullet b, POINT pts[5], int border = 0);
	//被击中
	virtual bool beShooted(bool isPlayerBullet);
	//击中障碍物
	static bool shootTerrain(int x, int y);

	//获取方向
	Direction m_dir();

	//重载赋值运算符
	tank&operator=(tank&t);
	//坦克重生
	void revive();
	//坦克信息拷贝
	void copy(const _STANK& t);
	//移动方向
	Direction dir;
};

//玩家坦克类
class tank_player :public tank
{
	friend class tank;
public:
	tank_player(Tank t);
	~tank_player();
private:
	tank_player();
};


//AI坦克类
class tank_computer :public tank
{
public:
	tank_computer(Tank t);
	~tank_computer();
private:
	tank_computer();
};