#include "pch.h"
#include "bullet.h"


bullet::bullet()
{
}
bullet::bullet(short int _x, short int _y,Direction _dir,bool _isPlayer)
{
	this->m_centre.x = _x;
	this->m_centre.y = _y;
	this->m_dir = _dir;
	this->isPlayer = _isPlayer;
}
bullet::bullet(short int _x, short int _y, Direction _dir, bool _isPlayer,bool _isAutoFind)
{
	this->m_centre.x = _x;
	this->m_centre.y = _y;
	this->m_dir = _dir;
	this->isPlayer = _isPlayer;
	this->isAutoFind = _isAutoFind;
}

bullet::~bullet()
{
}

bullet & bullet::operator=(const bullet & b)
{
	this->isPlayer = b.isPlayer;
	this->m_centre.copy(b.m_centre);
	this->m_dir = b.m_dir;
	return *this;
	// TODO: 在此处插入 return 语句
}
