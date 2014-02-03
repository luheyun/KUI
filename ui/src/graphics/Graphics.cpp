#include "UIDefine.h"
#include "Graphics.h"
#include "Size.h"

Graphics::Graphics(int width, int height)
    : _width(width)
    , _height(height)
{
}

Graphics::~Graphics()
{

}

Size Graphics::getSize()
{
    return Size(_width, _height);
}