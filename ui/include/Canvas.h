#pragma once

class Color;
class Size;
class KRect;
class Image;
class KPen; 
class KBrush;
class KString;
class KFont;
class KPoint;
class CanvasDelegate;

class AK_API Canvas
{
public:
    Canvas();
    ~Canvas();
    
    bool init(int width, int height, int canvasType);
    void* lockBits();
	void unlockBits();
	ak::GraphicsType getGraphicsType() const;

	void clear(const Color& color);

    Size getCanvasSize();
    bool drawLine(KPen* pen, int x1, int y1, int x2, int y2);
    bool drawImage(Image* image, int x, int y, int nAlpha = 255);
	bool drawImage(Image* image, int x, int y, float degrees);
    bool drawRect(KPen* pen, KRect& rect);
	bool fillRect(KBrush* brush, KRect& rect);
	bool drawString(const KString& str, int len, const KFont& font, const KPoint& pt, KBrush* brush);
	bool setClip(const KRect& rect, ak::opMode mode);
	bool resetClip();

private:
    CanvasDelegate* _canvasDelegate;
};