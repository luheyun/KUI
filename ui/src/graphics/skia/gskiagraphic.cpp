#include "StdAfx.h"
#include "gskiagraphic.h"
#include "ghwnddevice.h"
#include "gbasedatatype.h"
#include <WinDef.h>
#include "gwin32typeconvert.h"
#include "gsysteminfo.h"
#include "gskiabitmap.h"
#include "gskiahelper.h"

#pragma warning(disable:4244)
#pragma warning(disable:4481)
#pragma warning(disable:4100)
#pragma warning(disable:4127)
#include "SkCanvas.h"
#include "SkDevice.h"
#include "SkShader.h"
#include "SkTypeface.h"
#include "SkTextBox.h"
#pragma warning(default:4127)
#pragma warning(default:4100)
#pragma warning(default:4481)
#pragma warning(default:4244)

const char ellipsis[] = "\xE2\x80\xA6";

class GSkiaGraphicPrivateData
{
public:
    GSkiaGraphicPrivateData(GAbractDevice * device)
    {
        pDevice = dynamic_cast<GHwndDevice*>(device);
        G_ASSERT(pDevice);
    }

public:
    SkCanvas* pCanvas;
    GHwndDevice * pDevice;
};

GSkiaGraphic::GSkiaGraphic(GAbractDevice * device, int width, int height)
{
    INVALID_POINTER_RETURN(device);

    m_privateData = new GSkiaGraphicPrivateData(device);

    GSkiaBitmapPtr pBitmap(new GSkiaBitmap(width, height));
    m_privateData->pCanvas = new SkCanvas(pBitmap->bitmap);
    m_privateData->pDevice->setBitmap(pBitmap);
}


GSkiaGraphic::~GSkiaGraphic(void)
{
}

void GSkiaGraphic::resize(int width, int height)
{
    INVALID_POINTER_RETURN(m_privateData);
    INVALID_POINTER_RETURN(m_privateData->pCanvas);

    GSize screenSize = GSystemInfo::getScreenSize();
    GBitmapPtr pBitmap = m_privateData->pDevice->getBitmap();
    int bitmapWidth = pBitmap->width();
    int bitmapHeight = pBitmap->height();
    if (width > screenSize.width || height > screenSize.height)
    {
        m_privateData->pCanvas->unref();
        GSkiaBitmapPtr pBitmap(new GSkiaBitmap(width, height));
        m_privateData->pCanvas = new SkCanvas(pBitmap->bitmap);
        m_privateData->pDevice->setBitmap(pBitmap);
    }
    else if (bitmapWidth < screenSize.width || bitmapHeight < screenSize.height)
    {
        m_privateData->pCanvas->unref();
        GSkiaBitmapPtr pBitmap(new GSkiaBitmap(screenSize.width, screenSize.height));
        m_privateData->pCanvas = new SkCanvas(pBitmap->bitmap);
        m_privateData->pDevice->setBitmap(pBitmap);
    }
}

void GSkiaGraphic::erase(const GRect & rect)
{
    INVALID_POINTER_RETURN(m_privateData);
    INVALID_POINTER_RETURN(m_privateData->pCanvas);
    m_privateData->pCanvas->save();
    SkRect skR = GSkiaHelper::GRectToSkRect(rect);
    SkPaint paint;
    paint.setXfermodeMode(SkXfermode::kClear_Mode);
    m_privateData->pCanvas->drawRect(skR, paint);
    m_privateData->pCanvas->restore();
}

void GSkiaGraphic::setClipRect(const GRect & rect)
{
    INVALID_POINTER_RETURN(m_privateData);
    INVALID_POINTER_RETURN(m_privateData->pCanvas);
    m_privateData->pCanvas->clipRect(GSkiaHelper::GRectToSkRect(rect), SkRegion::kReplace_Op);
}

void GSkiaGraphic::drawPoint(const GPoint & pos, const GPenPtr & pPen)
{
    INVALID_POINTER_RETURN(pPen);
    INVALID_POINTER_RETURN(m_privateData);
    INVALID_POINTER_RETURN(m_privateData->pCanvas);

    GColor color = pPen->color();
    m_privateData->pCanvas->drawPoint(SkIntToScalar(pos.x), SkIntToScalar(pos.y), GSkiaHelper::GColorToSkColor(color));
}

