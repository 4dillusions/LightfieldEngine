/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFCircle.h"

namespace LFCore { namespace Math
{
    LFCircle::LFCircle() : position(0, 0), radius(0)
    { }

    LFCircle::LFCircle(float x, float y, float radius) : position(x, y), radius(radius)
    { }

    LFCircle &LFCircle::operator = (const LFCircle &value)
	{
	    position = value.position;
	    radius = value.radius;

		return *this;
	}

	bool LFCircle::operator == (const LFCircle &value) const
	{
	    return (position == value.position && radius == value.radius);
	}

	bool LFCircle::operator != (const LFCircle &value) const
	{
		return (position != value.position || radius != value.radius);
	}

    bool LFCircle::Contains(int x, int y)
    {
		return ( ((position.x - x) * (position.x - x)) + ((position.y - y) * (position.y - y)) ) < (radius * radius);
    }

    bool LFCircle::Contains(const LFVector2D &point)
    {
    	return ( ((position.x - point.x) * (position.x - point.x)) + ((position.y - point.y) * (position.y - point.y)) ) < (radius * radius);
    }

    bool LFCircle::Contains(const LFCircle &value)
    {
		return ( ((position.x - value.position.x) * (position.x - value.position.x)) + ((position.y - value.position.y) * (position.y - value.position.y)) ) < 
			((radius - value.radius) * (radius - value.radius));
    }

    bool LFCircle::Intersects(const LFCircle &value)
    {
		return ( ((position.x - value.position.x) * (position.x - value.position.x)) + ((position.y - value.position.y) * (position.y - value.position.y)) ) < 
			((radius + value.radius) * (radius + value.radius));
    }
}}
