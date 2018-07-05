/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCore.h"

namespace LFCore { namespace Common
{
	class LFCORE_LIBRARY LFString
	{
	private:
		char *data;

		#ifdef WIN32
		wchar_t *winString;
		#endif

		int size;
		int capacity;
		int hashCode;

		void CopyInThis(int index, const char *text);
		int GetDigits(int number);
		void CopyInThis(int number);
		void CopyInThis(int index, int number);
		void AppendCapacity();
		static int GetCharacterHashCode(char character, int index);

	public:
		static const int minCapacity = 512;
		static const int maxNumberDigits = 10;

		LFString();
		explicit LFString(int size); //LFString s = 'a'; //no implicit conversion
		explicit LFString(const char *text);
		LFString(const LFString &value);

		~LFString();

		LFString &operator = (const LFString &value);
		LFString &operator += (const LFString &value);
		LFString &operator += (const char *text);
		LFString &operator += (int number);
		LFString &operator += (float floatNumber);
		LFString operator + (const LFString &value) const;
		char operator [] (int index) const; //char c = text[0];
		char &operator [] (int index); //text[0] = 'A';
		bool operator < (const LFString &value) const;
		bool operator == (const LFString &value) const;
		static bool IsCharAraysEqual(const char *value1, const char *value2);
		bool operator != (const LFString &value) const;

		const char *const ToChar() const;
		char *ToNewChar();

		#ifdef WIN32
		LPCWSTR ToLpcwstr();
		LPCTSTR ToLpctstr();
		#endif

		int ToInt();

		void Clear();
		void Append(const char *text);
		LFString AppendStr(const char *text);
		void Append(const LFString &value);
		LFString AppendStr(const LFString &value);
		void Append(int number);
		LFString AppendStr(int number);
		void Append(float floatNumber);
		LFString AppendStr(float floatNumber);
		void Append(int number, int digits); //Append(3, 4); => 0003
		LFString AppendStr(int number, int digits); //Append(3, 4); => 0003

		int Length() const;
		int LengthNoSpace() const;
		int HashCode() const;
		int Capacity() const { return capacity; }
		bool IsEmpty() { return size < 2; }

		static int GetCharLength(const char *text);
		static bool IsDigitFromChar(char character);
		static bool IsDigitFromCharArray(char character);
		static bool IsAlphabetChar(char character);
		static bool IsEqual(const char *text1, const char *text2);

		bool Search(const char *text, int counter = 0); //text: "X-Ample123", Seacrh("Ample") -> true, Search("1234") -> false
		bool Search(const LFString &text);
	};
}}