void GSkiaGraphic::drawLine(const GLine & line, const GPenPtr & pPen)
{
    INVALID_POINTER_RETURN(pPen);
    INVALID_POINTER_RETURN(m_privateData);
    INVALID_POINTER_RETURN(m_privateData->pCanvas);

    SkPaint paint;
    const GColor color = pPen->color();
    paint.setColor(GSkiaHelper::GColorToSkColor(color));
    m_privateData->pCanvas->drawLine(SkIntToScalar(line.x1()), SkIntToScalar(line.y1()), SkIntToScalar(line.x2()), SkIntToScalar(line.y2()), paint);
}

void GSkiaGraphic::fillRect(const GRect & rect, double xRadious, double yRadious
    , const GPenPtr & pPen, const GBrushPtr & pBrush)
{
    G_UNUSED(xRadious);
    G_UNUSED(yRadious);
    G_UNUSED(pPen);
    INVALID_POINTER_RETURN(pBrush);
    INVALID_POINTER_RETURN(m_privateData);
    INVALID_POINTER_RETURN(m_privateData->pDevice);

    if (pBrush->style() == GBrush::GColorBrush)
    {
        SkPaint paint;
        SkRect rc = GSkiaHelper::GRectToSkRect(rect);
        const GColor & color = pBrush->color();
        paint.setColor(GSkiaHelper::GColorToSkColor(color));
        m_privateData->pCanvas->drawRect(rc, paint);
    }
    else if (pBrush->style() == GBrush::GGraientBrush)
    {
        // todo::
    }
    else if (pBrush->style() == GBrush::GNullBrush)
    {
        // todo::
    }
}

void GSkiaGraphic::drawArc(const GRect & rect, int startAngle, int spanAngle, const GPenPtr & pPen, const GBrushPtr & pBrush)
{
    G_UNUSED(rect);
    G_UNUSED(startAngle);
    G_UNUSED(spanAngle);
    G_UNUSED(pPen);
    G_UNUSED(pBrush);
}

void GSkiaGraphic::drawEllipse(const GRect & rect, const GPenPtr & pPen, const GBrushPtr & pBrush)
{
    G_UNUSED(rect);
    G_UNUSED(pPen);
    G_UNUSED(pBrush);
}

GRect GSkiaGraphic::textBoundingRect(const GString & text, const GRect & rect, int flags, const GFontPtr & pFont, const GPenPtr & pPen, const GBrushPtr & pBrush)
{
    G_UNUSED(pPen);
    G_UNUSED(pBrush);

    SkPaint paint;

    // 设置字体
    if (pFont)
    {
        SkTypeface::Style fontStyle = GSkiaHelper::GFontStyleToSkStyle(pFont->fontStyle());
        paint.setTypeface(SkTypeface::CreateFromName(pFont->fontName().toUTF8(), fontStyle));
        paint.setTextSize(SkIntToScalar(pFont->fontSize()));
    }

    paint.setAntiAlias(true);
    paint.setLCDRenderText(true);

    SkRect rcBound;
    const char* utf8Text = text.toUTF8();
    paint.measureText(utf8Text, strlen(utf8Text), &rcBound);

    SkPaint::FontMetrics fontMetrics;
    paint.getFontMetrics(&fontMetrics);

    // fontBound高度以字体Descent+Ascent为准, skia中Ascent为负数，需要做减法
    rcBound.fBottom = rcBound.fTop + fontMetrics.fDescent - fontMetrics.fAscent;

    SkRect rcDest = GSkiaHelper::GRectToSkRect(rect);

    if (CONTAIN_FLAG(flags, GEnumType::TextWordBreak))
    {
        SkTextBox textBox;
        textBox.setMode(SkTextBox::kLineBreak_Mode);
        textBox.setSpacing(SkIntToScalar(4)/3, 0);
        textBox.setText(utf8Text, strlen(utf8Text), paint);

        if (rcDest.width() > SkIntToScalar(0) && rcBound.width() > rcDest.width())
        {
            rcBound.fRight = rcBound.fLeft + rcDest.width();

            // 有点坑爹，先临时设置box大小，getTextHeight需要先设置box大小
            textBox.setBox(rcDest);
            rcBound.fBottom = rcBound.fTop + SkMinScalar(textBox.getTextHeight(), rcDest.height());
        }
        else
        {
            textBox.setBox(rcBound);
            rcBound.fRight = rcBound.fLeft + textBox.getTextWidth();
        }

        if (rcDest.height() > 0)
        {
            rcBound.fBottom = rcBound.fTop + SkMinScalar(textBox.getTextHeight(), rcDest.height());
        }
        else
        {
            rcBound.fBottom = rcBound.fTop + textBox.getTextHeight();
        }
    }
    else
    {
        if (rcDest.width() > SkIntToScalar(0) && rcBound.width() > rcDest.width())
        {
            rcBound.fRight = rcBound.fLeft + rcDest.width();
        }
    }
    
    rcBound.offsetTo(SkIntToScalar(0), SkIntToScalar(0));
    return GSkiaHelper::SkRectToGRect(rcBound);
}

