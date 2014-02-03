#include "view.h"
#include "UIDefine.h"
#include "Canvas.h"
#include <vector>

typedef std::vector<View*> VECTOR_VIEW;

class ViewDelegate
{
public:
    ViewDelegate::ViewDelegate()
        : _canvas(nullptr)
        , _isShow(true)
		, _parent(nullptr)
    {

    }

    ViewDelegate::~ViewDelegate()
    {

    }

public:
    Canvas* _canvas;
    KRect _rect;
    std::wstring _id;
    VECTOR_VIEW _children;
    bool _isShow;
	View* _parent;
};

View::View()
{
    _viewDelegate = new ViewDelegate;
}

View::~View()
{

}

bool View::draw()
{
    INVALID_POINTER_RETURN_FALSE(_viewDelegate);
    INVALID_POINTER_RETURN_FALSE(_viewDelegate->_canvas);
    VALUE_FALSE_RETURN_FALSE(isUsedCanvas());

    return draw(*(_viewDelegate->_canvas));
}

bool View::draw(Canvas& canvas)
{
    INVALID_POINTER_RETURN_FALSE(_viewDelegate);

    VECTOR_VIEW::iterator iter = _viewDelegate->_children.begin();
    
    for (; iter != _viewDelegate->_children.end(); ++iter)
    {
        if ((*iter)->isShow())
        {
            (*iter)->draw(canvas);
        }
    }

    return true;
}

bool View::addView(View* view)
{
    INVALID_POINTER_RETURN_FALSE(view);
    INVALID_POINTER_RETURN_FALSE(_viewDelegate);

	view->setParent(this);
    _viewDelegate->_children.push_back(view);
    return true;
}

bool View::isShow()
{
    INVALID_POINTER_RETURN_FALSE(_viewDelegate);
    return _viewDelegate->_isShow;
}

void View::show()
{
	INVALID_POINTER_RETURN(_viewDelegate);
	_viewDelegate->_isShow = true;
}

void View::hide()
{
	INVALID_POINTER_RETURN(_viewDelegate);
	_viewDelegate->_isShow = false;
}

Canvas* View::getCanvas()
{
    INVALID_POINTER_RETURN_NULL(_viewDelegate);
    return _viewDelegate->_canvas;
}

bool View::init()
{
    INVALID_POINTER_RETURN_FALSE(_viewDelegate);

    VECTOR_VIEW::iterator iter = _viewDelegate->_children.begin();

    for (; iter != _viewDelegate->_children.end(); ++iter)
    {
        (*iter)->init();
    }

    return true;
}

bool View::initCanvas(int canvasType)
{
    VALUE_FALSE_RETURN_FALSE(isUsedCanvas());
    INVALID_POINTER_RETURN_FALSE(_viewDelegate);

	if (nullptr != _viewDelegate->_canvas)
	{
		delete _viewDelegate->_canvas;
		_viewDelegate->_canvas = nullptr;
	}

    _viewDelegate->_canvas = new Canvas;
    return _viewDelegate->_canvas->init(_viewDelegate->_rect.width(), _viewDelegate->_rect.height(), canvasType);
}

void View::schedulePaint(KRect* rect)
{
	INVALID_POINTER_RETURN(_viewDelegate);
	INVALID_POINTER_RETURN(_viewDelegate->_parent);

	if (nullptr == rect)
	{
		return _viewDelegate->_parent->schedulePaint(&_viewDelegate->_rect);
	}
	else
	{
		return _viewDelegate->_parent->schedulePaint(rect);
	}
}

bool View::getRect(KRect& rect)
{
	INVALID_POINTER_RETURN_FALSE(_viewDelegate);
	rect.set(_viewDelegate->_rect);
	return true;
}

void View::setRect(KRect rect)
{
    INVALID_POINTER_RETURN(_viewDelegate);
    _viewDelegate->_rect = rect;
}

void View::setParent(View* parent)
{
	INVALID_POINTER_RETURN(_viewDelegate);
	INVALID_POINTER_RETURN(parent);

	_viewDelegate->_parent = parent;
}