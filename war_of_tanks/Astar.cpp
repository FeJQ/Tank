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
// Method:    InitMapInfo ��ʼ����ͼ��Ϣ
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
// Method:    InitPOINTInfo ��ʼ����ʼ����
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
// Method:    FindPath Ѱ�Ұ������·��������㣨���close��
// FullName:  CAstar::FindPath
// Access:    public 
// Returns:   bool
//************************************
bool CAstar::FindPath()
{
	//�Ƿ�׼������
	if (!m_bInitPOINTInfo ||
		!m_bInitMapInfo)
	{
		printf("δ��ʼ�����\n");
		return false;
	}
	/*
	   Ѱ·���̣�
	   1. ��ʼ�����
	   2. �������䵽open����
	   3. �ж�open���Ƿ�Ϊ�գ�˵��û�ҵ���
	   4. ��open�����ҵ�һ��Fֵ��С�ĵ㣬������ɢ
	   5. ����ɢ���ĵ���ӵ�close���У�����open��ɾ��
	   6. �����ɢ�����ĵ��Ƿ�����ص㣬������ǣ��ͼ��
		  �Ƿ������ӵ�open����
		  6.1 �Ƿ����յ㣨�ǣ���ֱ�ӷ���true��
		  6.2 �Ƿ�Խ��
		  6.3 �Ƿ����ϰ���
		  6.4 �Ƿ���open����
		  6.5 �Ƿ���close����
	   7. �Ѽ��ϸ����ӵ�open����
	   8. �ظ�3 - 7��
	*/
	//����ϴβ��ҵĵ�
	m_Open.clear();
	m_Close.clear();
	memset(m_pTempMap, 0, m_MapW*m_MapH);

	NODE_INFO startNode;
	startNode.codSelf = m_Start;
	startNode.g = 0;
	startNode.SetH_F(m_End);

	//���뵽open����
	m_Open.push_back(startNode);
	m_pTempMap[startNode.codSelf.y* m_MapW + startNode.codSelf.x].isOpen = true;

	while (true)
	{
		//open���Ƿ�Ϊ�գ�Ϊ�վ��˳�
		if (m_Open.empty())
		{
			return false;//û�ҵ�·��
		}
		//��open������Fֵ��С
		int nIndex = 0;
		for (int i = 1; i < m_Open.size(); i++)
		{
			//open�������������������ѭ��
			if (m_Open[nIndex].f > m_Open[i].f)
			{
				nIndex = i;
			}
		}
		//��ʱnIndex����open����Fֵ��С��һ����
		//ʹ�ô˵������ɢ��4���㣩
		NODE_INFO newNode[4] = {};
		//��
		newNode[0].codSelf.x = m_Open[nIndex].codSelf.x;
		newNode[0].codSelf.y = m_Open[nIndex].codSelf.y - 1;

		//��
		newNode[1].codSelf.x = m_Open[nIndex].codSelf.x;
		newNode[1].codSelf.y = m_Open[nIndex].codSelf.y + 1;
		//��
		newNode[2].codSelf.x = m_Open[nIndex].codSelf.x - 1;
		newNode[2].codSelf.y = m_Open[nIndex].codSelf.y;
		//��
		newNode[3].codSelf.x = m_Open[nIndex].codSelf.x + 1;
		newNode[3].codSelf.y = m_Open[nIndex].codSelf.y;

		for (int i = 0; i < 4; i++)
		{
			newNode[i].codParent = m_Open[nIndex].codSelf;
			newNode[i].g = m_Open[nIndex].g + 1;
			newNode[i].SetH_F(m_End);
			newNode[i].codSelf.d = (Direction)i; //������
		}

		//�����ɢ�㵽close����
		m_pTempMap[m_Open[nIndex].codSelf.y* m_MapW + m_Open[nIndex].codSelf.x].isClose = true;
		m_pTempMap[m_Open[nIndex].codSelf.y* m_MapW + m_Open[nIndex].codSelf.x].isOpen = false;

		m_Close.push_back(m_Open[nIndex]);
		m_Open.erase(m_Open.begin() + nIndex);

		//�����ɢ�����ĵ��Ƿ�����յ���Ƿ������ӵ�open����
		for (int i = 0; i < 4; i++)
		{
			int x = newNode[i].codSelf.x;
			int y = newNode[i].codSelf.y;

			//�Ƿ����յ�
			if (newNode[i].codSelf == m_End)
			{
				//�����յ㵽close����
				m_Close.push_back(newNode[i]);
				return true;
			}
			//�Ƿ�Խ��
			if (x <= 0 || x >= m_MapW ||
				y <= 0 || y >= m_MapH)
			{
				continue;//���������һ����
			}
			//�Ƿ����ϰ���
/*
			 char map[3][3] =
			   1 2 3
			   4 5 6
			   7 8 9
			  char* p = (char*)map
			  p[4] --> 5
			  [w*y + x] = 4
*/

			/*if (m_pMap[m_MapW* y + x] == Terrain::��ש || m_pMap[m_MapW* y + x] == Terrain::��Ӫ || m_pMap[m_MapW* y + x] == Terrain::��Ӫ���� ||
				m_pMap[m_MapW* y + x] == Terrain::�ñ�Ӫ || m_pMap[m_MapW* y + x] == Terrain::��ש || m_pMap[m_MapW* y + x] == Terrain::ռλ��)
			{
				continue;
			}*/
			if (m_pMap[m_MapW* y + x] == Terrain::��ש || m_pMap[m_MapW* y + x] == Terrain::��Ӫ || m_pMap[m_MapW* y + x] == Terrain::��ש )
			{
				continue;
			}

			if (m_pTempMap[m_MapW* y + x].isOpen ||
				m_pTempMap[m_MapW* y + x].isClose)
			{
				continue;
			}

			// 			�Ƿ���open����
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
			// 							//�Ƿ���close����
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

						//ͨ��������뵽open����
			m_Open.push_back(newNode[i]);

			m_pTempMap[newNode[i].codSelf.y* m_MapW + newNode[i].codSelf.x].isOpen = true;

		}
	}
	return true;
}

/*******************************
��ȡ���·���ĵ�һ������
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
��ȡ��һ������
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
// Method:    GetPath ��ȡ���·��
// FullName:  CAstar::GetPath
// Access:    public 
// Returns:   void
//************************************
void CAstar::GetPath()
{
	//����ϴε�·��
	m_Path.clear();
	//ͨ���յ�����ҵ���㣨ͨ���丸�ڵ���ң�
	int nIndex = m_Close.size() - 1;//���һ������±꣨�յ��±꣩
	while (true)
	{
		for (int i = 0; i < m_Close.size(); i++)
		{
			if (m_Close[nIndex].codParent == m_Start)
			{
				//������ڵ�����㣬˵��������
				return;
			}
			//������ĸ��ڵ�
			if (m_Close[nIndex].codParent == m_Close[i].codSelf)
			{
				//�ҵ����ڵ�󣬽��˸��ڵ�������ӵ�m_Path��
				m_Path.push_back(m_Close[i].codSelf);
				//setfillcolor(YELLOW);
				//solidrectangle(m_Close[i].codSelf.x*cell, m_Close[i].codSelf.y*cell, (m_Close[i].codSelf.x+1)*cell, (m_Close[i].codSelf.y+1)*cell);
				//��nIndex��ֵΪ���ڵ���±꣬�����Ҹ��ڵ�ĸ��ڵ�
				nIndex = i;
				break;
			}
		}
	}
}