void GSkiaGraphic::drawText(const GRect & rect, const GString & text, int flags, const GFontPtr & pFont, GRect * pBoundingRect, const GPenPtr & pPen, const GBrushPtr & pBrush)
{
    INVALID_POINTER_RETURN(pPen);
    INVALID_POINTER_RETURN(pBrush);
    INVALID_POINTER_RETURN(pFont);
    INVALID_POINTER_RETURN(m_privateData);
    INVALID_POINTER_RETURN(m_privateData->pDevice);

    SkPaint paint;

    // 设置字体
    SkTypeface::Style fontStyle = GSkiaHelper::GFontStyleToSkStyle(pFont->fontStyle());
    SkColor color = GSkiaHelper::GColorToSkColor(pPen->color());

    paint.setTypeface(SkTypeface::CreateFromName(pFont->fontName().toUTF8(), fontStyle));
    paint.setColor(color);
    paint.setTextSize(SkIntToScalar(pFont->fontSize()));
    paint.setAntiAlias(true);
    paint.setLCDRenderText(true);

    SkRect rcBound;
    SkRect rcDest = GSkiaHelper::GRectToSkRect(rect);
    const char* utf8Text = text.toUTF8();

    SkPaint::FontMetrics fontMetrics;
    paint.getFontMetrics(&fontMetrics);
    paint.measureText(utf8Text, strlen(utf8Text), &rcBound);

    // fontBound高度以字体Descent+Ascent为准, skia中Ascent为负数，需要做减法
    rcBound.fBottom = rcBound.fTop + fontMetrics.fDescent - fontMetrics.fAscent;

    if (pBoundingRect)
    {
        pBoundingRect->left = (int)rcBound.left();
        pBoundingRect->top = (int)rcBound.top();
        pBoundingRect->right = (int)rcBound.right();
        pBoundingRect->bottom = (int)rcBound.bottom();
    }

    if (rcBound.width() > rect.width() && CONTAIN_FLAG(flags, GEnumType::TextWordBreak))
    {
        SkTextBox textBox;
        textBox.setMode(SkTextBox::kLineBreak_Mode);
        textBox.setSpacing(SkIntToScalar(4)/3, 0);
        //char text[] = "\xE2\x80\xA6";
        textBox.setText(utf8Text, strlen(utf8Text), paint);

        // 有点坑爹，先临时设置box大小，getTextHeight需要先设置box大小
        textBox.setBox(rcDest);
        SkScalar textHeiht = SkMinScalar(textBox.getTextHeight(), rcDest.height());
        SkRect boxRect = rcDest;

        if (CONTAIN_FLAG(flags, GEnumType::TextAlignVCenter))
        {
            boxRect.fLeft = rcDest.fLeft;
            boxRect.fRight = rcDest.fRight;
            boxRect.fTop = rcDest.fTop + SkScalarHalf(rcDest.height() - textHeiht);
            boxRect.fBottom = boxRect.fTop + textHeiht;
        }
        else if (CONTAIN_FLAG(flags, GEnumType::TextAlignTop))
        {
            boxRect.fLeft = rcDest.fLeft;
            boxRect.fRight = rcDest.fRight;
            boxRect.fTop = rcDest.fTop;
            boxRect.fBottom = boxRect.fTop + textHeiht;
        }
        else if (CONTAIN_FLAG(flags, GEnumType::TextAlignBottom))
        {
            boxRect.fLeft = rcDest.fLeft;
            boxRect.fRight = rcDest.fRight;
            boxRect.fBottom = rcDest.fBottom;
            boxRect.fTop = boxRect.fBottom - textHeiht;
        }

        textBox.setBox(boxRect);
        textBox.draw(m_privateData->pCanvas);
    }
    else
    {
        SkScalar startX = rcDest.fLeft;
        SkScalar startY = rcDest.fTop;
        bool bElide = false;
        size_t len = 0;
        SkScalar ellipsisLen = SkIntToScalar(0);

        if (rcBound.width() > rect.width() && CONTAIN_FLAG(flags, GEnumType::TextSingleLine))
        {
            bElide = true;
            rcBound.fRight = rcBound.fLeft + rect.width();
            ellipsisLen = paint.measureText(ellipsis, strlen(ellipsis));
            len = paint.breakText(utf8Text, strlen(utf8Text), rcDest.width() - ellipsisLen);
        }

        if (CONTAIN_FLAG(flags, GEnumType::TextAlignHCenter))
        {
            startX = rcDest.centerX() - SkScalarHalf(rcBound.width());
            rcBound.offsetTo(rcDest.centerX() - SkScalarHalf(rcBound.width()), rcDest.centerY() - SkScalarHalf(rcBound.height()));
        }
        else if (CONTAIN_FLAG(flags, GEnumType::TextAlignLeft))
        {
            startX = rcDest.fLeft;
        }
        else if (CONTAIN_FLAG(flags, GEnumType::TextAlignRight))
        {
            startX = rcDest.fRight - rcBound.width();
        }

        if (CONTAIN_FLAG(flags, GEnumType::TextAlignVCenter))
        {
            startY = rcDest.centerY() - SkScalarHalf(rcBound.height());
        }
        else if (CONTAIN_FLAG(flags, GEnumType::TextAlignTop))
        {
            startY = rcDest.fTop;
        }
        else if (CONTAIN_FLAG(flags, GEnumType::TextAlignBottom))
        {
            startY = rcDest.fBottom - rcBound.height();
        }

        rcBound.offsetTo(startX, startY);
        if (!bElide)
        {
            m_privateData->pCanvas->drawText(utf8Text, strlen(utf8Text), rcBound.fLeft, rcBound.fTop - fontMetrics.fAscent, paint);
    
        }
        else
        {
            m_privateData->pCanvas->drawText(utf8Text, len, rcBound.fLeft, rcBound.fTop - fontMetrics.fAscent, paint);
            SkRect textBound;
            SkScalar ellipsisSX = paint.measureText(utf8Text, len, &textBound);
            m_privateData->pCanvas->drawText(ellipsis, strlen(ellipsis), rcBound.fLeft + ellipsisSX, rcBound.fTop + textBound.height(), paint);
        }
    }
}

