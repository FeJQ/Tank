#include "pch.h"
#include "game.h"
#include <graphics.h>
#include "consoleGraphics.h"
#include "point.h"
#include "Tool.h"
#include <time.h>
#include "terrain.h"
#include <Windows.h>
#include <windef.h>
#include <stdlib.h>
#define SILVER          0xC0C0C0
using namespace std;
//�Ƿ�����Զ����ͼ
bool isCustomMap = false;

//��Ϸ�Ƿ����
bool isGameOver = false;
//��ǰ�ؿ�
int currLv = 1;
//�����ߴ�
int  animate = 30;
//����һ������Ҫ�ķ���
int const firstPassScore = 4000;
//��ǰ�ؿ���������Ҫ�ķ���
int  passScore = firstPassScore;
//ÿ��һ��,�������������������
int const increaseScore = 400;

//�ܷ�(P1+P2)
int totalScore = 0;

//�Ƿ����
bool isPass = false;
clock_t time1 = clock();
//̹���б�
vector<tank*> tanks;

//����̹���б�
vector<tank*> tborn;

//��ը�����б�
vector<point> boom;

//��ըͼƬ����
IMAGE boom1, boom2, boom3, boom4, boom5;

//̹������ͼƬ����
IMAGE born1, born2, born3, born4;

//�浵��Ϣ
bool isShow_SWRITEMsg = false;
clock_t cwrtie1, cwrite2;

game::game()
{

}

game::~game()
{
}
int maxOption = 0;
bool isTwo = false;
/****************
start:������Ϸ
*****************/
void game::start()
{
	Tool::sound(0);
	boom.clear();
	loadimage(&boom1, _T("IMG/boom/0.gif"), animate, animate, true);
	loadimage(&boom2, _T("IMG/boom/1.gif"), animate, animate, true);
	loadimage(&boom3, _T("IMG/boom/2.gif"), animate, animate, true);
	loadimage(&boom4, _T("IMG/boom/3.gif"), animate, animate, true);
	loadimage(&boom5, _T("IMG/boom/4.gif"), animate, animate, true);

	loadimage(&born1, _T("IMG/star/star0.gif"), animate, animate, true);
	loadimage(&born2, _T("IMG/star/star1.gif"), animate, animate, true);
	loadimage(&born3, _T("IMG/star/star2.gif"), animate, animate, true);
	loadimage(&born4, _T("IMG/star/star3.gif"), animate, animate, true);
	//�����������
	srand(time(NULL));

	//��������
	consoleGraphics::Create();

	//��ҳ����
	IMAGE imgCover;
	int cwidth = 600, cheight = 200;
	loadimage(&imgCover, _T("IMG/cover.png"), cwidth, cheight, true);
	putimage((SCREEN_WIDTH - cwidth) / 2 + 150, 30, &imgCover, SRCINVERT);


	//��ҳ�˵�
	IMAGE imgMenu;
	int mwidth = 160, mheight = 200;
	int option = 1;

	point pos[5] = {};
	pos[0].x = (SCREEN_WIDTH - mwidth) / 2 - 70 + 150;
	pos[0].y = 335;
	pos[1].x = (SCREEN_WIDTH - mwidth) / 2 - 70 + 150;
	pos[1].y = 335 + 55;
	pos[2].x = (SCREEN_WIDTH - mwidth) / 2 - 70 + 150;
	pos[2].y = 335 + 55 * 2;
	pos[3].x = (SCREEN_WIDTH - mwidth) / 2 - 70 + 150;
	pos[3].y = 335 + 55 * 3;
	pos[4].x = (SCREEN_WIDTH - mwidth) / 2 - 70 + 150;
	pos[4].y = 335 + 55 * 4;
	//�����⵽�浵
	if (Tool::readData(false))
	{
		maxOption = 5;
		loadimage(&imgMenu, _T("IMG/Menu1.png"), mwidth, mheight + 55, true);
	}
	else
	{
		maxOption = 4;
		loadimage(&imgMenu, _T("IMG/Menu0.png"), mwidth, mheight, true);
	}
	putimage((SCREEN_WIDTH - mwidth) / 2 + 150, 330, &imgMenu, SRCINVERT);

	//ѡ���ͷ
	IMAGE imgArrows;
	const int awidth = 50, aheight = 25;
	loadimage(&imgArrows, _T("IMG/arrows.png"), awidth, aheight);
	putimage((SCREEN_WIDTH - mwidth) / 2 - 70 + 150, 335, &imgArrows, SRCINVERT);


	while (true)
	{
		int key = Tool::waitKey();
		if (key != 0)
		{
			switch (key)
			{
				//Enter
			case VK_RETURN:
				isTwo = false;
				Tool::sound(2);
				load(option); break;
				//case 224:;
				//W
			case 119:
				if (option != 1)
				{
					Tool::sound(1);
					clearrectangle(pos[option - 1].x, pos[option - 1].y, pos[option - 1].x + awidth, pos[option - 1].y + aheight);
					option--;
					putimage(pos[option - 1].x, pos[option - 1].y, &imgArrows, SRCINVERT);
				}
				break;
				//S
			case 115:
				if (option != maxOption)
				{
					Tool::sound(1);
					clearrectangle(pos[option - 1].x, pos[option - 1].y, pos[option - 1].x + awidth, pos[option - 1].y + aheight);
					option++;
					putimage(pos[option - 1].x, pos[option - 1].y, &imgArrows, SRCINVERT);
				}
				break;
			default:
				break;
			}
		}
	}

	system("pause");

	//���ٻ���
	consoleGraphics::Destroy();
}

