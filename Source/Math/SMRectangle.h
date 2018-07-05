#pragma once

#include "SMVector2D.h"

namespace SMEngine { namespace Math
{
    /*
    Egy t�glalap/n�gyzet ter�letet hatroz meg poz�ci�cal.

    Haszn�lat:
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
        bool Contains(const SMRectangle &value); //tartalmazza a m�sik rectangle-t, nem l�ghat ki bel�le
        bool Intersects(const SMRectangle &value); //�rinti a m�sik rectangle-t, �tk�z�s
	};
};};
