#include "pch.h"
#include "Astar.h"
#include "terrain.h"
#include "terrainType.h"
CAstar::CAstar()
{
}


CAstar::~CAstar()
{
}

//************************************
// Method:    InitMapInfo 初始化地图信息
// FullName:  CAstar::InitMapInfo
// Access:    public 
// Returns:   void
// Parameter: char * pMap
// Parameter: int nHigh
// Parameter: int nWidth
// Parameter: int nBlock
//************************************
void CAstar::InitMapInfo(int nHigh, int nWidth)
{
	m_pMap = *map;
	m_MapH = nHigh;
	m_MapW = nWidth;
	m_bInitMapInfo = true;

	//==============
	m_pTempMap = new TEMP_MAP[nHigh*nWidth]{};

}

//************************************
// Method:    InitPOINTInfo 初始化起始坐标
// FullName:  CAstar::InitPOINTInfo
// Access:    public 
// Returns:   void
// Parameter: POINT codStart
// Parameter: POINT codEnd
//************************************
void CAstar::InitPOINTInfo(POINT codStart, POINT codEnd)
{
	m_Start = codStart;
	m_End = codEnd;
	m_bInitPOINTInfo = true;
}

//************************************
// Method:    FindPath 寻找包含最短路径的坐标点（填充close表）
// FullName:  CAstar::FindPath
// Access:    public 
// Returns:   bool
//************************************
bool CAstar::FindPath()
{
	//是否准备就绪
	if (!m_bInitPOINTInfo ||
		!m_bInitMapInfo)
	{
		printf("未初始化完毕\n");
		return false;
	}
	/*
	   寻路过程：
	   1. 初始化起点
	   2. 把起点填充到open表中
	   3. 判断open表是否为空（说明没找到）
	   4. 从open表中找到一个F值最小的点，进行扩散
	   5. 把扩散过的点添加到close表中，并从open表删除
	   6. 检测扩散出来的点是否存在重点，如果不是，就检测
		  是否可以添加到open表中
		  6.1 是否是终点（是，就直接返回true）
		  6.2 是否越界
		  6.3 是否是障碍物
		  6.4 是否在open表中
		  6.5 是否在close表中
	   7. 把检测合格点添加到open表中
	   8. 重复3 - 7步
	*/
	//清空上次查找的点
	m_Open.clear();
	m_Close.clear();
	memset(m_pTempMap, 0, m_MapW*m_MapH);

	NODE_INFO startNode;
	startNode.codSelf = m_Start;
	startNode.g = 0;
	startNode.SetH_F(m_End);

	//加入到open表中
	m_Open.push_back(startNode);
	m_pTempMap[startNode.codSelf.y* m_MapW + startNode.codSelf.x].isOpen = true;

	while (true)
	{
		//open表是否为空，为空就退出
		if (m_Open.empty())
		{
			return false;//没找到路径
		}
		//从open表中找F值最小
		int nIndex = 0;
		for (int i = 1; i < m_Open.size(); i++)
		{
			//open表中至少由两个点才能循环
			if (m_Open[nIndex].f > m_Open[i].f)
			{
				nIndex = i;
			}
		}
		//此时nIndex就是open表中F值最小的一个点
		//使用此点进行扩散（4个点）
		NODE_INFO newNode[4] = {};
		//上
		newNode[0].codSelf.x = m_Open[nIndex].codSelf.x;
		newNode[0].codSelf.y = m_Open[nIndex].codSelf.y - 1;

		//下
		newNode[1].codSelf.x = m_Open[nIndex].codSelf.x;
		newNode[1].codSelf.y = m_Open[nIndex].codSelf.y + 1;
		//左
		newNode[2].codSelf.x = m_Open[nIndex].codSelf.x - 1;
		newNode[2].codSelf.y = m_Open[nIndex].codSelf.y;
		//右
		newNode[3].codSelf.x = m_Open[nIndex].codSelf.x + 1;
		newNode[3].codSelf.y = m_Open[nIndex].codSelf.y;

		for (int i = 0; i < 4; i++)
		{
			newNode[i].codParent = m_Open[nIndex].codSelf;
			newNode[i].g = m_Open[nIndex].g + 1;
			newNode[i].SetH_F(m_End);
			newNode[i].codSelf.d = (Direction)i; //自身方向
		}

		//添加扩散点到close表中
		m_pTempMap[m_Open[nIndex].codSelf.y* m_MapW + m_Open[nIndex].codSelf.x].isClose = true;
		m_pTempMap[m_Open[nIndex].codSelf.y* m_MapW + m_Open[nIndex].codSelf.x].isOpen = false;

		m_Close.push_back(m_Open[nIndex]);
		m_Open.erase(m_Open.begin() + nIndex);

		//检测扩散出来的点是否存在终点或是否可以添加到open表中
		for (int i = 0; i < 4; i++)
		{
			int x = newNode[i].codSelf.x;
			int y = newNode[i].codSelf.y;

			//是否是终点
			if (newNode[i].codSelf == m_End)
			{
				//保存终点到close表中
				m_Close.push_back(newNode[i]);
				return true;
			}
			//是否越界
			if (x <= 0 || x >= m_MapW ||
				y <= 0 || y >= m_MapH)
			{
				continue;//继续检测下一个点
			}
			//是否是障碍物
/*
			 char map[3][3] =
			   1 2 3
			   4 5 6
			   7 8 9
			  char* p = (char*)map
			  p[4] --> 5
			  [w*y + x] = 4
*/

			/*if (m_pMap[m_MapW* y + x] == Terrain::金砖 || m_pMap[m_MapW* y + x] == Terrain::大本营 || m_pMap[m_MapW* y + x] == Terrain::大本营副本 ||
				m_pMap[m_MapW* y + x] == Terrain::烂本营 || m_pMap[m_MapW* y + x] == Terrain::土砖 || m_pMap[m_MapW* y + x] == Terrain::占位格)
			{
				continue;
			}*/
			if (m_pMap[m_MapW* y + x] == Terrain::金砖 || m_pMap[m_MapW* y + x] == Terrain::大本营 || m_pMap[m_MapW* y + x] == Terrain::土砖 )
			{
				continue;
			}

			if (m_pTempMap[m_MapW* y + x].isOpen ||
				m_pTempMap[m_MapW* y + x].isClose)
			{
				continue;
			}

			// 			是否在open表中
			// 							bool bRet = false;
			// 							for (int o = 0; o < m_Open.size();o++)
			// 							{
			// 								if (m_Open[o].codSelf == 
			// 									newNode[i].codSelf)
			// 								{
			// 									bRet = true;
			// 									break;
			// 								}
			// 							}
			// 							if (bRet)
			// 								continue;
			// 							//是否在close表中
			// 							bRet = false;
			// 							for (int o = 0; o < m_Close.size(); o++)
			// 							{
			// 								if (m_Close[o].codSelf ==
			// 									newNode[i].codSelf)
			// 								{
			// 									bRet = true;
			// 									break;
			// 								}
			// 							}
			// 							if (bRet)
			// 								continue;

						//通过检测点加入到open表中
			m_Open.push_back(newNode[i]);

			m_pTempMap[newNode[i].codSelf.y* m_MapW + newNode[i].codSelf.x].isOpen = true;

		}
	}
	return true;
}

