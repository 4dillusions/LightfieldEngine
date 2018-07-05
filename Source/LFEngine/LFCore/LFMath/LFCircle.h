/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFVector2D.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFMath
{
	class LFCircle final
	{
	public:
        LFVector2D position;
        float radius;

        LFCircle();
		LFCircle(const LFCircle &other) = default;
        LFCircle(float x, float y, float radius);

        LFCircle &operator = (const LFCircle &value);
        bool operator == (const LFCircle &value) const;
		bool operator != (const LFCircle &value) const;

		void SetPosition(float x, float y);
		void SetPosition(const LFVector2D &pos);
		LFVector2D &GetPosition();
		void SetRadius(float radius);
		float GetRadius() const;

        bool Contains(int x, int y) const;
        bool Contains(const LFVector2D &point) const;
        bool Contains(const LFCircle &value) const;
        bool Intersects(const LFCircle &value) const;
	};
}}}}
