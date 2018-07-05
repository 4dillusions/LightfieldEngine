#pragma once

#ifdef BADA_PLATFORM
#include "FBaseString.h"
#include "FBase.h"

using namespace Osp::Base;
#endif

namespace SMEngine { namespace Core
{
	/*
	Saj�t sz�veg t�pus.

	Haszn�lat:
	SMString text;
	text.Append(errorCounter);
	SMLogger::Instance().WriteOutput(text);
	*/
	class SMString
	{
	private:
		char *data;

		#ifdef BADA_PLATFORM
		Osp::Base::String badaString;
		#endif

		int size; //a lez�r� karakterrel egy�tt a string m�rete
		int hashCode; //a karakterl�nc hash k�dja
		static const int dataSize = 256;

		void CopyInThis(int index, const char *text); //a data-ba pakolja a szoveget
		int GetDigits(int number); //egy eg�sz sz�mr�l megmondja h�ny sz�mjegyb�l �ll
		void CopyInThis(int number); //a data-ba teszi az egyjegy� eg�sz sz�mb�l konvert�lt char-t az utols� helyre
		void CopyInThis(int index, int number); //a data-ba teszi a t�bbjegy� eg�sz sz�mb�l konvert�lt sz�veget
		int GetCharacterHashCode(char character, int index); //visszaad egy k�dsz�mot a karakter �s a t�mbben val� helyzete alapj�n

	public:
		SMString();
		SMString(int size);
		SMString(const char *text);
		SMString(const SMString &value);

		~SMString();

		SMString &operator = (const SMString &value);
		char operator [] (int index) const;
		bool operator < (const SMString &value) const;
		bool operator == (const SMString &value) const;

		const char *const ToChar() const
		{
			return data;
		}

		#ifdef BADA_PLATFORM
		const mchar *const ToBadaChar();
		Osp::Base::String ToBadaString();
		#endif

		void Clear();
		void Append(const char *text);
		SMString AppendStr(const char *text);
		void Append(const SMString &value);
		SMString AppendStr(const SMString &value);
		void Append(int number);
		SMString AppendStr(int number);
		void Append(int number, int digits); //kieg�sz�t�ses sz�mra konvert�l�s, ha a sz�m kisebb, mint a sz�mjegyek, akkor 0-val eg�sz�ti ki
		SMString AppendStr(int number, int digits);

		int Lenght() const //z�r�karakter n�lk�l a sz�veg hossza
		{
			return (size - 1);
		}

		int HashCode() const
		{
			return hashCode;
		}
	};
};};
