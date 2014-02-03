#pragma once

#ifdef AK_DLL
#define AK_API __declspec(export)
#else
#define AK_API
#endif

namespace ak
{
    typedef enum
    {
        GdiGraphics,
        GdiPlusGraphics,
        SkiaGraphics,
    } GraphicsType;

	typedef enum
	{
		SolidBrush,
		TextureBrush,
		LinearGradientBrush,
	} BrushType;

	enum opMode
	{
		kModeReplace,
		kModeIntersect,
		kModeUnion,
		kModeXor,
		kModeExclude,
		kModeComplement, 
	};
}

typedef unsigned char byte;

#define INVALID_POINTER_RETURN(p) \
    if (nullptr == p) \
    return

#define INVALID_POINTER_RETURN_PARAM(p, r) \
    if (nullptr == p) \
    return r
#define INVALID_POINTER_RETURN_FALSE(p) \
    if (nullptr == p) \
    return false

#define INVALID_POINTER_RETURN_NULL(p) \
    if (nullptr == p) \
    return nullptr

#define VALUE_FALSE_RETURN(v) \
    if (false == v) \
    return

#define VALUE_FALSE_RETURN_FALSE(v) \
    if (false == v) \
    return false

#include <string>
#include "KString.h"