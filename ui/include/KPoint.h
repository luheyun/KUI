#pragma once

class KPoint
{
public:
    KPoint();
	KPoint(int x, int y);
    ~KPoint();

	void set(int x, int y);

public:
	int _x;
	int _y;
};