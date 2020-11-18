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
	//�ӵ����ĵ�
	point m_centre;
	//�ӵ�����
	Direction m_dir;
	//�Ƿ�Ϊ��ҷ������ӵ�
	bool isPlayer;
	//���������
	bullet& operator=(const bullet &b);
	//�Ƿ�Ϊ�����ӵ�
	bool isAutoFind;
};

