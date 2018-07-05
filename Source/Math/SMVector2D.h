#pragma once

namespace SMEngine { namespace Math
{
    /*
    Pont a 2D térben.

    Használat:
    SMVector2D vec(20, 30);
    SMVector2D vec2 = vec;
    SMVector2D vec3;
    vec3 = vec;

    SMVector2D vec4 = (SMVector2D)12; //implicit cast only

    A többi operátor szokásosan használható.
    */
	class SMVector2D
	{
	public:
		float x, y;

		SMVector2D() : x(0.0f), y(0.0f) {}
		SMVector2D(const float x, const float y) : x(x), y(y) {}
		explicit SMVector2D(const float scale) : x(scale), y(scale) {}

		SMVector2D &operator = (const SMVector2D &value);

		bool operator == (const SMVector2D &value) const;
		bool operator != (const SMVector2D &value) const;

		SMVector2D operator + (const SMVector2D &value) const;
		SMVector2D operator + (const float size) const;

		SMVector2D operator - (const SMVector2D &value) const;
		SMVector2D operator - (const float size) const;

		SMVector2D operator * (const SMVector2D &value) const;
		SMVector2D operator * (const float size) const;

		SMVector2D operator / (const SMVector2D &value) const;
		SMVector2D operator / (const float size) const;

		SMVector2D operator - () const;

		SMVector2D &operator ++ ();
		SMVector2D &operator ++ (int);
		SMVector2D &operator -- ();
		SMVector2D &operator -- (int);

		SMVector2D &operator += (const SMVector2D &value);
		SMVector2D &operator += (const float size);

		SMVector2D &operator -= (const SMVector2D &value);
		SMVector2D &operator -= (const float size);

		SMVector2D &operator *= (const SMVector2D &value);
		SMVector2D &operator *= (const float size);

		SMVector2D &operator /= (const SMVector2D &value);
		SMVector2D &operator /= (const float size);

		bool operator < (const SMVector2D &value) const;
		bool operator > (const SMVector2D &value) const;

		void Zero();
		void Rotate(float angle);
		void RotateCeil(float angle); //Kerekítéses forgatás
		void Rotate90DegreeForward(); //óramutatóval megegyezõ
		void Rotate90DegreeBackward(); //óramutatóval ellentétse
	};
};};
