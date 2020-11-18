#include "pch.h"
#include "consoleGraphics.h"

int consoleGraphics::m_screen_width = SCREEN_WIDTH;
int consoleGraphics::m_screen_height = SCREEN_HEIGHT;

consoleGraphics::consoleGraphics()
{
}


consoleGraphics::~consoleGraphics()
{
}

/********************
Create:��������
********************/
void consoleGraphics::Create()
{
	
	initgraph(m_screen_width+300, m_screen_height);	
	//������������(Ŀǰ�е�����,����ֻ��Ĭ�ϵ�1,1)
	setaspectratio(1, 1);
}

/*******************
Destroy:���ٻ���
*******************/
void consoleGraphics::Destroy()
{
	closegraph();
}

/**************************
GetScreenWidth:��ȡ��Ļ���
**************************/
int consoleGraphics::GetScreenWidth()
{
	return m_screen_width;
}

/**************************
GetScreenHeight:��ȡ��Ļ�߶�
**************************/
int consoleGraphics::GetScreenHeight()
{
	return m_screen_height;
}
