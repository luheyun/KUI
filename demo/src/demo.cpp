// demo.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "demo.h"
#include "UIDefine.h"
#include "DemoWidget.h"
#include "SkiaAnimatorView.h"
#include "GdiplusAnimatorView.h"
#include <gdiplus.h>

int fps = 0;
HINSTANCE g_hInst = nullptr;

// 此代码模块中包含的函数的前向声明:
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	g_hInst = hInstance;

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

 	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
 	ULONG_PTR gdiplusToken;
 
 	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    DemoWidget* widget = new DemoWidget;

    if (nullptr != widget)
    {
		widget->initialize(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    }

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEMO));

	DWORD curTime = 0;
	DWORD lastTime = ::GetTickCount();

	// 主消息循环:
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
			{
				::DestroyWindow(msg.hwnd);
				break;
			}

			curTime = ::GetTickCount();

			if (curTime - lastTime >= 1000)
			{
				lastTime = curTime;
				fps = widget->getFrameCount();
				widget->resetFrameCount();
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	if (nullptr != widget)
	{
		widget->stopAnimate();
		delete widget;
		widget = nullptr;
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);

	return (int) msg.wParam;
}
