#include "UIDefine.h"
#include "Widget.h"
#include "RootView.h"
#include "KRect.h"
#include "Size.h"
#include "Canvas.h"
#include <map>

extern HINSTANCE g_hInst;								// 当前实例
#define MAX_LOADSTRING 100
wchar_t szTitle[MAX_LOADSTRING] = L"WIDGET";					// 标题栏文本
wchar_t szWindowClass[MAX_LOADSTRING] = L"WIDGET";			// 主窗口类名

const int TIME_ID = 1;

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

std::map<HWND, Widget*> g_mapHwnd2Widget;

class WidgetDelegate
{
public:
    WidgetDelegate::WidgetDelegate(int x, int y, int width, int height)
        : _x(x)
        , _y(y)
        , _width(width)
        , _height(height)
        , _hwnd(nullptr)
        , _bitmap(nullptr)
        , _bits(nullptr)
    {
    }

    WidgetDelegate::~WidgetDelegate()
    {

    }

public:
    int _x;
    int _y;
    int _width;
    int _height;
    RootView _rootView;
    HWND _hwnd;
    HBITMAP _bitmap;
    void* _bits;
};

void CALLBACK timerProc(
  HWND hwnd,
  UINT uMsg,
  UINT_PTR idEvent,
  DWORD dwTime
)
{
    std::map<HWND, Widget*>::iterator iter = g_mapHwnd2Widget.find(hwnd);

    if (iter != g_mapHwnd2Widget.end() && nullptr != iter->second)
    {
	    iter->second->onTimer();
    }
}

Widget::Widget()
    : _widgetDeleget(nullptr)
{
}

Widget::~Widget()
{

}

void Widget::init(int x, int y, int width, int height)
{
    _widgetDeleget = new WidgetDelegate(x, y, width, height);
    registerClass();

    _widgetDeleget->_hwnd = ::CreateWindowEx(WS_EX_LAYERED, szWindowClass, szTitle, WS_POPUP,
        x, y, width, height, NULL, NULL, g_hInst, NULL);

    INVALID_POINTER_RETURN(_widgetDeleget->_hwnd); 
    
    BITMAPINFOHEADER stBmpInfoHeader = { 0 };   

    stBmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);   
    stBmpInfoHeader.biWidth = width;   
    stBmpInfoHeader.biHeight = -height;   
    stBmpInfoHeader.biPlanes = 1;
    stBmpInfoHeader.biBitCount = 32;   
    stBmpInfoHeader.biCompression = BI_RGB;   
    stBmpInfoHeader.biClrUsed = 0;   
    stBmpInfoHeader.biSizeImage = 0;	

    if (nullptr != _widgetDeleget->_bitmap)
    {
        ::DeleteObject(_widgetDeleget->_bitmap);
        _widgetDeleget->_bitmap = nullptr;
    }

    _widgetDeleget->_bitmap = ::CreateDIBSection(NULL, (PBITMAPINFO)&stBmpInfoHeader, DIB_RGB_COLORS, (void**)_widgetDeleget->_bits, NULL, 0);

    g_mapHwnd2Widget.insert(std::make_pair(_widgetDeleget->_hwnd, this));
    
    _widgetDeleget->_rootView.init(this, width, height);
}

void Widget::show()
{
    INVALID_POINTER_RETURN(_widgetDeleget);
    INVALID_POINTER_RETURN(_widgetDeleget->_hwnd);
    ShowWindow(_widgetDeleget->_hwnd, SW_SHOW);
    UpdateWindow(_widgetDeleget->_hwnd);
}

void Widget::center()
{
    INVALID_POINTER_RETURN(_widgetDeleget);
    INVALID_POINTER_RETURN(_widgetDeleget->_hwnd);

    int screenWidth = ::GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = ::GetSystemMetrics(SM_CYSCREEN);
    int x = (screenWidth - _widgetDeleget->_width) / 2;
    int y = (screenHeight - _widgetDeleget->_height) / 2;

    ::MoveWindow(_widgetDeleget->_hwnd, x, y, _widgetDeleget->_width, _widgetDeleget->_height, FALSE);
}

void Widget::moveWindow(int x, int y, int width, int height)
{
    INVALID_POINTER_RETURN(_widgetDeleget);
    INVALID_POINTER_RETURN(_widgetDeleget->_hwnd);
    ::MoveWindow(_widgetDeleget->_hwnd, x, y, width, height, FALSE);
}

int Widget::x()
{
    INVALID_POINTER_RETURN_PARAM(_widgetDeleget, 0);
    return _widgetDeleget->_x;
}

int Widget::y()
{
    INVALID_POINTER_RETURN_PARAM(_widgetDeleget, 0);
    return _widgetDeleget->_y;
}

int Widget::width()
{
    INVALID_POINTER_RETURN_PARAM(_widgetDeleget, 0);
    return _widgetDeleget->_width;
}

int Widget::height()
{
    INVALID_POINTER_RETURN_PARAM(_widgetDeleget, 0);
    return _widgetDeleget->_height;
}

