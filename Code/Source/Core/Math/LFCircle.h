/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFVector2D.h"

namespace LFCore { namespace Math
{
	class LFCORE_LIBRARY LFCircle
	{
	public:
        LFVector2D position;
        float radius;

        LFCircle();
        LFCircle(float x, float y, float radius);

        LFCircle &operator = (const LFCircle &value);
        bool operator == (const LFCircle &value) const;
		bool operator != (const LFCircle &value) const;

        void Position(float x, float y) { position.x = x; position.y = y; }
		void Position(const LFVector2D &pos) { this->position = pos; }
		LFVector2D &Position() { return this->position; }
		void Radius(float radius) { this->radius = radius; }
		float Radius() { return this->radius; }

        bool Contains(int x, int y);
        bool Contains(const LFVector2D &point);
        bool Contains(const LFCircle &value);
        bool Intersects(const LFCircle &value);
	};
}}
