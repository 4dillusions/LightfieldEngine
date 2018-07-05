#include "SMRectangle.h"

namespace SMEngine { namespace Math
{
    SMRectangle::SMRectangle() : position(0, 0), width(0), height(0)
    { }

    SMRectangle::SMRectangle(int x, int y, int width, int height) : position(x, y), width(width), height(height)
    { }

    SMRectangle &SMRectangle::operator = (const SMRectangle &value)
	{
	    position = value.position;
	    width = value.width;
	    height = value.height;

		return *this;
	}

	bool SMRectangle::operator == (const SMRectangle &value) const
	{
	    return (position == value.position && width == value.width && height == value.height);
	}

	bool SMRectangle::operator != (const SMRectangle &value) const
	{
		return (position != value.position || width != value.width || height != value.height);
	}

    int SMRectangle::Left() const
    {
        return position.x;
    }

    int SMRectangle::Right() const
    {
        return (position.x + width);
    }

    int SMRectangle::Top() const
    {
        return position.y;
    }

    int SMRectangle::Bottom() const
    {
        return (position.y + height);
    }

    void SMRectangle::Position(float x, float y)
    {
        position.x = x;
        position.y = y;
    }

    SMVector2D SMRectangle::Size() const
    {
    	return SMVector2D(width, height);
    }

    SMVector2D SMRectangle::Center() const
    {
        return SMVector2D(position.x + (width / 2), position.y + (height / 2));
    }

    bool SMRectangle::Contains(int x, int y)
    {
        return ((((position.x <= x) && (x < (position.x + width))) && (position.y <= y)) && (y < (position.y + height)));
    }

    bool SMRectangle::Contains(const SMRectangle &value)
    {
        return ((((position.x <= value.position.x) && ((value.position.x + value.width) <= (position.x + width))) &&
                 (position.y <= value.position.y)) && ((value.position.y + value.height) <= (position.y + height)));
    }

    bool SMRectangle::Intersects(const SMRectangle &value)
    {
        return ((((value.position.x < (position.x + width)) && (position.x < (value.position.x + value.width))) &&
                 (value.position.y < (position.y + height))) && (position.y < (value.position.y + value.height)));
    }
};};