bool Widget::addView(View* view)
{
    INVALID_POINTER_RETURN_FALSE(_widgetDeleget);
    return _widgetDeleget->_rootView.addView(view);
}

void Widget::startAnimate()
{
	INVALID_POINTER_RETURN(_widgetDeleget);
	::SetTimer(_widgetDeleget->_hwnd, TIME_ID, 15, timerProc);
}

void Widget::stopAnimate()
{
	INVALID_POINTER_RETURN(_widgetDeleget);
	::KillTimer(_widgetDeleget->_hwnd, TIME_ID);
}

bool Widget::initCanvas(int canvasType)
{
    INVALID_POINTER_RETURN_FALSE(_widgetDeleget);
    return _widgetDeleget->_rootView.initCanvas(canvasType);
}

LRESULT Widget::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
    LRESULT lResult = 0;

    switch (message)
    {
    case WM_PAINT:
        hdc = ::BeginPaint(hWnd, &ps);
		drawToWindow();
        ::EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        break;

    case WM_KEYDOWN:
        {
            lResult = processKeyDown(wParam, lParam);
        }
        break;

    case WM_WINDOWPOSCHANGING:
        break;

    case WM_WINDOWPOSCHANGED:
        break;

    case WM_MOVE:
        break;

    case WM_SIZE:
        break;

    case WM_NCHITTEST:
        lResult = HTCAPTION;
        break;

    default:
        return ::DefWindowProc(hWnd, message, wParam, lParam);
    }    

    return lResult;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT lResult = 0;

    std::map<HWND, Widget*>::iterator iter = g_mapHwnd2Widget.find(hWnd);

    if (iter != g_mapHwnd2Widget.end() && NULL != iter->second)
    {
	    lResult = iter->second->wndProc(hWnd, message, wParam, lParam);
    }

    if (0 == lResult)
    {
        return ::DefWindowProc(hWnd, message, wParam, lParam);
    }
	else
    {
        return lResult;
    }
}

Widget* Widget::createWindow(int x, int y, int width, int height)
{
    Widget* widget = new Widget;
    widget->init(x, y, width, height);
    return widget;
}

void Widget::registerClass()   
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= g_hInst;
	wcex.hIcon			= NULL; 
	wcex.hCursor		= NULL; 
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL; 
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= NULL;

	::RegisterClassEx(&wcex);
}

void Widget::createRootView()
{

}

LRESULT Widget::processKeyDown(WPARAM wparam, LPARAM lparam)
{
    LRESULT lResult = 0;

    INVALID_POINTER_RETURN_PARAM(_widgetDeleget, lResult);
    INVALID_POINTER_RETURN_PARAM(_widgetDeleget->_hwnd, lResult);

    switch(wparam)
    {
    case VK_ESCAPE:
        ::PostMessage(_widgetDeleget->_hwnd, WM_QUIT, 0, 0);
        return 1;
        break;

    default:
        break;
    }

    return lResult;
}

void Widget::onTimer()
{
	drawToWindow();
}

void Widget::drawToWindow()
{
	if (_widgetDeleget)
	{
		_widgetDeleget->_rootView.OnDraw();
		Canvas* canvas = _widgetDeleget->_rootView.getCanvas();

		if (canvas)
		{
			HWND hwnd = _widgetDeleget->_hwnd;
			HDC hdc = ::GetDC(hwnd);
			Size canvasSize = canvas->getCanvasSize();

			BITMAPINFO bmi;

			memset(&bmi, 0, sizeof(bmi));
			bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
			bmi.bmiHeader.biWidth       = canvasSize._width;
			bmi.bmiHeader.biHeight      = -canvasSize._height; // top-down image
			bmi.bmiHeader.biPlanes      = 1;
			bmi.bmiHeader.biBitCount    = 32;
			bmi.bmiHeader.biCompression = BI_RGB;
			bmi.bmiHeader.biSizeImage   = 0;

			HDC hMemDC = ::CreateCompatibleDC(hdc);
			HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, _widgetDeleget->_bitmap);
			::SetDIBitsToDevice(hMemDC, 0, 0, _widgetDeleget->_width, _widgetDeleget->_height, 0, 0, 0, canvasSize._height, canvas->lockBits(), &bmi, DIB_RGB_COLORS);
			canvas->unlockBits();
			BLENDFUNCTION blendFunc = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};

			RECT rc;
			::GetWindowRect(hwnd, &rc);
			POINT ptSrc = {0, 0};
			POINT ptDst = {rc.left, rc.top};
			SIZE size = {rc.right - rc.left, rc.bottom - rc.top};
			::UpdateLayeredWindow(hwnd, hdc, &ptDst, &size, hMemDC, &ptSrc, RGB(0, 0, 0), &blendFunc, ULW_ALPHA);

			::SelectObject(hMemDC, hOldBitmap);
			::DeleteObject(hMemDC);
            ::ReleaseDC(hwnd, hdc);
		}
	}
}

void Widget::schedualPaint(const KRect& rect)
{
	RECT updateRect = {rect._left, rect._top, rect._right, rect._bottom};
	::InvalidateRect(_widgetDeleget->_hwnd, &updateRect, FALSE);
}