#pragma once

#include "UIDefine.h"

class Color
{
public:
    Color();
    Color(byte a, byte r, byte g, byte b);
    ~Color();

    void setValue(int argb);
    int getValue() const;

	byte getA();
	byte getR();
	byte getG();
	byte getB();

private:
    int _color;
};