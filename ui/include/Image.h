#pragma once

class AK_API Image
{
public:
    virtual ~Image();

    static Image* createImage(int graphicsType);
	static Image* createImage(int width, int height, int graphicsType);

    virtual bool fromFile(char* file);
    virtual int width();
    virtual int height();

protected:
    Image();
};