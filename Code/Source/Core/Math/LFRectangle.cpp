/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFRectangle.h"

namespace LFCore { namespace Math
{
    LFRectangle::LFRectangle() : position(0, 0), width(0), height(0)
    { }

    LFRectangle::LFRectangle(float x, float y, float width, float height) : position(x, y), width(width), height(height)
    { }

	LFRectangle::LFRectangle(const LFVector2D &pos, const LFVector2D &size) : position(pos.x, pos.y), width(size.x), height(size.y)
	{ }

    LFRectangle &LFRectangle::operator = (const LFRectangle &value)
	{
	    position = value.position;
	    width = value.width;
	    height = value.height;

		return *this;
	}

	bool LFRectangle::operator == (const LFRectangle &value) const
	{
	    return (position == value.position && width == value.width && height == value.height);
	}

	bool LFRectangle::operator != (const LFRectangle &value) const
	{
		return (position != value.position || width != value.width || height != value.height);
	}

    bool LFRectangle::Contains(float x, float y)
    {
        return ((((position.x <= x) && (x < (position.x + width))) && (position.y <= y)) && (y < (position.y + height)));
    }

    bool LFRectangle::Contains(const LFVector2D &pofloat)
    {
    	return ((((position.x <= pofloat.x) && (pofloat.x < (position.x + width))) && (position.y <= pofloat.y)) && (pofloat.y < (position.y + height)));
    }

    bool LFRectangle::Contains(const LFRectangle &value)
    {
        return ((((position.x <= value.position.x) && ((value.position.x + value.width) <= (position.x + width))) &&
                 (position.y <= value.position.y)) && ((value.position.y + value.height) <= (position.y + height)));
    }

    bool LFRectangle::Intersects(const LFRectangle &value)
    {
        return ((((value.position.x < (position.x + width)) && (position.x < (value.position.x + value.width))) &&
                 (value.position.y < (position.y + height))) && (position.y < (value.position.y + value.height)));
    }
}}
