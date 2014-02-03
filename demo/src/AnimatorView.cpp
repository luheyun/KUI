#include "Stdafx.h"
#include "AnimatorView.h"
#include "KPen.h"
#include "Canvas.h"
#include "Image.h"
#include "demo.h"
#include "KPoint.h"
#include "KSolidBrush.h"
#include "KFontFamily.h"
#include "KFont.h"

extern int fps;

const int IMAGE_WIDTH = 128;
const char* const IMAGE_QQ_PATH = "../res/qq.png";
const char* const IMAGE_FLOWER_PATH = "../res/flower.png";

AnimatorView::AnimatorView()
	: _imageQQ(nullptr)
	, _imageFlower(nullptr)
{
}

AnimatorView::~AnimatorView()
{

}

bool AnimatorView::init()
{
	_alpha = 0;
	_degrees = 0;

	if (nullptr != _imageQQ)
	{
		delete _imageQQ;
		_imageQQ = nullptr;
	}

	_imageQQ = createImage();

	if (nullptr != _imageQQ)
	{
		_imageQQ->fromFile("../res/qq.png");
	}

	if (nullptr != _imageFlower)
	{
		delete _imageFlower;
		_imageFlower = nullptr;
	}

	_imageFlower = createImage();

	if (nullptr != _imageFlower)
	{
		_imageFlower->fromFile("../res/flower.png");
	}

	return true;
}

bool AnimatorView::doDraw(Canvas& canvas)
{
	if (nullptr != _imageQQ)
	{
		_alpha = _alpha > 255 ? 0 : _alpha;
		int alpha = _alpha;
		float degrees = _degrees;

		for (int y = 0; y < WINDOW_HEIGHT; y += IMAGE_WIDTH)
		{
			for (int x = 0; x < WINDOW_WIDTH; x += IMAGE_WIDTH)
			{
				canvas.drawImage(_imageFlower, x, y, degrees);
				canvas.drawImage(_imageQQ, x, y, alpha);
				degrees += 10;
				alpha += 5;
				alpha = alpha > 255 ? 0 : alpha;
			}
		}
	}

	_alpha += 10;
	_degrees += 20;

	KSolidBrush solidBrush(Color(200, 0, 0, 0));
	canvas.fillRect(&solidBrush, KRect(15, 20, 270, 100));

	KFontFamily fontFamily(L"Î¢ÈíÑÅºÚ");
	KFont font(&fontFamily, 15, KFontStyleRegular, KUnitPixel);
	KSolidBrush fontBrush(Color(255, 100, 210, 110));

	KString fpsStr(L"FPS : ");
	fpsStr += fps;
	KPoint pt(20, 80);
	canvas.drawString(fpsStr, -1, font, pt, &fontBrush);

	DWORD endTime = ::GetTickCount();

	KString ftStr(L"Frame Time : ");
	ftStr += ::GetTickCount() - _startTime;
	ftStr += L" ms";
	pt.set(20, 110);
	canvas.drawString(ftStr, -1, font, pt, &fontBrush);

	return true;
}