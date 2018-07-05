/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFVector2D.h"

namespace LFCore { namespace Math
{
	class LFCORE_LIBRARY LFRectangle
	{
	public:
        LFVector2D position;
        float width, height;

        LFRectangle();
        LFRectangle(float x, float y, float width, float height);
		LFRectangle(const LFVector2D &pos, const LFVector2D &size);

        LFRectangle &operator = (const LFRectangle &value);
        bool operator == (const LFRectangle &value) const;
		bool operator != (const LFRectangle &value) const;

		float Left() const { return position.x; }
		float Right() const { return (position.x + width); }
		float Top() const { return position.y; }
		float Bottom() const { return (position.y + height); }
		void Position(float x, float y) { position.x = x; position.y = y; }
		void Position(const LFVector2D &pos) { position = pos; }
		LFVector2D &Position() { return position; }
		LFVector2D Size() const { return LFVector2D(width, height); }
		void Size(const LFVector2D &size) { width = size.x; height = size.y; }
		LFVector2D Center() const { return LFVector2D(position.x + (width / 2), position.y + (height / 2)); }

        bool Contains(float x, float y);
        bool Contains(const LFVector2D &pofloat);
        bool Contains(const LFRectangle &value);
        bool Intersects(const LFRectangle &value);
	};
}}
