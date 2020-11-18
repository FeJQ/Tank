#pragma once
#include <graphics.h>
#define SCREEN_WIDTH    1050   //宽度
#define SCREEN_HEIGHT   775    //高度
#define Aspect_Ratio    1.5    //缩放因子
class consoleGraphics
{
	public:
		consoleGraphics();
		~consoleGraphics();
		//创建画布
		static void Create();
		//销毁画布
		static void Destroy();
		//获取屏幕宽度
		static int GetScreenWidth();
		//获取屏幕高度
		static int GetScreenHeight();
	private:
		//宽度
		static int m_screen_width;
		//高度
		static int m_screen_height;
};

