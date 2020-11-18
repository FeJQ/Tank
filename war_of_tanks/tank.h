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


//̹�˻���
class tank
{
public:
	tank();
	virtual ~tank();

	//�Ƿ����ӵ�׷��
	bool isEnableAutoFind;
	//�ӵ�clock
	clock_t tb_1, tb_2;
	//̹��clock
	clock_t tt_1, tt_2;
	//������clock
	clock_t ts_1, ts_2;
	//AI���clock
	clock_t aits_1, aits_2;
	//̹������clock
	clock_t cborn1, cborn2;
	//̹��Ѫ��
	int m_blood;
	//̹���ƶ��ٶ�
	int m_moveSpeed;
	//�ӵ��ٶ�
	int m_bulletSpeed;
	//������
	int m_shootInterval;
	//�л������ӵ���
	int switchBullet;
	//̹�����ĵ�
	point m_centre;
	//̹��ʵ��ģ�Ͱ뾶
	int m_model;
	//�Ƿ�Ϊ���̹��
	bool isPlayer;
	//̹������
	Tank tankType;
	//̹��ͼ��
	IMAGE UpImg, DownImg, LeftImg, RightImg;
	//�Ʒְ�
	IMAGE scorecard_star0, scorecard_star1, scorecard_star2, scorecard_star3, scorecard_star4, scorecard_star5;
	//�ӵ���ɫ
	COLORREF m_bulletColor;
	
	//̹�˱��
	int ID;
	//��ҵ÷�

	int score;
	//���ⰴ����
	int upKey;
	int leftKey;
	int downKey;
	int rightKey;
	int shootKey;
	//̹���ڵ�ǰ����ʣ�ಽ��
	int step;
	//��һ������
	Direction d;
	//���·���
	void updateScore(int player);
	//�ı䷽��
	virtual void changeDir(Direction dir);

	//̹���ƶ�
	virtual void move(Direction dir);
	//�ӵ�����
	vector<bullet> m_bulletList;
	//�����ӵ�
	virtual void shoot(bool isAutoFind);
	//�����ӵ�
	virtual void drawBullet(bullet b);
	//�����ӵ�
	virtual void displayBullet(bullet b);
	
	//�ӵ��ƶ�
	virtual void bulletMove(bullet & b);
	virtual bool bulletMove(bullet & b, POINT p1, POINT p2);
	
	//����̹��
	void drawTank();
	void drawTank(point centre);
	//����̹��
	void displayTank();
	//�����ӵ�ģ��
	void  buildBullet(bullet b, POINT pts[5], int border = 0);
	//������
	virtual bool beShooted(bool isPlayerBullet);
	//�����ϰ���
	static bool shootTerrain(int x, int y);

	//��ȡ����
	Direction m_dir();

	//���ظ�ֵ�����
	tank&operator=(tank&t);
	//̹������
	void revive();
	//̹����Ϣ����
	void copy(const _STANK& t);
	//�ƶ�����
	Direction dir;
};

//���̹����
class tank_player :public tank
{
	friend class tank;
public:
	tank_player(Tank t);
	~tank_player();
private:
	tank_player();
};


//AI̹����
class tank_computer :public tank
{
public:
	tank_computer(Tank t);
	~tank_computer();
private:
	tank_computer();
};