//������Ϸ
void game::load(int option)
{

	if (maxOption == 4)
	{
		switch (option)
		{
		case 2:
		{
			//������̹��2
			tank_player *tank_2 = new tank_player(���̹��2);
			tborn.push_back(tank_2);
			isTwo = true;
		}
		case 1:
		{
			//����
			cleardevice();
			//�Ʒְ�
			setfillcolor(SILVER);
			solidrectangle(SCREEN_WIDTH, 0, SCREEN_WIDTH + 300, SCREEN_HEIGHT);

			//������̹��1
			tank_player *tank_1 = new tank_player(���̹��1);
			tborn.push_back(tank_1);
			break;
		}
		case 3:
			//����
			//����
			cleardevice();
			Tool::readData(true);
			break;
		case 4:
			//�Զ����ͼ
			//����
			cleardevice();
			customMap();
			break;
		default:
			break;
		}
	}
	else if (maxOption == 5)
	{
		switch (option)
		{
		case 1:
			//������Ϸ
			Tool::readData(true);

			//����
			cleardevice();


			play();
			break;
		case 3:
		{
			//������̹��2
			tank_player *tank_2 = new tank_player(���̹��2);
			tborn.push_back(tank_2);
			isTwo = true;
		}
		case 2:
		{
			//����
			cleardevice();
			//�Ʒְ�
			setfillcolor(SILVER);
			solidrectangle(SCREEN_WIDTH, 0, SCREEN_WIDTH + 300, SCREEN_HEIGHT);

			//������̹��1
			tank_player *tank_1 = new tank_player(���̹��1);
			tborn.push_back(tank_1);
			break;
		}
		case 4:
			//����
			//����
			cleardevice();
			Tool::readData(true);
			break;
		case 5:
			//�Զ����ͼ
			//����
			cleardevice();
			customMap();
			break;
		default:
			break;
		}
	}
	//���ؼƷְ�
	int high = 20;
	for (int i = tborn.size() - 1; i > -1; i--)
	{
		if (tborn[i]->m_blood == 0) putimage(SCREEN_WIDTH + 20, high, &tborn[i]->scorecard_star0, SRCCOPY);
		if (tborn[i]->m_blood == 1) putimage(SCREEN_WIDTH + 20, high, &tborn[i]->scorecard_star1, SRCCOPY);
		if (tborn[i]->m_blood == 2) putimage(SCREEN_WIDTH + 20, high, &tborn[i]->scorecard_star2, SRCCOPY);
		if (tborn[i]->m_blood == 3) putimage(SCREEN_WIDTH + 20, high, &tborn[i]->scorecard_star3, SRCCOPY);
		if (tborn[i]->m_blood == 4) putimage(SCREEN_WIDTH + 20, high, &tborn[i]->scorecard_star4, SRCCOPY);
		if (tborn[i]->m_blood == 5) putimage(SCREEN_WIDTH + 20, high, &tborn[i]->scorecard_star5, SRCCOPY);
		high += 150;
		tborn[i]->updateScore(tborn[i]->ID);
	}
	play();
}
//�浵��ʾ����
RECT writeRect = { SCREEN_WIDTH + 60,400,SCREEN_WIDTH + 180,440 };
/****************
play:��ʼ��Ϸ
*****************/
void game::play()
{

	isGameOver = false;
	//�Ƿ��������̹��
	bool isborn = true;
	//��������
	totalScore = 0;
	//��ʾ�ؿ�
	showStage();

	if (!isCustomMap)
	{
		//���عؿ�
		Tool::loadLevels(currLv);
	}

	//���ص�ͼ
	terrain::drawMap();
	for (int i = 0; i < tanks.size(); i++)
	{
		tanks[i]->drawTank();
		if (tanks[i]->ID != 0)
		{
			setfillcolor(SILVER);
			solidrectangle(SCREEN_WIDTH, 0, SCREEN_WIDTH + 300, SCREEN_HEIGHT);
			tanks[i]->updateScore(tanks[i]->ID);
			if (tanks[i]->tankType == ���̹��1)
			{
				if (tanks[i]->m_blood == 0) putimage(SCREEN_WIDTH + 20, 20, &tanks[i]->scorecard_star0, SRCCOPY);
				if (tanks[i]->m_blood == 1) putimage(SCREEN_WIDTH + 20, 20, &tanks[i]->scorecard_star1, SRCCOPY);
				if (tanks[i]->m_blood == 2) putimage(SCREEN_WIDTH + 20, 20, &tanks[i]->scorecard_star2, SRCCOPY);
				if (tanks[i]->m_blood == 3) putimage(SCREEN_WIDTH + 20, 20, &tanks[i]->scorecard_star3, SRCCOPY);
				if (tanks[i]->m_blood == 4) putimage(SCREEN_WIDTH + 20, 20, &tanks[i]->scorecard_star4, SRCCOPY);
				if (tanks[i]->m_blood == 5) putimage(SCREEN_WIDTH + 20, 20, &tanks[i]->scorecard_star5, SRCCOPY);
				tanks[i]->updateScore(1);
			}
			if (tanks[i]->tankType == ���̹��2)
			{
				if (tanks[i]->m_blood == 0) putimage(SCREEN_WIDTH + 20, 170, &tanks[i]->scorecard_star0, SRCCOPY);
				if (tanks[i]->m_blood == 1) putimage(SCREEN_WIDTH + 20, 170, &tanks[i]->scorecard_star1, SRCCOPY);
				if (tanks[i]->m_blood == 2) putimage(SCREEN_WIDTH + 20, 170, &tanks[i]->scorecard_star2, SRCCOPY);
				if (tanks[i]->m_blood == 3) putimage(SCREEN_WIDTH + 20, 170, &tanks[i]->scorecard_star3, SRCCOPY);
				if (tanks[i]->m_blood == 4) putimage(SCREEN_WIDTH + 20, 170, &tanks[i]->scorecard_star4, SRCCOPY);
				if (tanks[i]->m_blood == 5) putimage(SCREEN_WIDTH + 20, 170, &tanks[i]->scorecard_star5, SRCCOPY);
				tanks[i]->updateScore(2);
			}

		}
	}
	//Ϊ��ʱ������ʼֵ
	for (size_t i = 0; i < tanks.size(); i++)
	{
		tanks[i]->tb_1 = clock();
		tanks[i]->tt_1 = clock();
		tanks[i]->ts_1 = clock();
	}
	clock_t graphics_control2, graphics_control1 = clock();
	//��Ϸ�������
	while (true)
	{
		try
		{


		BEGIN:
			if (isGameOver)
			{
				animate = 90;
				loadimage(&boom1, _T("IMG/boom/0.gif"), animate, animate, true);
				loadimage(&boom2, _T("IMG/boom/1.gif"), animate, animate, true);
				loadimage(&boom3, _T("IMG/boom/2.gif"), animate, animate, true);
				loadimage(&boom4, _T("IMG/boom/3.gif"), animate, animate, true);
				loadimage(&boom5, _T("IMG/boom/4.gif"), animate, animate, true);
				if (boom.size() == 0)
				{
					Sleep(1000);
					gameOver();
				}
			}
			//�˳������˵�(Esc)
			if (Tool::getKeyState(27))
			{
				//GAMEOVER
				gameOver(false);
			}
			//�浵(M)
			if (Tool::getKeyState(77))
			{
				char ch[20] = { 0 };
				TCHAR str[20];
				if (Tool::writeData())
				{
					strcpy_s(ch, 21, "save successfully!");
				}
				else
				{
					strcpy_s(ch, 21, "fail to save!!");
				}
				for (int i = 0; i < 20; i++)
				{
					str[i] = ch[i];
				}
				settextcolor(WHITE);
				setbkmode(TRANSPARENT);
				drawtext(str, &writeRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				cwrtie1 = clock();
				isShow_SWRITEMsg = true;
			}
			//ɾ���浵��ʾ��Ϣ
			if (isShow_SWRITEMsg)
			{
				cwrite2 = clock();
				if (cwrite2 - cwrtie1 > 3000)
				{
					isShow_SWRITEMsg = false;
					setfillcolor(SILVER);
					solidrectangle(writeRect.left, writeRect.top, writeRect.right, writeRect.bottom);
					setfillcolor(BLACK);
				}
			}
			//�л���ͨ/�����ӵ� 
			int bkey = Tool::waitKey();
			if (bkey == 107 || bkey == 75)//K
			{
				for (int i = 0; i < tanks.size(); i++)
				{
					if (tanks[i]->tankType == ���̹��1)
						tanks[i]->isEnableAutoFind = !(tanks[i]->isEnableAutoFind);
					Tool::sound(1);
				}
			}
			if (Tool::waitKey() == 50)//K
			{
				for (int i = 0; i < tanks.size(); i++)
				{
					if (tanks[i]->tankType == ���̹��2)
						tanks[i]->isEnableAutoFind = !(tanks[i]->isEnableAutoFind);
					Tool::sound(1);
				}
			}
			//��������3msһ֡,��ʡCPU��Դ
			graphics_control2 = clock();
			if (graphics_control2 - graphics_control1 < 3)
			{
				Sleep(1);
				continue;
			}
			graphics_control1 = graphics_control2;

			for (int i = 0; i < tanks.size(); i++)
			{
				/************���̹��************/
				if (tanks[i]->isPlayer)
				{


					//�ƶ�
					tanks[i]->tt_2 = clock();
					if (tanks[i]->tt_2 - tanks[i]->tt_1 >= 1000 / tanks[i]->m_moveSpeed)
					{
						tanks[i]->tt_1 = tanks[i]->tt_2;

						if (Tool::getKeyState(tanks[i]->upKey))
						{
							//���ƶ�
							tanks[i]->move(Up);
						}
						else if (Tool::getKeyState(tanks[i]->leftKey))
						{
							//���ƶ�
							tanks[i]->move(Left);
						}
						else if (Tool::getKeyState(tanks[i]->downKey))
						{
							//���ƶ�
							tanks[i]->move(Down);
						}
						else if (Tool::getKeyState(tanks[i]->rightKey))
						{
							//���ƶ�
							tanks[i]->move(Right);
						}
					}
					//���
					tanks[i]->ts_2 = clock();
					if (tanks[i]->ts_2 - tanks[i]->ts_1 >= tanks[i]->m_shootInterval)
					{
						tanks[i]->ts_1 = tanks[i]->ts_2;
						if (Tool::getKeyState(tanks[i]->shootKey))
						{

							//����
							Tool::sound(3);
							//����ӵ�������
							tanks[i]->shoot(tanks[i]->isEnableAutoFind);
							//�����ⷢ�ӵ�
							tanks[i]->drawBullet(tanks[i]->m_bulletList[0]);
						}
					}
				}
				else
				{
					/************AI̹��************/
					tanks[i]->tt_2 = clock();
					if (tanks[i]->tt_2 - tanks[i]->tt_1 > 1000 / tanks[i]->m_moveSpeed)
					{
						if (tanks[i]->step <= 0)
						{
							tanks[i]->step = rand() % 200;
							int nNum = rand() % 100;
							if (nNum >= 80)
							{
								//��(20%)						
								tanks[i]->d = Up;
							}
							else if (nNum >= 55)
							{
								//��(25%)
								tanks[i]->d = Left;
							}
							else if (nNum >= 30)
							{
								//��(25%)
								tanks[i]->d = Right;
							}
							else
							{
								//��(30%)
								tanks[i]->d = Down;
							}
						}
						//�ڴ˷����ʣ�ಽ���Լ�1
						tanks[i]->step--;
						tanks[i]->tt_1 = tanks[i]->tt_2;
						//�ƶ�֮ǰ��¼����
						point oldPoint = tanks[i]->m_centre;
						//�ƶ�
						tanks[i]->move(tanks[i]->d);
						//�ƶ�֮��Ƚ�����
						if (oldPoint.x == tanks[i]->m_centre.x && oldPoint.y == tanks[i]->m_centre.y)
						{
							tanks[i]->step -= 4;
						}
						//������
						tanks[i]->aits_2 = clock();
						int nNum = rand() % 20;
						if (nNum < 5)
						{
							nNum = 5;
						}
						if (tanks[i]->aits_2 - tanks[i]->aits_1 > 10000 / nNum)
						{
							tanks[i]->aits_1 = tanks[i]->aits_2;
							//���
							tanks[i]->shoot(tanks[i]->isEnableAutoFind);
						}
					}
				}
				//�ӵ��ƶ�
				tanks[i]->tb_2 = clock();
				if (tanks[i]->tb_2 - tanks[i]->tb_1 > 1000 / tanks[i]->m_bulletSpeed)
				{
					tanks[i]->tb_1 = tanks[i]->tb_2;
					for (int j = 0; j < tanks[i]->m_bulletList.size(); j++)
					{
						//����Ƿ���������"�ӵ�Խ����"
						bool flag = false;
						//�ӵ������ĵ�
						point bullet = tanks[i]->m_bulletList[j].m_centre;

						//�����ӵ�ͷ�����,�Ҽ�����
						POINT p, p1, p2;
						switch (tanks[i]->m_bulletList[j].m_dir)
						{
						case Up:
							p.x = bullet.x;
							p.y = bullet.y + 5;
							p1.x = bullet.x - 3;
							p1.y = bullet.y - 3;
							p2.x = bullet.x + 3;
							p2.y = bullet.y - 3;
							break;
						case Down:
							p.x = bullet.x;
							p.y = bullet.y - 5;
							p1.x = bullet.x - 3;
							p1.y = bullet.y + 3;
							p2.x = bullet.x + 3;
							p2.y = bullet.y + 3;
							break;
						case Left:
							p.x = bullet.x - 5;
							p.y = bullet.y;
							p1.x = bullet.x - 3;
							p1.y = bullet.y - 3;
							p2.x = bullet.x - 3;
							p2.y = bullet.y + 3;
							break;
						case Right:
							p.x = bullet.x + 5;
							p.y = bullet.y;
							p1.x = bullet.x + 3;
							p1.y = bullet.y - 3;
							p2.x = bullet.x + 3;
							p2.y = bullet.y + 3;
							break;
						default:
							break;
						}
						//bullet,go fighting!
						//�ӵ���ײ�ϰ�����
						if (tanks[i]->bulletMove(tanks[i]->m_bulletList[j], p1, p2))
						{
							//�Ƴ��ӵ�
							tanks[i]->displayBullet(tanks[i]->m_bulletList[j]);
							vector<::bullet>::iterator   iter = tanks[i]->m_bulletList.begin() + j;
							tanks[i]->m_bulletList.erase(iter);
							//�����������"�ӵ�Խ��"���
							flag = true;
						}
						//���»����ϰ���(���ѱ�����,��ɿյ�,�Ͳ������)
						point valpBullet1 = terrain::getPointInMap(point(bullet.x - 3, bullet.y - 3));
						point valpBullet2 = terrain::getPointInMap(point(bullet.x + 3, bullet.y - 3));
						point valpBullet3 = terrain::getPointInMap(point(bullet.x - 3, bullet.y + 3));
						point valpBullet4 = terrain::getPointInMap(point(bullet.x + 3, bullet.y + 3));
						if (map[valpBullet1.x][valpBullet1.y] != �յ�)
							terrain::reDraw(valpBullet1.x, valpBullet1.y);

						if (map[valpBullet2.x][valpBullet2.y] != �յ�)
							terrain::reDraw(valpBullet2.x, valpBullet2.y);

						if (map[valpBullet3.x][valpBullet3.y] != �յ�)
							terrain::reDraw(valpBullet3.x, valpBullet3.y);

						if (map[valpBullet4.x][valpBullet4.y] != �յ�)
							terrain::reDraw(valpBullet4.x, valpBullet4.y);


						//����ӵ��Ƿ���жԷ�̹��					
						for (int k = 0; k < tanks.size(); k++)
						{
							if (tanks[k]->m_centre.x == tanks[i]->m_centre.x && tanks[k]->m_centre.y == tanks[i]->m_centre.y)
							{
								//�ҵ����Լ�
								continue;
							}
							//�Է�̹�����ĵ�
							point tank = tanks[k]->m_centre;
							//̹��ģ�Ͱ뾶
							int model = tanks[k]->m_model;
							//������η�Χ(̹�˵�ʵ��ģ�ͷ�Χ)
							RECT rect = { tank.x - model,tank.y - model,tank.x + model,tank.y + model };
							//��ʼ���(���Ƿ��ھ��η�Χ��)
							if (PtInRect(&rect, p1) || PtInRect(&rect, p2))
							{
								//�Ƿ�Ϊ��ҵ��ӵ�
								bool isPlayerBullet = tanks[i]->m_bulletList[j].isPlayer;
								//�Ƴ��ӵ�
								tanks[i]->displayBullet(tanks[i]->m_bulletList[j]);
								vector<::bullet>::iterator   iter = tanks[i]->m_bulletList.begin() + j;
								tanks[i]->m_bulletList.erase(iter);
								if (tanks[k]->beShooted(isPlayerBullet))
								{
									Tool::sound(4);
									int lives = 0;
									for (int l = 0; l < tanks.size(); l++)
									{
										if (tanks[l]->ID == 1 || tanks[l]->ID == 2)
										{
											lives += tanks[l]->m_blood;
										}
									}
									if (lives == 0)
									{
										isGameOver = true;
										goto BEGIN;
									}
									//�Է�̹������
									if (isPlayerBullet)
									{
										//�ӷ�
										tanks[i]->score += 200;
										tanks[i]->updateScore(tanks[i]->ID);
										totalScore += 200;
										if (totalScore >= passScore)
										{
											//�ﵽ�����������
											//�رյо�̹������
											isborn = false;
											//���������������
											passScore += firstPassScore + increaseScore * currLv;
										}
									}
									point p;
									p.x = tanks[k]->m_centre.x;
									p.y = tanks[k]->m_centre.y;
									//���ñ�ը���
									p.mark1 = 1;
									//��ӵ���ը����
									boom.push_back(p);
									//����̹��
									tanks[k]->displayTank();
									//�Ƴ���̹�˷���������ӵ�
									for (int l = 0; l < tanks[k]->m_bulletList.size(); l++)
									{
										tanks[k]->displayBullet(tanks[k]->m_bulletList[l]);
									}
									tanks[k]->m_bulletList.clear();
									//�ͷ�̹����Դ
									delete tanks[k];
									//��̹�˳���ɾ����̹��
									vector<::tank*>::iterator   iter = tanks.begin() + k;
									tanks.erase(iter);
									//����о�̹�˵�����
									int enemyCount = 0;
									for (int x = 0; x < tanks.size(); x++)
									{
										if (tanks[x]->ID != 1 && tanks[x]->ID != 2)
										{
											enemyCount++;
										}
									}
									if (enemyCount == 0)
									{
										//�з�̹����ȫ������,������һ��
										currLv++;
										if (Tool::loadLevels(currLv))
										{
											time1 = clock();
											isPass = true;
										}
										else
										{
											//δ��ȡ����һ����ͼ�ļ�
											//ͨ��
											isGameOver = true;
											goto BEGIN;
										}

									}
								}
								goto BEGIN;
								//break;
							}
						}
						//�ӵ�ײ�ӵ����
					reCheck:
						for (int x = 0; x < tanks.size(); x++)
						{
							if (tanks[i]->m_centre.x == tanks[x]->m_centre.x && tanks[i]->m_centre.y == tanks[x]->m_centre.y)
							{
								//�ҵ����Լ�
								continue;
							}
							for (int y = 0; y < tanks[x]->m_bulletList.size(); y++)
							{
								//����Ŀ���ӵ��ķ�Χ(���ϽǺ����½�)
								POINT pBullet1, pBullet2;
								pBullet1.x = tanks[x]->m_bulletList[y].m_centre.x - 3;
								pBullet1.y = tanks[x]->m_bulletList[y].m_centre.y - 3;
								pBullet2.x = tanks[x]->m_bulletList[y].m_centre.x + 3;
								pBullet2.y = tanks[x]->m_bulletList[y].m_centre.y + 3;
								RECT bulletArea = { pBullet1.x,pBullet1.y,pBullet2.x,pBullet2.y };
								//����ӵ������������ӵ��ķ�Χ��,���Ƴ��ӵ�
								if (PtInRect(&bulletArea, p1) || PtInRect(&bulletArea, p2))
								{
									//�Ƴ��ӵ�
									if (i >= tanks.size())break;
									tanks[i]->displayBullet(tanks[i]->m_bulletList[j]);
									vector<::bullet>::iterator   iter1 = tanks[i]->m_bulletList.begin() + j;
									tanks[i]->m_bulletList.erase(iter1);

									tanks[x]->displayBullet(tanks[x]->m_bulletList[y]);
									vector<::bullet>::iterator   iter2 = tanks[x]->m_bulletList.begin() + y;
									tanks[x]->m_bulletList.erase(iter2);

									flag = true;
									goto reCheck;
								}
							}
						}
						if (flag)
						{
							continue;
						}
						//����ӵ��Ƿ񳬳��߽�
						if (tanks[i]->m_bulletList[j].m_centre.x > SCREEN_WIDTH + 5 ||
							tanks[i]->m_bulletList[j].m_centre.y > SCREEN_HEIGHT + 5 ||
							tanks[i]->m_bulletList[j].m_centre.x < -5 ||
							tanks[i]->m_bulletList[j].m_centre.y < -5)
						{
							//ɾ���ӵ�
							vector<::bullet>::iterator   iter = tanks[i]->m_bulletList.begin() + j;
							tanks[i]->m_bulletList.erase(iter);
							continue;
						}
					}
				}
			}

			//��ը����
			for (int i = 0; i < boom.size(); i++)
			{
				boom[i].cboom2 = clock();
				if (boom[i].cboom2 - boom[i].cboom1 > 100)
				{
					boom[i].cboom1 = boom[i].cboom2;
					//���ض���
					switch (boom[i].mark1)
					{
					case 1:putimage(boom[i].x - animate / 2, boom[i].y - animate / 2, &boom1, SRCCOPY); boom[i].mark1++; break;
					case 2:putimage(boom[i].x - animate / 2, boom[i].y - animate / 2, &boom2, SRCCOPY); boom[i].mark1++; break;
					case 3:putimage(boom[i].x - animate / 2, boom[i].y - animate / 2, &boom3, SRCCOPY); boom[i].mark1++; break;
					case 4:putimage(boom[i].x - animate / 2, boom[i].y - animate / 2, &boom4, SRCCOPY); boom[i].mark1++; break;
					case 5:putimage(boom[i].x - animate / 2, boom[i].y - animate / 2, &boom5, SRCCOPY); boom[i].mark1++; break;
					default:break;
					}
					if (boom[i].mark1 > 5)
					{
						//�Ƴ�����
						clearrectangle(
							boom[i].x - animate / 2,
							boom[i].y - animate / 2,
							boom[i].x + animate / 2,
							boom[i].y + animate / 2
						);
						//�Ƴ���ը����
						vector<point>::iterator   iter = boom.begin() + i;
						boom.erase(iter);
					}
				}
			}
			//����̹������		
			for (int i = 0; i < tborn.size(); i++)
			{
				tborn[i]->cborn2 = clock();
				if (tborn[i]->cborn2 - tborn[i]->cborn1 > 70)
				{
					//���ض���
					tborn[i]->cborn1 = tborn[i]->cborn2;
					if (tborn[i]->m_centre.mark2 == 1 || tborn[i]->m_centre.mark2 == 5 || tborn[i]->m_centre.mark2 == 9)
					{

						//��ӡ������һ֡
						putimage(tborn[i]->m_centre.x - animate / 2, tborn[i]->m_centre.y - animate / 2, &born1, SRCCOPY);
						tborn[i]->m_centre.mark2++;
					}
					else if (tborn[i]->m_centre.mark2 == 2 || tborn[i]->m_centre.mark2 == 6 || tborn[i]->m_centre.mark2 == 10)
					{
						//��ӡ�����ڶ�֡
						putimage(tborn[i]->m_centre.x - animate / 2, tborn[i]->m_centre.y - animate / 2, &born2, SRCCOPY);
						tborn[i]->m_centre.mark2++;
					}
					else if (tborn[i]->m_centre.mark2 == 3 || tborn[i]->m_centre.mark2 == 7 || tborn[i]->m_centre.mark2 == 11)
					{
						//��ӡ��������֡
						putimage(tborn[i]->m_centre.x - animate / 2, tborn[i]->m_centre.y - animate / 2, &born3, SRCCOPY);
						tborn[i]->m_centre.mark2++;
					}
					else if (tborn[i]->m_centre.mark2 == 4 || tborn[i]->m_centre.mark2 == 8 || tborn[i]->m_centre.mark2 == 12)
					{
						//��ӡ��������֡
						putimage(tborn[i]->m_centre.x - animate / 2, tborn[i]->m_centre.y - animate / 2, &born4, SRCCOPY);
						tborn[i]->m_centre.mark2++;
					}
					else if (tborn[i]->m_centre.mark2 > 12)
					{
						//�Ƴ�����
						clearrectangle(
							tborn[i]->m_centre.x - animate / 2,
							tborn[i]->m_centre.y - animate / 2,
							tborn[i]->m_centre.x + animate / 2,
							tborn[i]->m_centre.y + animate / 2
						);
						try
						{
							//���̹�˵�̹�˶���
							tanks.push_back(tborn[i]);
							tborn[i]->drawTank();
							vector<::tank*>::iterator   iter = tborn.begin() + i;
							tborn.erase(iter);
						}
						catch (const std::exception&)
						{

						}

					}
				}
			}
			int count = isTwo ? 5 : 4;
			//�����з�̹��
			if (isborn)
			{
				if (tanks.size() + tborn.size() < count)
				{
					switch (rand() % 3)
					{
					case 0:
					{
						tank *tc_A1 = new tank_computer(AI̹��1);
						tborn.push_back(tc_A1);
						break;
					}
					case 1:
					{
						tank *tc_B1 = new tank_computer(AI̹��2);
						tborn.push_back(tc_B1);
						break;
					}
					case 2:
					{
						tank *tc_C1 = new tank_computer(AI̹��3);
						tborn.push_back(tc_C1);
						break;
					}
					}
				}
			}
			//����ﵽ��������
			if (isPass)
			{
				if (clock() - time1 > 3000)
				{
					//��ʾ�ؿ���Ϣ
					showStage();
					//���Ƶ�ͼ
					terrain::drawMap();
					//�����о�̹������
					isborn = true;
					int forcount = tanks.size();
					for (int x = 0; x < forcount; x++)
					{
						//�Ƴ��ӵ�
						for (int y = 0; y < tanks[x]->m_bulletList.size(); y++)
						{
							//�Ƴ��ӵ�
							tanks[x]->displayBullet(tanks[x]->m_bulletList[y]);
						}
						tanks[x]->m_bulletList.clear();
						//̹������
						tanks[x]->revive();
						isPass = false;
					}
					//���̹�˳�
					tanks.clear();
				}
			}
		}
		catch (const std::exception&)
		{
			continue;
		}
	}
}


/**********************
customMap:�Զ����ͼ
**********************/
void game::customMap()
{
	/*for (int i = 0; i < SCREEN_WIDTH / cell; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT / cell; j++)
		{
			map[i][j] = 0;
		}
	}*/
	memset(map, 0, (SCREEN_WIDTH / cell)*(SCREEN_HEIGHT / cell) * 4);
	//�Ʒְ�
	setfillcolor(SILVER);
	solidrectangle(SCREEN_WIDTH, 0, SCREEN_WIDTH + 300, SCREEN_HEIGHT);
	//���ش�Ӫ
	map[SCREEN_WIDTH / cell / 2 - 1][SCREEN_HEIGHT / cell - 2] = ��Ӫ;

	//����������ɫ�ͱ���ɫ
	settextcolor(WHITE);
	setbkcolor(SILVER);
	//��������
	RECT r = { SCREEN_WIDTH + 20, 0,SCREEN_WIDTH + 200 , 40 };
	drawtext(_T("��ǰ�ϰ���:"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//�ָ�ԭ�ȱ���ɫ
	setbkcolor(BLACK);
	//���Ƶ�ͼ
	terrain::drawMap();
	//��ǰ������
	Terrain currTer = �յ�;
	//���ص�ǰ�ϰ���
	terrain t;
	terrain::reDraw(SCREEN_WIDTH + 80, 50, currTer);
	//�����Ϣ�ṹ��
	MOUSEMSG mouse;
	while (true)
	{
		//��⵱ǰ�Ƿ��������Ϣ
		if (MouseHit())
		{
			//��ȡһ�������Ϣ	
			mouse = GetMouseMsg();
			//����������
			if (mouse.mkLButton)
			{
				if (mouse.x >= SCREEN_WIDTH)
					continue;
				point valp = terrain::getPointInMap(point(mouse.x, mouse.y));
				//����ϰ���
				terrain t;
				t.addTerrain(valp.x, valp.y, currTer);
			}
		}
		int key = Tool::waitKey();
		if (key != 0)
		{
			switch (key)
			{
			case VK_SPACE:
				//�л���ǰ�ϰ���
				currTer = (Terrain)((int)currTer + 1);
				if (currTer > 4)
					currTer = �յ�;
				terrain::reDraw(SCREEN_WIDTH + 80, 50, currTer);
				break;
			case 27:
				//����
				cleardevice();
				//Tool::makeLevels();
				isCustomMap = true;
				cleardevice();
				start();
			default:
				break;
			}
		}

	}
}

/*********************
����:��ʾ�ؿ���Ϣ
*********************/
void game::showStage()
{
	//��ʾ�ؿ���Ϣ
	setfillcolor(SILVER);
	settextcolor(BLACK);
	solidrectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	RECT r = { (SCREEN_WIDTH) / 2 - 50,SCREEN_HEIGHT / 2 - 20,(SCREEN_WIDTH) / 2 + 50,SCREEN_HEIGHT / 2 + 20 };
	char ch[20];
	sprintf_s(ch, 20, "STAGE   %d", currLv);
	TCHAR str[20];
	for (int i = 0; i < 20; i++)
	{
		str[i] = ch[i];
	}
	setbkmode(TRANSPARENT);
	drawtext(str, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	Sleep(2000);
	//����ؿ���Ϣ
	setbkmode(OPAQUE);
	setfillcolor(BLACK);
	solidrectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	solidrectangle((SCREEN_WIDTH) / 2 - 50, SCREEN_HEIGHT / 2 - 20, (SCREEN_WIDTH) / 2 + 50, SCREEN_HEIGHT / 2 + 20);
}

/*******************
��Ϸ����
*******************/
void game::gameOver(bool isShow)
{
	//�Ƿ���ʾGAMEOVER����
	if (isShow)
	{
		Tool::sound(5);
		cleardevice();
		IMAGE over;
		int cwidth = 600, cheight = 300;
		loadimage(&over, _T("IMG/gameover.jpg"), cwidth, cheight, true);
		putimage((SCREEN_WIDTH - cwidth) / 2 + 150, 30, &over, SRCINVERT); while (true)
		{
			Sleep(1);
			int key = Tool::waitKey();
			if (key == 27)
			{

				break;
			}
		}
	}
	//������Ϸ����
	animate = 30;
	loadimage(&boom1, _T("IMG/boom/0.gif"), animate, animate, true);
	loadimage(&boom2, _T("IMG/boom/1.gif"), animate, animate, true);
	loadimage(&boom3, _T("IMG/boom/2.gif"), animate, animate, true);
	loadimage(&boom4, _T("IMG/boom/3.gif"), animate, animate, true);
	loadimage(&boom5, _T("IMG/boom/4.gif"), animate, animate, true);
	totalScore = 0;
	isPass = false;
	currLv = 1;
	isGameOver = false;
	passScore = firstPassScore;
	tanks.clear();
	tborn.clear();
	boom.clear();
	isTwo = false;
	isCustomMap = false;
	//�ص��˵�����
	start();
}
