#pragma once

#include "UIDefine.h"

class AK_API KBrush
{
public:
	KBrush() {}
	virtual ~KBrush() {}

	virtual ak::BrushType getBrushType() = 0;
};