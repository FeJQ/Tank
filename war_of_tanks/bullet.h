#pragma once
#include "point.h"
#include "direction.h"
class bullet
{
public:
	bullet();
	bullet(short int _x, short int _y,Direction _dir, bool _isPlayer);
	bullet(short int _x, short int _y, Direction _dir, bool _isPlayer, bool _isAutoFind);
	~bullet();
	//子弹中心点
	point m_centre;
	//子弹方向
	Direction m_dir;
	//是否为玩家发出的子弹
	bool isPlayer;
	//运算符重载
	bullet& operator=(const bullet &b);
	//是否为跟踪子弹
	bool isAutoFind;
};

