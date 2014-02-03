#pragma once

#include "Graphics.h"

class GdiGraphicsDelegate;

class GdiGraphics : public Graphics
{
public:
	GdiGraphics(int width, int height);
	virtual ~GdiGraphics();

	// Graphics
	virtual void* lockBits() override;
	virtual void clear(const Color& color) override;
	virtual bool drawLine(KPen* pen, int x1, int y1, int x2, int y2) override;
	virtual bool drawImage(Image* image, int x, int y, int nAlpha = 255) override;
	virtual bool drawRect(KPen* pen, KRect& rect) override;
	virtual bool fillRect(KBrush* brush, KRect& rect) override;
	virtual bool drawString(const KString& str, int len, const KFont& font, const KPoint& pt, KBrush* brush);
	virtual bool setClip(const KRect& rect, ak::opMode mode) override;
	virtual bool resetClip() override;

private:
	GdiGraphicsDelegate* _gdiGraphicsDelegate;
};