#pragma once

#include <windows.h>

class View;
class KRect;
class WidgetDelegate;

class AK_API Widget
{
public:
    Widget();
    virtual ~Widget();
    virtual void show();
    virtual void center();
    virtual void moveWindow(int x, int y, int width, int height);
    virtual int x();
    virtual int y();
    virtual int width();
    virtual int height();
    virtual bool addView(View* view);
	virtual void startAnimate();
	virtual void stopAnimate();
	virtual void onTimer();
	virtual void drawToWindow();

	void schedualPaint(const KRect& rect);

    /**
     *  ≥ı ºªØªÊ÷∆ø‚
     */
    virtual bool initCanvas(int canvasType);

    LRESULT wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    static Widget* createWindow(int x, int y, int width, int height);

protected:
	virtual LRESULT processKeyDown(WPARAM wparam, LPARAM lparam);
	virtual void init(int x, int y, int width, int height);

private:
	void registerClass();
    void createRootView();
    
private:
    WidgetDelegate* _widgetDeleget;
};