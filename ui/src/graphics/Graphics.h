#pragma once

class Color;
class Size;
class KRect;
class KPen;
class KBrush;
class KFont;
class Image;
class KString;
class KPoint;
class KRegion;

class Graphics
{
public:
    Graphics(int width, int height);
    virtual ~Graphics();

    virtual void* lockBits() = 0;
	virtual void unlockBits() {}
	virtual void clear(const Color& color) {}
    virtual Size getSize();

	// use solid pen as default value
    virtual bool drawLine(KPen* pen, int x1, int y1, int x2, int y2) { return false; }
    virtual bool drawImage(Image* image, int x, int y, int nAlpha = 255) { return false; }
    virtual bool drawImage(Image* image, int x, int y, float degrees) { return false; }
	virtual bool drawRect(KPen* pen, KRect& rect) {return false;}
    virtual bool fillRect(KBrush* brush, KRect& rect) = 0;

	// the len parameter can be set to -1 if the string is null terminated.
	virtual bool drawString(const KString& str, int len, const KFont& font, const KPoint& pt, KBrush* brush) { return false; }

	virtual bool setClip(const KRect& rect, ak::opMode mode) { return false; }
	virtual bool resetClip() { return false; }

protected:
    int _width;
    int _height;
};