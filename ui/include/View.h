#pragma once

#include "UIDefine.h"
#include "KRect.h"

class ViewDelegate;
class Canvas;

class AK_API View
{
public:
    View();
    virtual ~View();

    virtual bool init();
    virtual bool initCanvas(int canvasType = ak::SkiaGraphics);
    virtual bool draw();
    virtual bool draw(Canvas& canvas);
    virtual bool addView(View* view);
    virtual bool isShow();
	virtual void show();
	virtual void hide();

	void setRect(KRect rect);
    Canvas* getCanvas();

protected:
    virtual bool isUsedCanvas() {return false;}
	virtual void schedulePaint(KRect* rect = nullptr);
	bool getRect(KRect& rect);
	void setParent(View* parent);

protected:
    ViewDelegate* _viewDelegate;
};
