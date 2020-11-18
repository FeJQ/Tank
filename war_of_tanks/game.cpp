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
//是否存在自定义地图
bool isCustomMap = false;

//游戏是否结束
bool isGameOver = false;
//当前关卡
int currLv = 1;
//动画尺寸
int  animate = 30;
//过第一关所需要的分数
int const firstPassScore = 4000;
//当前关卡过关所需要的分数
int  passScore = firstPassScore;
//每加一关,过关所需分数的增长数
int const increaseScore = 400;

//总分(P1+P2)
int totalScore = 0;

//是否过关
bool isPass = false;
clock_t time1 = clock();
//坦克列表
vector<tank*> tanks;

//生成坦克列表
vector<tank*> tborn;

//爆炸任务列表
vector<point> boom;

//爆炸图片对象
IMAGE boom1, boom2, boom3, boom4, boom5;

//坦克生成图片对象
IMAGE born1, born2, born3, born4;

//存档消息
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
start:进入游戏
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
	//设置随机种子
	srand(time(NULL));

	//创建画布
	consoleGraphics::Create();

	//首页封面
	IMAGE imgCover;
	int cwidth = 600, cheight = 200;
	loadimage(&imgCover, _T("IMG/cover.png"), cwidth, cheight, true);
	putimage((SCREEN_WIDTH - cwidth) / 2 + 150, 30, &imgCover, SRCINVERT);


	//首页菜单
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
	//如果检测到存档
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

	//选项箭头
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

	//销毁画布
	consoleGraphics::Destroy();
}