/*******************************
获取最短路径的第一个坐标
*******************************/
point CAstar::getPathFirstPoint()
{
	if (m_Path.size() > 0)
	{
		point p;
		p.x = m_Path[m_Path.size() - 1].x;
		p.y = m_Path[m_Path.size() - 1].y;
		return p;
	}
	return point();
}

/****************************
获取下一步方向
***************************/
Direction CAstar::getNextDir()
{
	if (m_Path.size() > 0)
	{
		return m_Path[m_Path.size() - 1].d;
	}
	return Direction();
}


//************************************
// Method:    GetPath 获取最短路径
// FullName:  CAstar::GetPath
// Access:    public 
// Returns:   void
//************************************
void CAstar::GetPath()
{
	//清空上次的路径
	m_Path.clear();
	//通过终点回溯找到起点（通过其父节点查找）
	int nIndex = m_Close.size() - 1;//最后一个点的下标（终点下标）
	while (true)
	{
		for (int i = 0; i < m_Close.size(); i++)
		{
			if (m_Close[nIndex].codParent == m_Start)
			{
				//如果父节点是起点，说明找完了
				return;
			}
			//找自身的父节点
			if (m_Close[nIndex].codParent == m_Close[i].codSelf)
			{
				//找到父节点后，将此父节点坐标添加到m_Path中
				m_Path.push_back(m_Close[i].codSelf);
				//setfillcolor(YELLOW);
				//solidrectangle(m_Close[i].codSelf.x*cell, m_Close[i].codSelf.y*cell, (m_Close[i].codSelf.x+1)*cell, (m_Close[i].codSelf.y+1)*cell);
				//将nIndex赋值为父节点的下标，继续找父节点的父节点
				nIndex = i;
				break;
			}
		}
	}
}