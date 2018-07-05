/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFVector2D.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFMath
{
	class LFRectangle final
	{
	public:
        LFVector2D position = LFVector2D();
        float width = 0, height = 0;

		LFRectangle() = default;
		LFRectangle(const LFRectangle &other) = default;
        LFRectangle(float x, float y, float width, float height);
		LFRectangle(const LFVector2D &pos, const LFVector2D &size);

        LFRectangle &operator = (const LFRectangle &value);
        bool operator == (const LFRectangle &value) const;
		bool operator != (const LFRectangle &value) const;

		float GetLeft() const;
		float GetRight() const;
		float GetTop() const;
		float GetBottom() const;
		void SetPosition(float x, float y);
		void SetPosition(const LFVector2D &pos);
		LFVector2D &GetPosition();
		LFVector2D GetSize() const;
		void SetSize(const LFVector2D &size);
		LFVector2D GetCenter() const;

        bool Contains(float x, float y) const;
        bool Contains(const LFVector2D &pofloat) const;
        bool Contains(const LFRectangle &value) const;
        bool Intersects(const LFRectangle &value) const;
	};
}}}}