//加载游戏
void game::load(int option)
{

	if (maxOption == 4)
	{
		switch (option)
		{
		case 2:
		{
			//添加玩家坦克2
			tank_player *tank_2 = new tank_player(玩家坦克2);
			tborn.push_back(tank_2);
			isTwo = true;
		}
		case 1:
		{
			//清屏
			cleardevice();
			//计分板
			setfillcolor(SILVER);
			solidrectangle(SCREEN_WIDTH, 0, SCREEN_WIDTH + 300, SCREEN_HEIGHT);

			//添加玩家坦克1
			tank_player *tank_1 = new tank_player(玩家坦克1);
			tborn.push_back(tank_1);
			break;
		}
		case 3:
			//读档
			//清屏
			cleardevice();
			Tool::readData(true);
			break;
		case 4:
			//自定义地图
			//清屏
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
			//继续游戏
			Tool::readData(true);

			//清屏
			cleardevice();


			play();
			break;
		case 3:
		{
			//添加玩家坦克2
			tank_player *tank_2 = new tank_player(玩家坦克2);
			tborn.push_back(tank_2);
			isTwo = true;
		}
		case 2:
		{
			//清屏
			cleardevice();
			//计分板
			setfillcolor(SILVER);
			solidrectangle(SCREEN_WIDTH, 0, SCREEN_WIDTH + 300, SCREEN_HEIGHT);

			//添加玩家坦克1
			tank_player *tank_1 = new tank_player(玩家坦克1);
			tborn.push_back(tank_1);
			break;
		}
		case 4:
			//读档
			//清屏
			cleardevice();
			Tool::readData(true);
			break;
		case 5:
			//自定义地图
			//清屏
			cleardevice();
			customMap();
			break;
		default:
			break;
		}
	}
	//加载计分板
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
//存档提示区域
RECT writeRect = { SCREEN_WIDTH + 60,400,SCREEN_WIDTH + 180,440 };
/****************
play:开始游戏
*****************/
void game::play()
{

	isGameOver = false;
	//是否继续生成坦克
	bool isborn = true;
	//分数置零
	totalScore = 0;
	//显示关卡
	showStage();

	if (!isCustomMap)
	{
		//加载关卡
		Tool::loadLevels(currLv);
	}

	//加载地图
	terrain::drawMap();
	for (int i = 0; i < tanks.size(); i++)
	{
		tanks[i]->drawTank();
		if (tanks[i]->ID != 0)
		{
			setfillcolor(SILVER);
			solidrectangle(SCREEN_WIDTH, 0, SCREEN_WIDTH + 300, SCREEN_HEIGHT);
			tanks[i]->updateScore(tanks[i]->ID);
			if (tanks[i]->tankType == 玩家坦克1)
			{
				if (tanks[i]->m_blood == 0) putimage(SCREEN_WIDTH + 20, 20, &tanks[i]->scorecard_star0, SRCCOPY);
				if (tanks[i]->m_blood == 1) putimage(SCREEN_WIDTH + 20, 20, &tanks[i]->scorecard_star1, SRCCOPY);
				if (tanks[i]->m_blood == 2) putimage(SCREEN_WIDTH + 20, 20, &tanks[i]->scorecard_star2, SRCCOPY);
				if (tanks[i]->m_blood == 3) putimage(SCREEN_WIDTH + 20, 20, &tanks[i]->scorecard_star3, SRCCOPY);
				if (tanks[i]->m_blood == 4) putimage(SCREEN_WIDTH + 20, 20, &tanks[i]->scorecard_star4, SRCCOPY);
				if (tanks[i]->m_blood == 5) putimage(SCREEN_WIDTH + 20, 20, &tanks[i]->scorecard_star5, SRCCOPY);
				tanks[i]->updateScore(1);
			}
			if (tanks[i]->tankType == 玩家坦克2)
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
	//为计时器赋初始值
	for (size_t i = 0; i < tanks.size(); i++)
	{
		tanks[i]->tb_1 = clock();
		tanks[i]->tt_1 = clock();
		tanks[i]->ts_1 = clock();
	}
	clock_t graphics_control2, graphics_control1 = clock();
	//游戏主代码段
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
			//退出到主菜单(Esc)
			if (Tool::getKeyState(27))
			{
				//GAMEOVER
				gameOver(false);
			}
			//存档(M)
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
			//删除存档提示信息
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
			//切换普通/跟踪子弹 
			int bkey = Tool::waitKey();
			if (bkey == 107 || bkey == 75)//K
			{
				for (int i = 0; i < tanks.size(); i++)
				{
					if (tanks[i]->tankType == 玩家坦克1)
						tanks[i]->isEnableAutoFind = !(tanks[i]->isEnableAutoFind);
					Tool::sound(1);
				}
			}
			if (Tool::waitKey() == 50)//K
			{
				for (int i = 0; i < tanks.size(); i++)
				{
					if (tanks[i]->tankType == 玩家坦克2)
						tanks[i]->isEnableAutoFind = !(tanks[i]->isEnableAutoFind);
					Tool::sound(1);
				}
			}
			//限制至少3ms一帧,节省CPU资源
			graphics_control2 = clock();
			if (graphics_control2 - graphics_control1 < 3)
			{
				Sleep(1);
				continue;
			}
			graphics_control1 = graphics_control2;

			for (int i = 0; i < tanks.size(); i++)
			{
				/************玩家坦克************/
				if (tanks[i]->isPlayer)
				{


					//移动
					tanks[i]->tt_2 = clock();
					if (tanks[i]->tt_2 - tanks[i]->tt_1 >= 1000 / tanks[i]->m_moveSpeed)
					{
						tanks[i]->tt_1 = tanks[i]->tt_2;

						if (Tool::getKeyState(tanks[i]->upKey))
						{
							//上移动
							tanks[i]->move(Up);
						}
						else if (Tool::getKeyState(tanks[i]->leftKey))
						{
							//左移动
							tanks[i]->move(Left);
						}
						else if (Tool::getKeyState(tanks[i]->downKey))
						{
							//下移动
							tanks[i]->move(Down);
						}
						else if (Tool::getKeyState(tanks[i]->rightKey))
						{
							//右移动
							tanks[i]->move(Right);
						}
					}
					//射击
					tanks[i]->ts_2 = clock();
					if (tanks[i]->ts_2 - tanks[i]->ts_1 >= tanks[i]->m_shootInterval)
					{
						tanks[i]->ts_1 = tanks[i]->ts_2;
						if (Tool::getKeyState(tanks[i]->shootKey))
						{

							//开炮
							Tool::sound(3);
							//添加子弹到队列
							tanks[i]->shoot(tanks[i]->isEnableAutoFind);
							//绘制这发子弹
							tanks[i]->drawBullet(tanks[i]->m_bulletList[0]);
						}
					}
				}
				else
				{
					/************AI坦克************/
					tanks[i]->tt_2 = clock();
					if (tanks[i]->tt_2 - tanks[i]->tt_1 > 1000 / tanks[i]->m_moveSpeed)
					{
						if (tanks[i]->step <= 0)
						{
							tanks[i]->step = rand() % 200;
							int nNum = rand() % 100;
							if (nNum >= 80)
							{
								//上(20%)						
								tanks[i]->d = Up;
							}
							else if (nNum >= 55)
							{
								//左(25%)
								tanks[i]->d = Left;
							}
							else if (nNum >= 30)
							{
								//右(25%)
								tanks[i]->d = Right;
							}
							else
							{
								//下(30%)
								tanks[i]->d = Down;
							}
						}
						//在此方向的剩余步数自减1
						tanks[i]->step--;
						tanks[i]->tt_1 = tanks[i]->tt_2;
						//移动之前记录坐标
						point oldPoint = tanks[i]->m_centre;
						//移动
						tanks[i]->move(tanks[i]->d);
						//移动之后比较坐标
						if (oldPoint.x == tanks[i]->m_centre.x && oldPoint.y == tanks[i]->m_centre.y)
						{
							tanks[i]->step -= 4;
						}
						//随机射击
						tanks[i]->aits_2 = clock();
						int nNum = rand() % 20;
						if (nNum < 5)
						{
							nNum = 5;
						}
						if (tanks[i]->aits_2 - tanks[i]->aits_1 > 10000 / nNum)
						{
							tanks[i]->aits_1 = tanks[i]->aits_2;
							//射击
							tanks[i]->shoot(tanks[i]->isEnableAutoFind);
						}
					}
				}
				//子弹移动
				tanks[i]->tb_2 = clock();
				if (tanks[i]->tb_2 - tanks[i]->tb_1 > 1000 / tanks[i]->m_bulletSpeed)
				{
					tanks[i]->tb_1 = tanks[i]->tb_2;
					for (int j = 0; j < tanks[i]->m_bulletList.size(); j++)
					{
						//标记是否跳过本次"子弹越界检查"
						bool flag = false;
						//子弹的中心点
						point bullet = tanks[i]->m_bulletList[j].m_centre;

						//计算子弹头和左肩,右肩坐标
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
						//子弹碰撞障碍物检测
						if (tanks[i]->bulletMove(tanks[i]->m_bulletList[j], p1, p2))
						{
							//移除子弹
							tanks[i]->displayBullet(tanks[i]->m_bulletList[j]);
							vector<::bullet>::iterator   iter = tanks[i]->m_bulletList.begin() + j;
							tanks[i]->m_bulletList.erase(iter);
							//标记跳过本次"子弹越界"检查
							flag = true;
						}
						//重新绘制障碍物(若已被击垮,变成空地,就不会绘制)
						point valpBullet1 = terrain::getPointInMap(point(bullet.x - 3, bullet.y - 3));
						point valpBullet2 = terrain::getPointInMap(point(bullet.x + 3, bullet.y - 3));
						point valpBullet3 = terrain::getPointInMap(point(bullet.x - 3, bullet.y + 3));
						point valpBullet4 = terrain::getPointInMap(point(bullet.x + 3, bullet.y + 3));
						if (map[valpBullet1.x][valpBullet1.y] != 空地)
							terrain::reDraw(valpBullet1.x, valpBullet1.y);

						if (map[valpBullet2.x][valpBullet2.y] != 空地)
							terrain::reDraw(valpBullet2.x, valpBullet2.y);

						if (map[valpBullet3.x][valpBullet3.y] != 空地)
							terrain::reDraw(valpBullet3.x, valpBullet3.y);

						if (map[valpBullet4.x][valpBullet4.y] != 空地)
							terrain::reDraw(valpBullet4.x, valpBullet4.y);


						//检测子弹是否击中对方坦克					
						for (int k = 0; k < tanks.size(); k++)
						{
							if (tanks[k]->m_centre.x == tanks[i]->m_centre.x && tanks[k]->m_centre.y == tanks[i]->m_centre.y)
							{
								//找到了自己
								continue;
							}
							//对方坦克中心点
							point tank = tanks[k]->m_centre;
							//坦克模型半径
							int model = tanks[k]->m_model;
							//定义矩形范围(坦克的实际模型范围)
							RECT rect = { tank.x - model,tank.y - model,tank.x + model,tank.y + model };
							//开始检查(点是否在矩形范围内)
							if (PtInRect(&rect, p1) || PtInRect(&rect, p2))
							{
								//是否为玩家的子弹
								bool isPlayerBullet = tanks[i]->m_bulletList[j].isPlayer;
								//移除子弹
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
									//对方坦克死亡
									if (isPlayerBullet)
									{
										//加分
										tanks[i]->score += 200;
										tanks[i]->updateScore(tanks[i]->ID);
										totalScore += 200;
										if (totalScore >= passScore)
										{
											//达到过关所需分数
											//关闭敌军坦克生成
											isborn = false;
											//过关所需分数增加
											passScore += firstPassScore + increaseScore * currLv;
										}
									}
									point p;
									p.x = tanks[k]->m_centre.x;
									p.y = tanks[k]->m_centre.y;
									//重置爆炸标记
									p.mark1 = 1;
									//添加到爆炸任务
									boom.push_back(p);
									//隐藏坦克
									tanks[k]->displayTank();
									//移除该坦克发射的所有子弹
									for (int l = 0; l < tanks[k]->m_bulletList.size(); l++)
									{
										tanks[k]->displayBullet(tanks[k]->m_bulletList[l]);
									}
									tanks[k]->m_bulletList.clear();
									//释放坦克资源
									delete tanks[k];
									//从坦克池里删除该坦克
									vector<::tank*>::iterator   iter = tanks.begin() + k;
									tanks.erase(iter);
									//计算敌军坦克的数量
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
										//敌方坦克已全部阵亡,进入下一关
										currLv++;
										if (Tool::loadLevels(currLv))
										{
											time1 = clock();
											isPass = true;
										}
										else
										{
											//未读取到下一个地图文件
											//通关
											isGameOver = true;
											goto BEGIN;
										}

									}
								}
								goto BEGIN;
								//break;
							}
						}
						//子弹撞子弹检测
					reCheck:
						for (int x = 0; x < tanks.size(); x++)
						{
							if (tanks[i]->m_centre.x == tanks[x]->m_centre.x && tanks[i]->m_centre.y == tanks[x]->m_centre.y)
							{
								//找到了自己
								continue;
							}
							for (int y = 0; y < tanks[x]->m_bulletList.size(); y++)
							{
								//计算目标子弹的范围(左上角和右下角)
								POINT pBullet1, pBullet2;
								pBullet1.x = tanks[x]->m_bulletList[y].m_centre.x - 3;
								pBullet1.y = tanks[x]->m_bulletList[y].m_centre.y - 3;
								pBullet2.x = tanks[x]->m_bulletList[y].m_centre.x + 3;
								pBullet2.y = tanks[x]->m_bulletList[y].m_centre.y + 3;
								RECT bulletArea = { pBullet1.x,pBullet1.y,pBullet2.x,pBullet2.y };
								//如果子弹两肩在其他子弹的范围内,则移除子弹
								if (PtInRect(&bulletArea, p1) || PtInRect(&bulletArea, p2))
								{
									//移除子弹
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
						//检查子弹是否超出边界
						if (tanks[i]->m_bulletList[j].m_centre.x > SCREEN_WIDTH + 5 ||
							tanks[i]->m_bulletList[j].m_centre.y > SCREEN_HEIGHT + 5 ||
							tanks[i]->m_bulletList[j].m_centre.x < -5 ||
							tanks[i]->m_bulletList[j].m_centre.y < -5)
						{
							//删除子弹
							vector<::bullet>::iterator   iter = tanks[i]->m_bulletList.begin() + j;
							tanks[i]->m_bulletList.erase(iter);
							continue;
						}
					}
				}
			}

			//爆炸任务
			for (int i = 0; i < boom.size(); i++)
			{
				boom[i].cboom2 = clock();
				if (boom[i].cboom2 - boom[i].cboom1 > 100)
				{
					boom[i].cboom1 = boom[i].cboom2;
					//加载动画
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
						//移除动画
						clearrectangle(
							boom[i].x - animate / 2,
							boom[i].y - animate / 2,
							boom[i].x + animate / 2,
							boom[i].y + animate / 2
						);
						//移除爆炸任务
						vector<point>::iterator   iter = boom.begin() + i;
						boom.erase(iter);
					}
				}
			}
			//生成坦克任务		
			for (int i = 0; i < tborn.size(); i++)
			{
				tborn[i]->cborn2 = clock();
				if (tborn[i]->cborn2 - tborn[i]->cborn1 > 70)
				{
					//加载动画
					tborn[i]->cborn1 = tborn[i]->cborn2;
					if (tborn[i]->m_centre.mark2 == 1 || tborn[i]->m_centre.mark2 == 5 || tborn[i]->m_centre.mark2 == 9)
					{

						//打印动画第一帧
						putimage(tborn[i]->m_centre.x - animate / 2, tborn[i]->m_centre.y - animate / 2, &born1, SRCCOPY);
						tborn[i]->m_centre.mark2++;
					}
					else if (tborn[i]->m_centre.mark2 == 2 || tborn[i]->m_centre.mark2 == 6 || tborn[i]->m_centre.mark2 == 10)
					{
						//打印动画第二帧
						putimage(tborn[i]->m_centre.x - animate / 2, tborn[i]->m_centre.y - animate / 2, &born2, SRCCOPY);
						tborn[i]->m_centre.mark2++;
					}
					else if (tborn[i]->m_centre.mark2 == 3 || tborn[i]->m_centre.mark2 == 7 || tborn[i]->m_centre.mark2 == 11)
					{
						//打印动画第三帧
						putimage(tborn[i]->m_centre.x - animate / 2, tborn[i]->m_centre.y - animate / 2, &born3, SRCCOPY);
						tborn[i]->m_centre.mark2++;
					}
					else if (tborn[i]->m_centre.mark2 == 4 || tborn[i]->m_centre.mark2 == 8 || tborn[i]->m_centre.mark2 == 12)
					{
						//打印动画第四帧
						putimage(tborn[i]->m_centre.x - animate / 2, tborn[i]->m_centre.y - animate / 2, &born4, SRCCOPY);
						tborn[i]->m_centre.mark2++;
					}
					else if (tborn[i]->m_centre.mark2 > 12)
					{
						//移除动画
						clearrectangle(
							tborn[i]->m_centre.x - animate / 2,
							tborn[i]->m_centre.y - animate / 2,
							tborn[i]->m_centre.x + animate / 2,
							tborn[i]->m_centre.y + animate / 2
						);
						try
						{
							//添加坦克到坦克队列
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
			//新增敌方坦克
			if (isborn)
			{
				if (tanks.size() + tborn.size() < count)
				{
					switch (rand() % 3)
					{
					case 0:
					{
						tank *tc_A1 = new tank_computer(AI坦克1);
						tborn.push_back(tc_A1);
						break;
					}
					case 1:
					{
						tank *tc_B1 = new tank_computer(AI坦克2);
						tborn.push_back(tc_B1);
						break;
					}
					case 2:
					{
						tank *tc_C1 = new tank_computer(AI坦克3);
						tborn.push_back(tc_C1);
						break;
					}
					}
				}
			}
			//如果达到过关条件
			if (isPass)
			{
				if (clock() - time1 > 3000)
				{
					//显示关卡信息
					showStage();
					//绘制地图
					terrain::drawMap();
					//开启敌军坦克生成
					isborn = true;
					int forcount = tanks.size();
					for (int x = 0; x < forcount; x++)
					{
						//移除子弹
						for (int y = 0; y < tanks[x]->m_bulletList.size(); y++)
						{
							//移除子弹
							tanks[x]->displayBullet(tanks[x]->m_bulletList[y]);
						}
						tanks[x]->m_bulletList.clear();
						//坦克重生
						tanks[x]->revive();
						isPass = false;
					}
					//清空坦克池
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
customMap:自定义地图
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
	//计分板
	setfillcolor(SILVER);
	solidrectangle(SCREEN_WIDTH, 0, SCREEN_WIDTH + 300, SCREEN_HEIGHT);
	//加载大本营
	map[SCREEN_WIDTH / cell / 2 - 1][SCREEN_HEIGHT / cell - 2] = 大本营;

	//设置文字颜色和背景色
	settextcolor(WHITE);
	setbkcolor(SILVER);
	//绘制文字
	RECT r = { SCREEN_WIDTH + 20, 0,SCREEN_WIDTH + 200 , 40 };
	drawtext(_T("当前障碍物:"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//恢复原先背景色
	setbkcolor(BLACK);
	//绘制地图
	terrain::drawMap();
	//当前建筑物
	Terrain currTer = 空地;
	//加载当前障碍物
	terrain t;
	terrain::reDraw(SCREEN_WIDTH + 80, 50, currTer);
	//鼠标消息结构体
	MOUSEMSG mouse;
	while (true)
	{
		//检测当前是否有鼠标消息
		if (MouseHit())
		{
			//获取一个鼠标消息	
			mouse = GetMouseMsg();
			//鼠标左键按下
			if (mouse.mkLButton)
			{
				if (mouse.x >= SCREEN_WIDTH)
					continue;
				point valp = terrain::getPointInMap(point(mouse.x, mouse.y));
				//添加障碍物
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
				//切换当前障碍物
				currTer = (Terrain)((int)currTer + 1);
				if (currTer > 4)
					currTer = 空地;
				terrain::reDraw(SCREEN_WIDTH + 80, 50, currTer);
				break;
			case 27:
				//清屏
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
功能:显示关卡信息
*********************/
void game::showStage()
{
	//显示关卡信息
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
	//清除关卡信息
	setbkmode(OPAQUE);
	setfillcolor(BLACK);
	solidrectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	solidrectangle((SCREEN_WIDTH) / 2 - 50, SCREEN_HEIGHT / 2 - 20, (SCREEN_WIDTH) / 2 + 50, SCREEN_HEIGHT / 2 + 20);
}

/*******************
游戏结束
*******************/
void game::gameOver(bool isShow)
{
	//是否显示GAMEOVER界面
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
	//重置游戏参数
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
	//回到菜单界面
	start();
}
