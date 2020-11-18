#pragma once
#include <vector>
using std::vector;
#include <windows.h>
#include "point.h"
#include "direction.h"
class CAstar
{
public:
	CAstar();
	~CAstar();

	//自定义的坐标结构体
	typedef struct _MY_POINT :public POINT
	{
		//重载等号运算符，方便比较
		bool operator==(POINT cod)
		{
			return (x == cod.x) && (y == cod.y);
		}
		//重载赋值运算符，方便赋值
		void operator=(POINT cod)
		{
			x = cod.x;
			y = cod.y;
		}
		Direction d; //坐标点方向
	}MY_POINT, *PMY_POINT;

	//节点的信息结构体
	typedef struct _NODE_INFO
	{
		int g;//移动损耗（每一动一次加1）
		int h;//距离终点最短距离
		int f;//g+h

		void SetH_F(POINT cod2)
		{
			h = abs(codSelf.x - cod2.x) + abs(codSelf.y - cod2.y);
			f = g + h;
		}

		MY_POINT codSelf;  //自身坐标
		MY_POINT codParent;//父坐标点(由谁扩散出来的点的坐标)
	}NODE_INFO, *PNODE_INFO;

private:
	vector<NODE_INFO> m_Open;  //代检测的点的集合
	vector<NODE_INFO> m_Close; //检测过的点（扩散过的点）的集合
	vector<MY_POINT> m_Path;   //最短路径 

	//int m_Block[3];  //地图中的障碍物
	int m_MapH;   //地图高度
	int m_MapW;   //地图宽度
	int* m_pMap; //地图首地址

	POINT m_Start; //起点坐标
	POINT m_End;   //终点坐标

	bool m_bInitMapInfo;   //是否初始化地图信息
	bool m_bInitPOINTInfo; //是否初始化起始坐标
public:
	void InitMapInfo( int nHigh, int nWidth);
	void InitPOINTInfo(POINT codStart, POINT codEnd);

	void GetPath();  //获取最短路径
	bool FindPath(); //寻找包含最短路径的点

	typedef struct _TEMP_MAP
	{
		char isOpen : 1;
		char isClose : 1;
		char recver : 6;
	}TEMP_MAP, *PTEMP_MAP;

	PTEMP_MAP m_pTempMap;
	//获取最短路径的第一个点
	point getPathFirstPoint();
	//获取下一步方向
	Direction getNextDir();
};

