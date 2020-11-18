#pragma once
#include "tank.h"
#include <vector>
#include "point.h"
#include <time.h>
using namespace std;

//̹���б�
extern vector<tank*> tanks;
//����̹���б�
extern vector<tank*> tborn;
//��ը�����б�
extern vector<point> boom;
//��Ϸ�Ƿ����
extern bool isGameOver;
//�Ƿ�����Զ����ͼ
extern bool isCustomMap ;

//��Ϸ�Ƿ����
extern bool isGameOver;
//��ǰ�ؿ�
extern int currLv;
//�����ߴ�
extern int  animate ;
//����һ������Ҫ�ķ���
extern int const firstPassScore;
//��ǰ�ؿ���������Ҫ�ķ���
extern int  passScore ;
//ÿ��һ��,�������������������
extern int const increaseScore ;

//�ܷ�(P1+P2)
extern int totalScore;

//�Ƿ����
extern bool isPass;
extern clock_t time1;
//̹���б�
extern vector<tank*> tanks;

//����̹���б�
extern vector<tank*> tborn;

//��ը�����б�
extern vector<point> boom;

//�浵��Ϣ
extern bool isShow_SWRITEMsg;
extern clock_t cwrtie1, cwrite2;

extern bool isTwo;

class game
{
public:
	game();
	~game();
	//������Ϸ
	void start();
protected:
	//������Ϸ
	void load(int option);
	//��ʼ��Ϸ
	void play();
	//�Զ����ͼ
	void customMap();
	//��ʾ�ؿ���Ϣ
	void showStage();
	//��Ϸ����
	 void gameOver(bool isShow=true);
};

