/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFRectangle.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFMath
{
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

	float LFRectangle::GetLeft() const
    {
	    return position.x;
    }

	float LFRectangle::GetRight() const
    {
	    return (position.x + width);
    }

	float LFRectangle::GetTop() const
    {
	    return position.y;
    }

	float LFRectangle::GetBottom() const
    {
	    return (position.y + height);
    }

	void LFRectangle::SetPosition(float x, float y)
    {
	    position.x = x; 
		position.y = y;
    }

	void LFRectangle::SetPosition(const LFVector2D &pos)
    {
	    position = pos;
    }

	LFVector2D &LFRectangle::GetPosition()
    {
	    return position;
    }

	LFVector2D LFRectangle::GetSize() const
    {
	    return LFVector2D(width, height);
    }

	void LFRectangle::SetSize(const LFVector2D &size)
    {
	    width = size.x; 
		height = size.y;
    }

	LFVector2D LFRectangle::GetCenter() const
    {
	    return LFVector2D(position.x + (width / 2), position.y + (height / 2));
    }

    bool LFRectangle::Contains(float x, float y) const
    {
        return ((((position.x <= x) && (x < (position.x + width))) && (position.y <= y)) && (y < (position.y + height)));
    }

    bool LFRectangle::Contains(const LFVector2D &pofloat) const
    {
    	return ((((position.x <= pofloat.x) && (pofloat.x < (position.x + width))) && (position.y <= pofloat.y)) && (pofloat.y < (position.y + height)));
    }

    bool LFRectangle::Contains(const LFRectangle &value) const
    {
        return ((((position.x <= value.position.x) && ((value.position.x + value.width) <= (position.x + width))) &&
                 (position.y <= value.position.y)) && ((value.position.y + value.height) <= (position.y + height)));
    }

    bool LFRectangle::Intersects(const LFRectangle &value) const
    {
        return ((((value.position.x < (position.x + width)) && (position.x < (value.position.x + value.width))) &&
                 (value.position.y < (position.y + height))) && (position.y < (value.position.y + value.height)));
    }
}}}}
