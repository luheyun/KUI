#pragma once

#include "UIDefine.h"

class AK_API Size
{
public:
    Size()
        : _width(0)
        , _height(0)
    {

    }

    Size(int width, int height)
        : _width(width)
        , _height(height)
    {

    }

    ~Size()
    {

    }

public:
    int _width;
    int _height;
};