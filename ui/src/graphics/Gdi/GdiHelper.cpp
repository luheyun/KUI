#include "UIDefine.h"
#include "GdiHelper.h"

#include <Windows.h>
#include <Wingdi.h>

namespace GdiHelper
{
	int opModeToGdiOp(ak::opMode mode)
	{
		int opMode = RGN_COPY;

		switch(mode)
		{
		case ak::kModeXor:
			opMode = RGN_XOR;
			break;

		case ak::kModeUnion:
			opMode = RGN_OR;
			break;

		case ak::kModeReplace:
			opMode = RGN_COPY;
			break;

		case ak::kModeExclude: // not support
			break;

		case ak::kModeIntersect:
			opMode = RGN_AND;
			break;

		case ak::kModeComplement:
			opMode = RGN_DIFF;
			break;

		default:
			break;
		}

		return opMode;
	}
}