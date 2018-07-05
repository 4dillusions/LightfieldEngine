#pragma once

#ifdef BADA_PLATFORM
#include "FBaseString.h"
#include "FBase.h"

using namespace Osp::Base;
#endif

namespace SMEngine { namespace Core
{
	/*
	Saját szöveg típus.

	Használat:
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

		int size; //a lezáró karakterrel együtt a string mérete
		int hashCode; //a karakterlánc hash kódja
		static const int dataSize = 256;

		void CopyInThis(int index, const char *text); //a data-ba pakolja a szoveget
		int GetDigits(int number); //egy egész számról megmondja hány számjegybõl áll
		void CopyInThis(int number); //a data-ba teszi az egyjegyû egész számból konvertált char-t az utolsó helyre
		void CopyInThis(int index, int number); //a data-ba teszi a többjegyû egész számból konvertált szöveget
		int GetCharacterHashCode(char character, int index); //visszaad egy kódszámot a karakter és a tömbben való helyzete alapján

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
		void Append(int number, int digits); //kiegészítéses számra konvertálás, ha a szám kisebb, mint a számjegyek, akkor 0-val egészíti ki
		SMString AppendStr(int number, int digits);

		int Lenght() const //zárókarakter nélkül a szöveg hossza
		{
			return (size - 1);
		}

		int HashCode() const
		{
			return hashCode;
		}
	};
};};
