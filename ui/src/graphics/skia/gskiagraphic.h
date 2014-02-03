#pragma once
#include "gbasedatatype.h"
#include "gviewpointer.h"

class GBitmap;
class GAbractDevice;
class GHwndDevice;
class GSkiaGraphicPrivateData;
class GSkiaGraphic
{
public:
    GSkiaGraphic(GAbractDevice * device, int width, int height);
    virtual ~GSkiaGraphic(void);

    void resize(int width, int height);
    void erase(const GRect & rect);

    void setClipRect(const GRect & rect);
    void drawPoint(const GPoint & pos, const GPenPtr & pPen);
    void drawLine(const GLine & line, const GPenPtr & pPen);
    void fillRect(const GRect & rect, double xRadious, double yRadious
        , const GPenPtr & pPen, const GBrushPtr & pBrush);
    void drawArc(const GRect & rect, int startAngle, int spanAngle, const GPenPtr & pPen, const GBrushPtr & pBrush);
    void drawEllipse(const GRect & rect, const GPenPtr & pPen, const GBrushPtr & pBrush);

    GRect textBoundingRect(const GString & text, const GRect & rect, int flags, const GFontPtr & pFont, const GPenPtr & pPen, const GBrushPtr & pBrush);
    void drawText(const GRect & rect, const GString & text, int flags, const GFontPtr & pFont, GRect * boundingRect, const GPenPtr & pPen, const GBrushPtr & pBrush);

    void drawBitmap(const GRect & target, const GBitmapPtr & pBitmap, const GRect & source, int flags);
    
private:
    GSkiaGraphicPrivateData * m_privateData;
};

