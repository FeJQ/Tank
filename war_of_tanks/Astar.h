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

	//�Զ��������ṹ��
	typedef struct _MY_POINT :public POINT
	{
		//���صȺ������������Ƚ�
		bool operator==(POINT cod)
		{
			return (x == cod.x) && (y == cod.y);
		}
		//���ظ�ֵ����������㸳ֵ
		void operator=(POINT cod)
		{
			x = cod.x;
			y = cod.y;
		}
		Direction d; //����㷽��
	}MY_POINT, *PMY_POINT;

	//�ڵ����Ϣ�ṹ��
	typedef struct _NODE_INFO
	{
		int g;//�ƶ���ģ�ÿһ��һ�μ�1��
		int h;//�����յ���̾���
		int f;//g+h

		void SetH_F(POINT cod2)
		{
			h = abs(codSelf.x - cod2.x) + abs(codSelf.y - cod2.y);
			f = g + h;
		}

		MY_POINT codSelf;  //��������
		MY_POINT codParent;//�������(��˭��ɢ�����ĵ������)
	}NODE_INFO, *PNODE_INFO;

private:
	vector<NODE_INFO> m_Open;  //�����ĵ�ļ���
	vector<NODE_INFO> m_Close; //�����ĵ㣨��ɢ���ĵ㣩�ļ���
	vector<MY_POINT> m_Path;   //���·�� 

	//int m_Block[3];  //��ͼ�е��ϰ���
	int m_MapH;   //��ͼ�߶�
	int m_MapW;   //��ͼ���
	int* m_pMap; //��ͼ�׵�ַ

	POINT m_Start; //�������
	POINT m_End;   //�յ�����

	bool m_bInitMapInfo;   //�Ƿ��ʼ����ͼ��Ϣ
	bool m_bInitPOINTInfo; //�Ƿ��ʼ����ʼ����
public:
	void InitMapInfo( int nHigh, int nWidth);
	void InitPOINTInfo(POINT codStart, POINT codEnd);

	void GetPath();  //��ȡ���·��
	bool FindPath(); //Ѱ�Ұ������·���ĵ�

	typedef struct _TEMP_MAP
	{
		char isOpen : 1;
		char isClose : 1;
		char recver : 6;
	}TEMP_MAP, *PTEMP_MAP;

	PTEMP_MAP m_pTempMap;
	//��ȡ���·���ĵ�һ����
	point getPathFirstPoint();
	//��ȡ��һ������
	Direction getNextDir();
};

