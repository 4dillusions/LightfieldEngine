/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFVector3D.h"

namespace LFCore { namespace Math
{
	class LFCORE_LIBRARY LFColor
	{
	public:
		unsigned char a, r, g, b;

		LFColor() : a(0), r(0), g(0), b(0) {}
		LFColor(unsigned char a, unsigned char r, unsigned char g, unsigned char b) : a(a), r(r), g(g), b(b) {}
		LFColor(unsigned char r, unsigned char g, unsigned char b) : a(0), r(r), g(g), b(b) {}

		LFVector3D ConvertToFloatColorRGB();
	};
}}
