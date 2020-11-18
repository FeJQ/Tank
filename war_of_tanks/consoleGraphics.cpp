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
Create:创建画布
********************/
void consoleGraphics::Create()
{
	
	initgraph(m_screen_width+300, m_screen_height);	
	//设置缩放因子(目前有点问题,所以只用默认的1,1)
	setaspectratio(1, 1);
}

/*******************
Destroy:销毁画布
*******************/
void consoleGraphics::Destroy()
{
	closegraph();
}

/**************************
GetScreenWidth:获取屏幕宽度
**************************/
int consoleGraphics::GetScreenWidth()
{
	return m_screen_width;
}

/**************************
GetScreenHeight:获取屏幕高度
**************************/
int consoleGraphics::GetScreenHeight()
{
	return m_screen_height;
}
