#pragma once

class Rect
{
public:
    Rect()
        : _left(0)
        , _right(0)
        , _top(0)
        , _bottom(0)
    {

    }

    Rect(int x, int y, int width, int height)
        : _left(x)
        , _right(x + width)
        , _top(y)
        , _bottom(y + height)
    {

    }

    void Rect::set(int left, int top, int right, int bottom)
    {
        _left = left;
        _top = top;
        _right = right;
        _bottom = bottom;
    }

    ~Rect()
    {

    }

    int width()
    {
        return _right - _left;
    }

    int height()
    {
        return _bottom - _top;
    }

public:
    int _left;
    int _top;
    int _right;
    int _bottom;
};