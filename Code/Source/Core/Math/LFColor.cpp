/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFColor.h"

namespace LFCore { namespace Math
{
    LFVector3D LFColor::ConvertToFloatColorRGB()
	{
		return LFVector3D(1 / (255 / (float)r), 1 / (255 / (float)g), 1 / (255 / (float)b)); 
	}
}}
