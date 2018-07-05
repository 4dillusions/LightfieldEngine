#pragma once

namespace SMEngine { namespace Math
{
    /*
    TODO: nincs m�g k�sz
    */
	class SMMatrix4
	{
	public:
		float m[4][4];

		SMMatrix4();

		//float operator() (int indexX, int indexY) const; //float a = matrix(0, 0);
		//float &operator() (int indexX, int indexY); //matrix(0, 0) = 22.12;

		SMMatrix4 operator * (const SMMatrix4 &value) const; //konkaten�lt
		SMMatrix4 operator + (const SMMatrix4 &value) const;
		SMMatrix4 operator - (const SMMatrix4 &value) const;

		bool operator == (const SMMatrix4 &value) const;
		bool operator != (const SMMatrix4 &value) const;

		void Zero(); //nullm�trix
		void Identity(); //egys�gm�trix
	};
};};
