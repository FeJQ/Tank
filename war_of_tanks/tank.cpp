#include "pch.h"
#include "tank.h"
#include <graphics.h>
#include "game.h"
#include "consoleGraphics.h"
#include "terrain.h"
#include "Tool.h"
#include "point.h"
#include "Astar.h"
//������̹�˹��캯��������
tank::tank()
{
	this->m_centre.mark1 = 1;
	this->m_centre.mark2 = 1;
	this->cborn1 = clock();
	this->aits_1 = clock();
	this->m_model = tank_model;
	this->isEnableAutoFind = false;
}
tank::~tank()
{
}
//������̹����������������


/*************************
display:����̹��
**************************/
void tank::displayTank()
{
	clearrectangle(m_centre.x - m_model, m_centre.y - m_model, m_centre.x + m_model, m_centre.y + m_model);
}

/**********************
����:ʵʱ���¼Ʒ����
**********************/
void tank::updateScore(int player)
{
	//����������ɫ�ͱ���ɫ
	settextcolor(WHITE);
	//setbkcolor(SILVER);
	//��������
	RECT r;
	if (player == 1)
	{
		r.left = SCREEN_WIDTH + 110;
		r.top = 82;
		r.right = SCREEN_WIDTH + 180;
		r.bottom = 110;

	}
	else if (player == 2)
	{
		r.left = SCREEN_WIDTH + 110;
		r.top = 182 + 57;
		r.right = SCREEN_WIDTH + 180;
		r.bottom = 210 + 57;
	}
	char ch[10];

	sprintf_s(ch, 10, "%d", this->score);
	TCHAR str[10];
	for (int i = 0; i < 10; i++)
	{
		str[i] = ch[i];
	}

	drawtext(str, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//�ָ�ԭ�ȱ���ɫ
	//setbkcolor(BLACK);
}

/********************
����:�ı�̹�˷���
********************/
void tank::changeDir(Direction dir)
{
	this->dir = dir;
	displayTank();
	drawTank();
}

/*******************
����:����̹��
*******************/
void tank::drawTank()
{
	switch (m_dir())
	{
	case Up: putimage(this->m_centre.x - m_model, this->m_centre.y - m_model, &UpImg, SRCCOPY); break;
	case Down:putimage(this->m_centre.x - m_model, this->m_centre.y - m_model, &DownImg, SRCCOPY); break;
	case Left:putimage(this->m_centre.x - m_model, this->m_centre.y - m_model, &LeftImg, SRCCOPY); break;
	case Right:putimage(this->m_centre.x - m_model, this->m_centre.y - m_model, &RightImg, SRCCOPY); break;
	default:break;
	}
}

/*******************
����:����̹��
centre:̹�����ĵ�
*******************/
void tank::drawTank(point centre)
{
	this->m_centre = centre;
	drawTank();
}


/************************
move:̹���ƶ�
dir:�ƶ�����
************************/
void tank::move(Direction dir)
{
	changeDir(dir);
	this->displayTank();
	//̹�����ϽǺ����Ͻ��Լ�ǹ��

	POINT p1, p2;
	point myp1, myp2, myp3;
	switch (dir)
	{
	case Up:
		p1.x = m_centre.x - m_model;
		p1.y = m_centre.y - m_model;
		p1.y -= STEP;
		p2.x = m_centre.x + m_model;
		p2.y = m_centre.y - m_model;
		p2.y -= STEP;

		myp1.x = p1.x - tank_terrain_distance;
		myp1.y = p1.y - tank_terrain_distance;
		myp2.x = p2.x + tank_terrain_distance;
		myp2.y = p2.y - tank_terrain_distance;
		myp3.x = (myp1.x + myp2.x) / 2;
		myp3.y = (myp1.y + myp2.y) / 2;
		break;
	case Down:
		p1.x = m_centre.x + m_model;
		p1.y = m_centre.y + m_model;
		p1.y += STEP;
		p2.x = m_centre.x - m_model;
		p2.y = m_centre.y + m_model;
		p2.y += STEP;
		myp1.x = p1.x + tank_terrain_distance;
		myp1.y = p1.y + tank_terrain_distance;
		myp2.x = p2.x - tank_terrain_distance;
		myp2.y = p2.y + tank_terrain_distance;
		myp3.x = (myp1.x + myp2.x) / 2;
		myp3.y = (myp1.y + myp2.y) / 2;
		break;
	case Left:
		p1.x = m_centre.x - m_model;
		p1.y = m_centre.y + m_model;
		p1.x -= STEP;
		p2.x = m_centre.x - m_model;
		p2.y = m_centre.y - m_model;
		p2.x -= STEP;
		myp1.x = p1.x - tank_terrain_distance;
		myp1.y = p1.y + tank_terrain_distance;
		myp2.x = p2.x - tank_terrain_distance;
		myp2.y = p2.y - tank_terrain_distance;
		myp3.x = (myp1.x + myp2.x) / 2;
		myp3.y = (myp1.y + myp2.y) / 2;
		break;
	case Right:
		p1.x = m_centre.x + m_model;
		p1.y = m_centre.y - m_model;
		p1.x += STEP;
		p2.x = m_centre.x + m_model;
		p2.y = m_centre.y + m_model;
		p2.x += STEP;
		myp1.x = p1.x + tank_terrain_distance;
		myp1.y = p1.y - tank_terrain_distance;
		myp2.x = p2.x + tank_terrain_distance;
		myp2.y = p2.y + tank_terrain_distance;
		myp3.x = (myp1.x + myp2.x) / 2;
		myp3.y = (myp1.y + myp2.y) / 2;
		break;
	default:break;
	}
	int border = -20;
	//�߽���
	if (p1.x - this->m_model<0 + border ||
		p1.y - this->m_model <0 + border ||
		p2.x + this->m_model>SCREEN_WIDTH - border ||
		p2.y + this->m_model>SCREEN_HEIGHT - border)
	{
		this->drawTank(this->m_centre);
		return;
	}
	//�ϰ�����ײ���
	//���̹�����Ҽ��Լ�ǹ���ڵ�ͼ�е�ʵ��ֵ
	point valp1 = terrain::getPointInMap(myp1);
	point valp2 = terrain::getPointInMap(myp2);
	point valp3 = terrain::getPointInMap(myp3);
	int val1 = map[valp1.x][valp1.y];
	int val2 = map[valp2.x][valp2.y];
	int val3 = map[valp3.x][valp3.y];

	if (val1 == ��ש || val1 == ��ש || val1 == ���� || val1 == ��Ӫ || val1 == ռλ�� ||
		val2 == ��ש || val2 == ��ש || val2 == ���� || val2 == ��Ӫ || val2 == ռλ�� ||
		val3 == ��ש || val3 == ��ש || val3 == ���� || val3 == ��Ӫ || val3 == ռλ��)
	{
		this->drawTank(this->m_centre);
		return;
	}
	//��̹����ײ���	
	for (int i = 0; i < tanks.size(); i++)
	{
		if (this->m_centre.x == tanks[i]->m_centre.x && this->m_centre.y == tanks[i]->m_centre.y)
		{
			//�ҵ����Լ�
			//����
			continue;
		}
		point tank = tanks[i]->m_centre;
		int model = tanks[i]->m_model + 0;
		//�жϵ��Ƿ���Ŀ����η�Χ��
		RECT rect = { tank.x - model,tank.y - model,tank.x + model,tank.y + model };
		if (PtInRect(&rect, p1) || PtInRect(&rect, p2))
		{
			this->drawTank(this->m_centre);
			return;
		}
	}
	this->displayTank();
	this->dir = dir;
	switch (m_dir())
	{
	case Up:this->m_centre.y -= STEP; break;
	case Down:this->m_centre.y += STEP; break;
	case Left:this->m_centre.x -= STEP; break;
	case Right:this->m_centre.x += STEP; break;
	case UpLeft:this->m_centre.x -= STEP; m_centre.y -= STEP; break;
	case UpRight:this->m_centre.x += STEP; m_centre.y -= STEP; break;
	case LowerLeft:this->m_centre.x -= STEP; m_centre.y += STEP; break;
	case LowerRight:this->m_centre.x += STEP; m_centre.y += STEP; break;
	default:break;
	}
	this->drawTank(this->m_centre);
	//����̹�˵ľŵ�������
	//������
	//������
	//������
	point valp_1 = terrain::getPointInMap(point(this->m_centre.x - m_model, this->m_centre.y - m_model));
	point valp_2 = terrain::getPointInMap(point(this->m_centre.x - m_model, this->m_centre.y));
	point valp_3 = terrain::getPointInMap(point(this->m_centre.x + m_model, this->m_centre.y - m_model));
	point valp_4 = terrain::getPointInMap(point(this->m_centre.x, this->m_centre.y - m_model));
	point valp_5 = terrain::getPointInMap(point(this->m_centre));
	point valp_6 = terrain::getPointInMap(point(this->m_centre.x + m_model, this->m_centre.y));
	point valp_7 = terrain::getPointInMap(point(this->m_centre.x - m_model, this->m_centre.y + m_model));
	point valp_8 = terrain::getPointInMap(point(this->m_centre.x, this->m_centre.y + m_model));
	point valp_9 = terrain::getPointInMap(point(this->m_centre.x + m_model, this->m_centre.y + m_model));

	if (map[valp_1.x][valp_1.y] == ɭ�� ||
		map[valp_2.x][valp_2.y] == ɭ�� ||
		map[valp_3.x][valp_3.y] == ɭ�� ||
		map[valp_4.x][valp_4.y] == ɭ�� ||
		map[valp_5.x][valp_5.y] == ɭ�� ||
		map[valp_6.x][valp_6.y] == ɭ�� ||
		map[valp_7.x][valp_7.y] == ɭ�� ||
		map[valp_8.x][valp_8.y] == ɭ�� ||
		map[valp_9.x][valp_9.y] == ɭ��)
	{
		//���»����ϰ���(���ѱ�����,��ɿյ�,�Ͳ������)
		terrain::reDraw(valp_1.x, valp_1.y);
		terrain::reDraw(valp_2.x, valp_2.y);
		terrain::reDraw(valp_3.x, valp_3.y);
		terrain::reDraw(valp_4.x, valp_4.y);
		terrain::reDraw(valp_5.x, valp_5.y);
		terrain::reDraw(valp_6.x, valp_6.y);
		terrain::reDraw(valp_7.x, valp_7.y);
		terrain::reDraw(valp_8.x, valp_8.y);
		terrain::reDraw(valp_9.x, valp_9.y);
	}

	return;
}
/***********************
buildBullet:�����ӵ�ģ��
***********************/
void tank::buildBullet(bullet b, POINT pts[5], int border)
{
	//��
	//��
	int A = 3;//�����α߳�/2
	int B = 4;//�����θ�

	switch (b.m_dir)
	{
	case Up:
		pts[0].x = b.m_centre.x;
		pts[0].y = b.m_centre.y - A - B - border;
		pts[1].x = b.m_centre.x - A - border;
		pts[1].y = b.m_centre.y - A - border;
		pts[2].x = b.m_centre.x - A - border;
		pts[2].y = b.m_centre.y + A + border;
		pts[3].x = b.m_centre.x + A + border;
		pts[3].y = b.m_centre.y + A + border;
		pts[4].x = b.m_centre.x + A + border;
		pts[4].y = b.m_centre.y - A - border;
		break;
	case Down:
		pts[0].x = b.m_centre.x;
		pts[0].y = b.m_centre.y + A + B + border;
		pts[1].x = b.m_centre.x - A - border;
		pts[1].y = b.m_centre.y + A + border;
		pts[2].x = b.m_centre.x - A - border;
		pts[2].y = b.m_centre.y - A - border;
		pts[3].x = b.m_centre.x + A + border;
		pts[3].y = b.m_centre.y - A - border;
		pts[4].x = b.m_centre.x + A + border;
		pts[4].y = b.m_centre.y + A + border;
		break;
	case Left:
		pts[0].x = b.m_centre.x - A - B - border;
		pts[0].y = b.m_centre.y;
		pts[1].x = b.m_centre.x - A - border;
		pts[1].y = b.m_centre.y - A - border;
		pts[2].x = b.m_centre.x + A + border;
		pts[2].y = b.m_centre.y - A - border;
		pts[3].x = b.m_centre.x + A + border;
		pts[3].y = b.m_centre.y + A + border;
		pts[4].x = b.m_centre.x - A - border;
		pts[4].y = b.m_centre.y + A + border;
		break;
	case Right:
		pts[0].x = b.m_centre.x + A + B + border;
		pts[0].y = b.m_centre.y;
		pts[1].x = b.m_centre.x + A + border;
		pts[1].y = b.m_centre.y + A + border;
		pts[2].x = b.m_centre.x - A - border;
		pts[2].y = b.m_centre.y + A + border;
		pts[3].x = b.m_centre.x - A - border;
		pts[3].y = b.m_centre.y - A - border;
		pts[4].x = b.m_centre.x + A + border;
		pts[4].y = b.m_centre.y - A - border;
		break;
	case UpLeft:			 break;
	case UpRight:			 break;
	case LowerLeft:			 break;
	case LowerRight:		 break;
	default:
		break;
	}
}




/***********************
drawBullet:�����ӵ�
***********************/
void tank::drawBullet(bullet b)
{
	setfillcolor(this->m_bulletColor);
	POINT pts[5] = { 0 };
	buildBullet(b, pts);
	//���ӵ�
	fillpolygon(pts, 5);
}


/***********************
displayBullet:�����ӵ�
***********************/
void tank::displayBullet(bullet b)
{
	POINT pts[5] = { 0 };
	buildBullet(b, pts, 1);
	//�����ӵ�
	clearpolygon(pts, 5);
}
/***********************
shoot:�����ӵ�
isAutoFind:�Ƿ�Ϊ�����ӵ�
***********************/
void tank::shoot(bool isAutoFind)
{
	bool isPlayerBullet = this->isPlayer ? true : false;
	switch (this->m_dir())
	{
	case Up:
		m_bulletList.insert(m_bulletList.begin(), bullet(m_centre.x, m_centre.y - (m_model + 9), Up, isPlayerBullet, isAutoFind));
		break;
	case Down:
		this->m_bulletList.insert(m_bulletList.begin(), bullet(m_centre.x, m_centre.y + (m_model + 9), Down, isPlayerBullet, isAutoFind));
		break;
	case Left:
		this->m_bulletList.insert(m_bulletList.begin(), bullet(m_centre.x - (m_model + 9), m_centre.y, Left, isPlayerBullet, isAutoFind));
		break;
	case Right:
		this->m_bulletList.insert(m_bulletList.begin(), bullet(m_centre.x + (m_model + 9), m_centre.y, Right, isPlayerBullet, isAutoFind));
		break;
	default:break;
	}
}


/**********************
bulletMove:�ӵ��ƶ�
return:�Ƿ�ɾ���ӵ�
**********************/
void tank::bulletMove(bullet &b)
{
	displayBullet(b);
	if (!b.isAutoFind)
	{

		switch (b.m_dir)
		{
		case Up:b.m_centre.y -= STEP; break;
		case Down:b.m_centre.y += STEP; break;
		case Left:b.m_centre.x -= STEP; break;
		case Right:b.m_centre.x += STEP; break;
		default:break;
		}
	}
	else
	{
		CAstar sta;
		sta.InitMapInfo(SCREEN_WIDTH / cell, SCREEN_HEIGHT / cell);
		for (int i = 0; i < tanks.size(); i++)
		{
			if (tanks[i]->ID == 0)
			{
				sta.InitPOINTInfo({ b.m_centre.x, b.m_centre.y }, { tanks[i]->m_centre.x, tanks[i]->m_centre.y });
			}
		}
		if (sta.FindPath())
		{
			sta.GetPath();
		}
		point p= sta.getPathFirstPoint();
		b.m_centre.x = p.x*cell;
		b.m_centre .y= p.y*cell;

	}
	drawBullet(b);
}

/**************************************************
bulletMove:�ӵ��ƶ�
b:�ӵ���������
p1,p2�ӵ����Ҽ�����
return:�Ƿ�ɾ���ӵ�
**************************************************/
bool tank::bulletMove(bullet & b, POINT p1, POINT p2)
{
	////�����ͼ�±�
	point valpBullet1;
	valpBullet1 = terrain::getPointInMap(p1);
	point valpBullet2;
	valpBullet2 = terrain::getPointInMap(p2);
	bool result = false;
	//����Ƿ�����ϰ�
	bool isDelBullet1 = tank::shootTerrain(valpBullet1.x, valpBullet1.y);
	bool isDelBullet2 = tank::shootTerrain(valpBullet2.x, valpBullet2.y);
	if (isDelBullet1 || isDelBullet2)
	{
		result = true;
	}
	displayBullet(b);
	if (!b.isAutoFind)
	{
		this->m_bulletSpeed = 1000;
		this->m_shootInterval =200 ;
		switch (b.m_dir)
		{
		case Up:b.m_centre.y -= STEP; break;
		case Down:b.m_centre.y += STEP; break;
		case Left:b.m_centre.x -= STEP; break;
		case Right:b.m_centre.x += STEP; break;
		default:break;
		}
	}
	else
	{
		//�Զ������ӵ�
		this->m_bulletSpeed = 10;
		this->m_shootInterval = 700;
		//�Զ�Ѱ·
		CAstar sta;
		sta.InitMapInfo(SCREEN_WIDTH / cell, SCREEN_HEIGHT / cell);
		point bpos, tpos;
		
		
		for (int i = 0; i < tanks.size(); i++)
		{
			if (tanks[i]->ID == 0)
			{
				bpos = terrain::getPointInMap(b.m_centre);
				tpos = terrain::getPointInMap(tanks[i]->m_centre);
				sta.InitPOINTInfo({ bpos.x, bpos.y }, {tpos.x, tpos.y });
				break;
			}
		}
		//��ȡ·��
		if (sta.FindPath())
		{
			sta.GetPath();
		}
		//�õ�·�߱����һ���ӵ�����
		b.m_dir = sta.getNextDir();
		
		//�ӵ��ƶ�
		switch (b.m_dir)
		{
		case Up:b.m_centre.y -= STEP*10; break;
		case Down:b.m_centre.y += STEP*10; break;
		case Left:b.m_centre.x -= STEP*10; break;
		case Right:b.m_centre.x += STEP*10; break;
		default:break;
		}
	}
	drawBullet(b);

	return result;
}


/***********************************
beShooted:�����е�Ч��
isPlayerBullet:�Ƿ�Ϊ����ӵ�
����ֵ:�Ƿ�������
***********************************/
bool tank::beShooted(bool isPlayerBullet)
{
	//��������ѷ�̹��
	if ((isPlayerBullet && this->isPlayer) || (!isPlayerBullet && !this->isPlayer))
	{
		this->displayTank();
		this->drawTank(this->m_centre);
		return false;
	}
	this->m_blood--;
	if (this->ID == 1 || this->ID == 2)
	{
		int high = (this->ID == 1 ? 20 : 170);
		if (this->m_blood == 0) putimage(SCREEN_WIDTH + 20, high, &this->scorecard_star0, SRCCOPY);
		if (this->m_blood == 1) putimage(SCREEN_WIDTH + 20, high, &this->scorecard_star1, SRCCOPY);
		if (this->m_blood == 2) putimage(SCREEN_WIDTH + 20, high, &this->scorecard_star2, SRCCOPY);
		if (this->m_blood == 3) putimage(SCREEN_WIDTH + 20, high, &this->scorecard_star3, SRCCOPY);
		if (this->m_blood == 4) putimage(SCREEN_WIDTH + 20, high, &this->scorecard_star4, SRCCOPY);
		if (this->m_blood == 5) putimage(SCREEN_WIDTH + 20, high, &this->scorecard_star5, SRCCOPY);
		this->updateScore(this->ID);
	}
	if (this->m_blood == 0)
	{
		//����
		return true;
	}
	this->displayTank();
	this->drawTank(this->m_centre);
	return false;

}
/***********************************
shootTerrain:�����ϰ���
x,y:��ͼ�±�
return:�Ƿ�ɾ���ӵ�
***********************************/
bool tank::shootTerrain(int x, int y)
{
	Terrain ter = (Terrain)map[x][y];
	Terrain t = �յ�;
	bool isDel = false;
	switch (ter)
	{
	case �յ�:
		return false;
	case ��ש:
		t = �յ�;
		isDel = true;
		break;
	case ��ש:
		t = ��ש;
		isDel = true;
		break;
	case ����:
		t = ����;
		isDel = false;
		break;
	case ɭ��:
		t = ɭ��;
		isDel = false;
		break;
	case ��Ӫ����:
	case ��Ӫ:
		Tool::sound(4);
		t = ��Ӫ;
		isGameOver = true;
		isDel = true;
		map[SCREEN_WIDTH / cell / 2 - 1][SCREEN_HEIGHT / cell - 2] = �ñ�Ӫ;
		terrain::reDraw(SCREEN_WIDTH / cell / 2 - 1, SCREEN_HEIGHT / cell - 2);
		boom.push_back(point((SCREEN_WIDTH / cell / 2 - 1)*cell + 25, (SCREEN_HEIGHT / cell - 2)*cell + 10));
		break;
	case ռλ��:
		t = ռλ��;
		isDel = true;
		break;
	default:
		t = �յ�;
		isDel = true;
		break;
	}
	map[x][y] = t;
	terrain tt;
	tt.addTerrain(x, y, t);
	return isDel;
}

//��ȡ̹�˵�ǰ����
Direction tank::m_dir()
{
	return this->dir;
}

//���ظ�ֵ�����
tank& tank::operator=(tank & t)
{
	this->score = t.score;
	this->m_blood = t.m_blood;
	return *this;
}

/******************
����:̹������
******************/
void tank::revive()
{
	for (int i = 0; i < tanks.size(); i++)
	{
		if (tanks[i]->ID == this->ID)
		{
			tank *ptank = new tank_player((Tank)(this->ID - 1));
			*ptank = *tanks[i];
			//����̹��
			tanks[i]->displayTank();
			//�ͷ�̹����Դ
			delete tanks[i];
			//��̹�˳���ɾ����̹��
			//vector<::tank*>::iterator   iter = tanks.begin() + i;
			//tanks.erase(iter);
			tborn.push_back(ptank);
		}
	}
}

/**********************
̹����Ϣ����
**********************/
void tank::copy(const _STANK & t)
{
	this->aits_1 = t.aits_1;
	this->aits_2 = t.aits_2;
	this->cborn1 = t.cborn1;
	this->cborn2 = t.cborn2;
	this->d = t.d;
	this->dir = t.dir;
	//this->DownImg = t.DownImg;
	this->downKey = t.downKey;
	this->ID = t.ID;
	this->isPlayer = t.isPlayer;
	//this->LeftImg = t.LeftImg;
	this->leftKey = t.leftKey;
	this->m_blood = t.m_blood;

	for (int i = 0; i < t.bulletCount; i++)
	{
		this->m_bulletList.push_back(t.m_bulletList[i]);
	}
	this->m_bulletSpeed = t.m_bulletSpeed;
	this->m_centre = t.m_centre;
	this->m_model = t.m_model;
	this->m_moveSpeed = t.m_moveSpeed;
	this->m_shootInterval = t.m_shootInterval;

	this->rightKey = t.rightKey;
	this->score = t.score;
	//this->scorecard_star0 = t.scorecard_star0;
	//this->scorecard_star1 = t.scorecard_star1;
	//this->scorecard_star2 = t.scorecard_star2;
	//this->scorecard_star3 = t.scorecard_star3;
	//this->scorecard_star4 = t.scorecard_star4;
	this->shootKey = t.shootKey;
	this->step = t.step;
	this->tankType = t.tankType;
	this->tb_1 = t.tb_1;
	this->tb_2 = t.tb_2;
	this->ts_1 = t.ts_1;
	this->ts_2 = t.ts_2;
	this->tt_1 = t.tt_1;
	this->tt_2 = t.tt_2;
	//this->UpImg = t.UpImg;
	this->upKey = t.upKey;
}

/**************************************************�ָ���**************************************************/
/**************************************************�ָ���**************************************************/
/**************************************************�ָ���**************************************************/


//���������̹�˹��캯��������
tank_player::tank_player(Tank t)
{
	score = 0;
	isPlayer = true;
	dir = Up;
	m_model = tank_model;
	m_bulletColor = DARKGRAY;
	m_moveSpeed = 60;
	m_bulletSpeed = 1000;
	m_shootInterval = 200;
	m_blood = 5;
	this->tankType = t;

	switch (t)
	{
	case ���̹��1:
		m_centre.x = SCREEN_WIDTH / 2 - cell * 4;
		m_centre.y = 755;
		upKey = 87;//W
		downKey = 83;//S
		leftKey = 65;//A
		rightKey = 68;//D
		shootKey = 74;//J
		switchBullet = 75;//K
		ID = 1;
		loadimage(&UpImg, _T("IMG/tank/p1_up.gif"), tank_model * 2, tank_model * 2, true);
		loadimage(&DownImg, _T("IMG/tank/p1_down.gif"), tank_model * 2, tank_model * 2, true);
		loadimage(&LeftImg, _T("IMG/tank/p1_left.gif"), tank_model * 2, tank_model * 2, true);
		loadimage(&RightImg, _T("IMG/tank/p1_right.gif"), tank_model * 2, tank_model * 2, true);

		loadimage(&scorecard_star0, _T("IMG/tank/scorecard1_star0.png"), 260, 140, true);
		loadimage(&scorecard_star1, _T("IMG/tank/scorecard1_star1.png"), 260, 140, true);
		loadimage(&scorecard_star2, _T("IMG/tank/scorecard1_star2.png"), 260, 140, true);
		loadimage(&scorecard_star3, _T("IMG/tank/scorecard1_star3.png"), 260, 140, true);
		loadimage(&scorecard_star4, _T("IMG/tank/scorecard1_star4.png"), 260, 140, true);
		loadimage(&scorecard_star5, _T("IMG/tank/scorecard1_star5.png"), 260, 140, true);
		break;
	case ���̹��2:
		m_centre.x = SCREEN_WIDTH / 2 + cell * 4;
		m_centre.y = 755;
		upKey = 38;//��
		downKey = 40;//��
		leftKey = 37;//��
		rightKey = 39;//��
		shootKey = 97;//1
		switchBullet = 50;//2
		ID = 2;
		loadimage(&UpImg, _T("IMG/tank/p2_up.gif"), tank_model * 2, tank_model * 2, true);
		loadimage(&DownImg, _T("IMG/tank/p2_down.gif"), tank_model * 2, tank_model * 2, true);
		loadimage(&LeftImg, _T("IMG/tank/p2_left.gif"), tank_model * 2, tank_model * 2, true);
		loadimage(&RightImg, _T("IMG/tank/p2_right.gif"), tank_model * 2, tank_model * 2, true);

		loadimage(&scorecard_star0, _T("IMG/tank/scorecard2_star0.png"), 270, 154, true);
		loadimage(&scorecard_star1, _T("IMG/tank/scorecard2_star1.png"), 270, 154, true);
		loadimage(&scorecard_star2, _T("IMG/tank/scorecard2_star2.png"), 270, 154, true);
		loadimage(&scorecard_star3, _T("IMG/tank/scorecard2_star3.png"), 270, 154, true);
		loadimage(&scorecard_star4, _T("IMG/tank/scorecard2_star4.png"), 270, 154, true);
		loadimage(&scorecard_star5, _T("IMG/tank/scorecard2_star5.png"), 270, 154, true);
		break;
	}


}
tank_player::~tank_player()
{

}

//���������̹����������������


/**************************************************�ָ���**************************************************/
/**************************************************�ָ���**************************************************/
/**************************************************�ָ���**************************************************/


//������AI̹�˹��캯��������
tank_computer::tank_computer()
{

}
tank_computer::tank_computer(Tank t)
{

	this->isPlayer = false;
	m_bulletSpeed = 300;
	m_shootInterval = 200;
	point pos;
	step = 3;
	d = Down;
	this->tankType = t;
	int num = rand() % 3;
	switch (num)
	{
	case 0:
		pos.x = 25;
		pos.y = 25;
		break;
	case 1:
		pos.x = SCREEN_WIDTH / 2;
		pos.y = 25;
		break;
	case 2:
		pos.x = SCREEN_WIDTH - 25;
		pos.y = 25;
		break;
	default:break;
	}

	switch (t)
	{
	case AI̹��1:
		m_moveSpeed = 60;
		m_blood = 3;
		m_centre.x = pos.x;
		m_centre.y = pos.y;
		loadimage(&UpImg, _T("IMG/gray-tank/c1_up.gif"), tank_model * 2, tank_model * 2, true);
		loadimage(&DownImg, _T("IMG/gray-tank/c1_down.gif"), tank_model * 2, tank_model * 2, true);
		loadimage(&LeftImg, _T("IMG/gray-tank/c1_left.gif"), tank_model * 2, tank_model * 2, true);
		loadimage(&RightImg, _T("IMG/gray-tank/c1_right.gif"), tank_model * 2, tank_model * 2, true);
		break;
	case AI̹��2:
		m_moveSpeed = 80;
		m_blood = 2;
		m_centre.x = pos.x;
		m_centre.y = pos.y;
		loadimage(&UpImg, _T("IMG/gray-tank/c2_up.gif"), tank_model * 2, tank_model * 2, true);
		loadimage(&DownImg, _T("IMG/gray-tank/c2_down.gif"), tank_model * 2, tank_model * 2, true);
		loadimage(&LeftImg, _T("IMG/gray-tank/c2_left.gif"), tank_model * 2, tank_model * 2, true);
		loadimage(&RightImg, _T("IMG/gray-tank/c2_right.gif"), tank_model * 2, tank_model * 2, true);
		break;
	case AI̹��3:
		m_moveSpeed = 40;
		m_blood = 5;
		m_centre.x = pos.x;
		m_centre.y = pos.y;
		loadimage(&UpImg, _T("IMG/gray-tank/c3_up.gif"), tank_model * 2, tank_model * 2, true);
		loadimage(&DownImg, _T("IMG/gray-tank/c3_down.gif"), tank_model * 2, tank_model * 2, true);
		loadimage(&LeftImg, _T("IMG/gray-tank/c3_left.gif"), tank_model * 2, tank_model * 2, true);
		loadimage(&RightImg, _T("IMG/gray-tank/c3_right.gif"), tank_model * 2, tank_model * 2, true);
		break;
	default:
		break;
	}

}

tank_computer::~tank_computer()
{
}
//������AI̹����������������


/**************************************************�ָ���**************************************************/
/**************************************************�ָ���**************************************************/
/**************************************************�ָ���**************************************************/



