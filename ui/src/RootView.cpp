#include "UIDefine.h"
#include "RootView.h"
#include "widget.h"

RootView::RootView()
{

}

RootView::~RootView()
{

}

void RootView::init(Widget* widget, int width, int height)
{
	INVALID_POINTER_RETURN(widget);
    setRect(KRect(0, 0, width, height));
	_widget = widget;
    View::init();
}

void RootView::OnDraw()
{
    draw();
}

void RootView::schedulePaint(KRect* rect)
{
	INVALID_POINTER_RETURN(_widget);

	if (nullptr == rect)
	{
		KRect rcRootView;
		getRect(rcRootView);
		_widget->schedualPaint(rcRootView);
	}
	else
	{
		_widget->schedualPaint(*rect);
	}
}
