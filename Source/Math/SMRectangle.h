#pragma once

#include "SMVector2D.h"

namespace SMEngine { namespace Math
{
    /*
    Egy téglalap/négyzet területet hatroz meg pozíciócal.

    Használat:
    SMRectangle rectangle(0, 0, 20, 30);
    SMRectangle rectangle2 = rectangle;
    SMRectangle rectangle3;
    rectangle3 = rectangle;
    */
	class SMRectangle
	{
	public:
        SMVector2D position;
        int width, height;

        SMRectangle();
        SMRectangle(int x, int y, int width, int height);

        SMRectangle &operator = (const SMRectangle &value);
        bool operator == (const SMRectangle &value) const;
		bool operator != (const SMRectangle &value) const;

        int Left() const;
        int Right() const;
        int Top() const;
        int Bottom() const;
        void Position(float x, float y);
        SMVector2D Size() const;
        SMVector2D Center() const;

        bool Contains(int x, int y); //tartalmazza az adott pontot
        bool Contains(const SMRectangle &value); //tartalmazza a másik rectangle-t, nem lóghat ki belõle
        bool Intersects(const SMRectangle &value); //érinti a másik rectangle-t, ütközés
	};
};};
