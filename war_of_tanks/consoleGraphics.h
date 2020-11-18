#pragma once
#include <graphics.h>
#define SCREEN_WIDTH    1050   //���
#define SCREEN_HEIGHT   775    //�߶�
#define Aspect_Ratio    1.5    //��������
class consoleGraphics
{
	public:
		consoleGraphics();
		~consoleGraphics();
		//��������
		static void Create();
		//���ٻ���
		static void Destroy();
		//��ȡ��Ļ���
		static int GetScreenWidth();
		//��ȡ��Ļ�߶�
		static int GetScreenHeight();
	private:
		//���
		static int m_screen_width;
		//�߶�
		static int m_screen_height;
};