void GSkiaGraphic::drawBitmap(const GRect & target, const GBitmapPtr & pBitmap, const GRect & source, int flags)
{
    GSkiaBitmapPtr pSkiaBitmap = boost::dynamic_pointer_cast<GSkiaBitmap>(pBitmap); 
    if (pSkiaBitmap)
    {
        SkRect rcDst = GSkiaHelper::GRectToSkRect(target);
        SkIRect rcSrc = GSkiaHelper::GRectToSkIRect(source);
        if (CONTAIN_FLAG(flags, GEnumType::ImageTitle))
        {
//             SkShader* shader = SkShader::CreateBitmapShader(pSkiaBitmap->bitmap, SkShader::kRepeat_TileMode, SkShader::kRepeat_TileMode);
//             SkPaint paint;
//             paint.setShader(shader);
//             m_privateData->pCanvas->drawRect(rcDst, paint);
            m_privateData->pCanvas->drawBitmapRect(pSkiaBitmap->bitmap, &rcSrc, rcDst, NULL);
        }
        else if (CONTAIN_FLAG(flags, GEnumType::ImageNotScale))
        {
            int minW = min(source.width(), target.width());
            int minH = min(source.height(), target.height());
            GRect des = target;
            GRect src = source;
            des.resize(minW, minH);
            src.resize(minW, minH);
            SkRect rcDst = GSkiaHelper::GRectToSkRect(des);
            SkIRect rcSrc = GSkiaHelper::GRectToSkIRect(src);    
            m_privateData->pCanvas->drawBitmapRect(pSkiaBitmap->bitmap, &rcSrc, rcDst);
        }
        else if (CONTAIN_FLAG(flags, GEnumType::ImageScaleKeepRadio))
        {   
            //Todo:: not impl yet.
            m_privateData->pCanvas->drawBitmapRect(pSkiaBitmap->bitmap, &rcSrc, rcDst);
        }
        else //if ((flags & GEnumType::ImageScale) == GEnumType::ImageScale)
        {
            m_privateData->pCanvas->drawBitmapRect(pSkiaBitmap->bitmap, &rcSrc, rcDst);
        }
    }
}
