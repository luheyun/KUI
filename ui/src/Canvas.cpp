#include "UIDefine.h"
#include "Canvas.h"
#include "SkiaGraphics.h"
#include "GdiPlusGraphics.h"
#include "GdiGraphics.h"
#include "Size.h"

class CanvasDelegate 
{
public:
    CanvasDelegate::CanvasDelegate()
        : _pGraphics(nullptr)
		, _graphicsType(ak::GdiGraphics)
    {

    }

    CanvasDelegate::~CanvasDelegate()
    {
        if (nullptr != _pGraphics)
        {
            delete _pGraphics;
            _pGraphics = nullptr;
        }
    }

public:
    Graphics* _pGraphics;
	ak::GraphicsType _graphicsType;
};

Canvas::Canvas()
{
    _canvasDelegate = new CanvasDelegate;
}

Canvas::~Canvas()
{

}

bool Canvas::init(int width, int height, int canvasType)
{
    INVALID_POINTER_RETURN_FALSE(_canvasDelegate);

	if (nullptr != _canvasDelegate->_pGraphics)
	{
		delete _canvasDelegate->_pGraphics;
		_canvasDelegate = nullptr;
	}

    switch(canvasType)
    {
    case ak::SkiaGraphics:
		_canvasDelegate->_graphicsType = ak::SkiaGraphics;
        _canvasDelegate->_pGraphics = new SkiaGraphics(width, height);
        break;

    case ak::GdiPlusGraphics:
		_canvasDelegate->_graphicsType = ak::GdiPlusGraphics;
		_canvasDelegate->_pGraphics = new GdiPlusGraphics(width, height);
        break;

    case ak::GdiGraphics:
		_canvasDelegate->_graphicsType = ak::GdiGraphics;
		_canvasDelegate->_pGraphics = new GdiGraphics(width, height);
        break;

    default:
        return false;
    }

    return true;
}

void* Canvas::lockBits()
{
    INVALID_POINTER_RETURN_NULL(_canvasDelegate);
    INVALID_POINTER_RETURN_NULL(_canvasDelegate->_pGraphics);
    return _canvasDelegate->_pGraphics->lockBits();
}

void Canvas::unlockBits()
{
	INVALID_POINTER_RETURN(_canvasDelegate);
	INVALID_POINTER_RETURN(_canvasDelegate->_pGraphics);
	_canvasDelegate->_pGraphics->unlockBits();
}

ak::GraphicsType Canvas::getGraphicsType() const
{
	INVALID_POINTER_RETURN_PARAM(_canvasDelegate, ak::GdiGraphics);
	return _canvasDelegate->_graphicsType;
}

void Canvas::clear(const Color& color)
{
	INVALID_POINTER_RETURN(_canvasDelegate);
	INVALID_POINTER_RETURN(_canvasDelegate->_pGraphics);
	_canvasDelegate->_pGraphics->clear(color);
}

Size Canvas::getCanvasSize()
{
    Size size;
    INVALID_POINTER_RETURN_PARAM(_canvasDelegate, size);
    INVALID_POINTER_RETURN_PARAM(_canvasDelegate->_pGraphics, size);
    return _canvasDelegate->_pGraphics->getSize();
}

bool Canvas::drawLine(KPen* pen, int x1, int y1, int x2, int y2)
{
    INVALID_POINTER_RETURN_FALSE(_canvasDelegate);
    INVALID_POINTER_RETURN_FALSE(_canvasDelegate->_pGraphics);
    return _canvasDelegate->_pGraphics->drawLine(pen, x1, y1, x2, y2);
}

bool Canvas::drawImage(Image* image, int x, int y, int nAlpha)
{
    INVALID_POINTER_RETURN_FALSE(_canvasDelegate);
    INVALID_POINTER_RETURN_FALSE(_canvasDelegate->_pGraphics);
    return _canvasDelegate->_pGraphics->drawImage(image, x, y, nAlpha);
}

bool Canvas::drawImage(Image* image, int x, int y, float degrees)
{
	INVALID_POINTER_RETURN_FALSE(_canvasDelegate);
	INVALID_POINTER_RETURN_FALSE(_canvasDelegate->_pGraphics);
	return _canvasDelegate->_pGraphics->drawImage(image, x, y, degrees);
}

bool Canvas::drawRect(KPen* pen, KRect& rect)
{
    INVALID_POINTER_RETURN_FALSE(_canvasDelegate);
    INVALID_POINTER_RETURN_FALSE(_canvasDelegate->_pGraphics);
    return _canvasDelegate->_pGraphics->drawRect(pen, rect);
}

bool Canvas::fillRect(KBrush* brush, KRect& rect)
{
	INVALID_POINTER_RETURN_FALSE(_canvasDelegate);
	INVALID_POINTER_RETURN_FALSE(_canvasDelegate->_pGraphics);
	return _canvasDelegate->_pGraphics->fillRect(brush, rect);
}

bool Canvas::drawString(const KString& str, int len, const KFont& font, const KPoint& pt, KBrush* brush)
{
	INVALID_POINTER_RETURN_FALSE(_canvasDelegate);
	INVALID_POINTER_RETURN_FALSE(_canvasDelegate->_pGraphics);
	return _canvasDelegate->_pGraphics->drawString(str, len, font, pt, brush);
}

bool Canvas::setClip(const KRect& rect, ak::opMode mode)
{
	INVALID_POINTER_RETURN_FALSE(_canvasDelegate);
	INVALID_POINTER_RETURN_FALSE(_canvasDelegate->_pGraphics);
	return _canvasDelegate->_pGraphics->setClip(rect, mode);
}

bool Canvas::resetClip()
{
	INVALID_POINTER_RETURN_FALSE(_canvasDelegate);
	INVALID_POINTER_RETURN_FALSE(_canvasDelegate->_pGraphics);
	return _canvasDelegate->_pGraphics->resetClip();
}