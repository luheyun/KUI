#pragma once

class KRect
{
public:
    KRect()
        : _left(0)
        , _right(0)
        , _top(0)
        , _bottom(0)
    {

    }

    KRect(int x, int y, int width, int height)
        : _left(x)
        , _right(x + width)
        , _top(y)
        , _bottom(y + height)
    {

    }

    void KRect::set(int left, int top, int right, int bottom)
    {
        _left = left;
        _top = top;
        _right = right;
        _bottom = bottom;
    }

	void KRect::set(const KRect& rect)
	{
		_left = rect._left;
		_top = rect._top;
		_right = rect._right;
		_bottom = rect._bottom;
	}

    ~KRect()
    {

    }

    int width() const
    {
        return _right - _left;
    }

    int height() const
    {
        return _bottom - _top;
    }

public:
    int _left;
    int _top;
    int _right;
    int _bottom;
};