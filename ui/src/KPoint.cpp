#include "KPoint.h"

KPoint::KPoint()
	: _x(0)
	, _y(0)
{

}

KPoint::KPoint(int x, int y)
	: _x(x)
	, _y(y)
{

}

KPoint::~KPoint()
{

}

void KPoint::set(int x, int y)
{
	_x = x;
	_y = y;
}