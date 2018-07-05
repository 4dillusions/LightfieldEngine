#pragma once

namespace SMEngine { namespace Math
{
    /*
    TODO: nincs még kész
    */
	class SMMatrix4
	{
	public:
		float m[4][4];

		SMMatrix4();

		//float operator() (int indexX, int indexY) const; //float a = matrix(0, 0);
		//float &operator() (int indexX, int indexY); //matrix(0, 0) = 22.12;

		SMMatrix4 operator * (const SMMatrix4 &value) const; //konkatenált
		SMMatrix4 operator + (const SMMatrix4 &value) const;
		SMMatrix4 operator - (const SMMatrix4 &value) const;

		bool operator == (const SMMatrix4 &value) const;
		bool operator != (const SMMatrix4 &value) const;

		void Zero(); //nullmátrix
		void Identity(); //egységmátrix
	};
};};
