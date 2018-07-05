/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFString.h"
#include "LFMemoryManager.h"
#include "..\Math\LFMath.h"

#ifdef TIZEN
#include <Elementary.h>
#endif

using namespace LFCore::Math;

namespace LFCore { namespace Common
{
	LFString::LFString() : data(nullptr),
			#ifdef WIN32
			winString(nullptr),
			#endif
			size(0), hashCode(0)
	{
		capacity = minCapacity;
		data = LFNewArray<char>(AT, capacity);
	}

	LFString::LFString(int size) : data(nullptr),
			#ifdef WIN32
			winString(nullptr),
			#endif
			size(0), hashCode(0)
	{
		if (size < minCapacity)
			size = minCapacity;

		capacity = size + 1;
		data = LFNewArray<char>(AT, capacity);
	}

	LFString::LFString(const char *text) : data(nullptr),
			#ifdef WIN32
			winString(nullptr),
			#endif
			size(0), hashCode(0)
	{
		capacity = GetCharLength(text);
		if (capacity < minCapacity)
			capacity = minCapacity;

		data = LFNewArray<char>(AT, capacity);
		CopyInThis(size, text);
	}

	LFString::LFString(const LFString &value) : data(nullptr),
			#ifdef WIN32
			winString(nullptr),
			#endif
			size(0), hashCode(0)
	{
		capacity = value.size;
		data = LFNewArray<char>(AT, capacity);
		CopyInThis(size, value.data);
	}

	LFString::~LFString()
	{
		if (data != nullptr)
			LFDeleteArray(data);

		#ifdef WIN32
		if (winString != nullptr)
			LFDeleteArray(winString);
		#endif
	}

	void LFString::CopyInThis(int index, const char *text)
	{
		if (size > 0)
			hashCode -= GetCharacterHashCode('\0', size);

		for (int dataIndex = index, textIndex = 0; ; ++dataIndex, ++textIndex)
		{
			if (size > capacity)
				return;

			data[dataIndex] = text[textIndex];
			hashCode += GetCharacterHashCode(data[dataIndex], dataIndex);
			size++;

			if (text[textIndex] == '\0')
				break;
		}
	}

	int LFString::GetDigits(int number)
	{
		for (int result = 1, numTemp = number; ; result++)
		{
			if (numTemp < 10) return result;
			numTemp = numTemp / 10;
		}

		return 0;
	}

	void LFString::CopyInThis(int number)
	{
		if (size > capacity)
			return;

		data[size] = (char)(number + 48);
		hashCode += GetCharacterHashCode((char)(number + 48), size);
		size++;

		data[size] = '\0';
		hashCode += GetCharacterHashCode(data[size], size);
		size++;
	}

	void LFString::CopyInThis(int index, int number)
	{
		if (size > 0)
			hashCode -= GetCharacterHashCode('\0', size);

		if (number < 10)
		{
			CopyInThis(number);
		}
		else
		{
			int *numBuffer = LFNewArray<int>(AT, 11);

			for (int digits = 1, numTemp = number; ; digits++)
			{
				numBuffer[11 - digits] = numTemp % 10;

				if (numTemp < 10)
				{
					for (int i = 11 - digits, dataIndex = index; i < 11; ++i, ++dataIndex)
					{
						if (size > capacity)
							return;

						data[dataIndex] = (char)(numBuffer[i] + 48);

						size++;
						hashCode += GetCharacterHashCode(data[dataIndex], dataIndex);
					}

					if (size > capacity)
						return;

					data[size] = '\0';
					hashCode += GetCharacterHashCode(data[size], size);
					size++;

					LFDeleteArray(numBuffer);
					break;
				}

				numTemp = numTemp / 10;
			}
		}
	}

	int LFString::GetCharacterHashCode(char character, int index)
	{
		return ((int)character * 31 ^ index);
	}

	LFString &LFString::operator = (const LFString &value)
	{
		if (this == &value)
			return *this;

		if (data != nullptr)
			LFDeleteArray(data);

		size = 0;
		hashCode = 0;
		capacity = value.size;
		data = LFNewArray<char>(AT, capacity);
		CopyInThis(size, value.data);

		return *this;
	}

	LFString &LFString::operator += (const LFString &value)
	{
		Append(value);

		return *this;
	}

	LFString &LFString::operator += (const char *text)
	{
		Append(text);

		return *this;
	}

	LFString &LFString::operator += (int number)
	{
		Append(number);

		return *this;
	}

	LFString &LFString::operator += (float floatNumber)
	{
		Append(floatNumber);

		return *this;
	}

	LFString LFString::operator + (const LFString &value) const
	{
		LFString result;

		result.Append(data);
		result.Append(value);

		return  result;
	}

	char LFString::operator [] (int index) const
	{
		return data[index];
	}

	char &LFString::operator [] (int index)
	{
		return data[index];
	}

	bool LFString::operator < (const LFString &value) const
	{
		return (hashCode < value.HashCode());
	}

	bool LFString::operator == (const LFString &value) const
	{
		return (hashCode == value.HashCode());
	}

	bool LFString::IsCharAraysEqual(const char *value1, const char *value2)
	{
		int value1HashCode = 0;
		for (int i = 0; value1[i] != '\0'; i++)
			value1HashCode += GetCharacterHashCode(value1[i], i);

		int value2HashCode = 0;
		for (int i = 0; value2[i] != '\0'; i++)
			value2HashCode += GetCharacterHashCode(value2[i], i);

		return (value1HashCode == value2HashCode);
	}

	bool LFString::operator != (const LFString &value) const
	{
		return (hashCode != value.HashCode());
	}

	const char *const LFString::ToChar() const
	{
		return data;
	}

	char *LFString::ToNewChar()
	{
		char *result;

		result = (char *)malloc(strlen(data) + 1);
		strcpy(result, data);

		return result;
	}

	#ifdef WIN32
	LPCWSTR LFString::ToLpcwstr()
	{
		if (winString != nullptr)
			LFDeleteArray(winString);

		int length = strlen(data) + 1;
		winString = LFNewArray<wchar_t>(AT, length);
		memset(winString, 0, length);
		MultiByteToWideChar(0, NULL, data, -1, winString, length);
	
		return winString;
	}

	LPCTSTR LFString::ToLpctstr()
	{
		return (LPCTSTR)ToLpcwstr();
	}
	#endif

	int LFString::ToInt()
	{
		int result = 0;
		int digits[maxNumberDigits];
		int digitCount = 0;

		while(data[digitCount] != '\0')
		{
			if (!IsDigitFromCharArray(data[digitCount]))
				return 0;

			if (digitCount > maxNumberDigits)
				return 0;

			digits[digitCount] = (int)data[digitCount] - '0';
			++digitCount;
		}
	
		for (int index = digitCount - 1, pow = 1; index >= 0; --index, pow *= 10)
			result += digits[index] * pow;

		return result;
	}

	void LFString::Clear()
	{
		data[0] = '\0';
		size = 0;
		hashCode = 0;
	}

	void LFString::Append(const char *text)
	{
		if (size > 0) size--;
		CopyInThis(size, text);
	}

	LFString LFString::AppendStr(const char *text)
	{
		LFString result;
		result.Append(text);

		return result;
	}

	void LFString::Append(const LFString &value)
	{
		if (size > 0) size--;
		CopyInThis(size, value.data);
	}

	LFString LFString::AppendStr(const LFString &value)
	{
		LFString result;
		result.Append(value);

		return result;
	}

	void LFString::Append(int number)
	{
		if (size > 0) size--;
		CopyInThis(size, number);
	}

	LFString LFString::AppendStr(int number)
	{
		LFString result;
		result.Append(number);

		return result;
	}

	void LFString::Append(float floatNumber)
	{
		Append((int)floatNumber);
		Append(".");

		float rightNum = floatNumber - (int)floatNumber;
		int num = 0;
		for (int pow = 1; pow < 5; ++pow)
		{
			num = rightNum * LFMath::Pow(10, pow);

			if (num % 10 == 0)
				break;
		}
		Append(num);
	}

	LFString LFString::AppendStr(float floatNumber)
	{
		LFString result;
		result.Append(floatNumber);

		return result;
	}

	void LFString::Append(int number, int digits)
	{
		int length = GetDigits(number);

		if (length < digits)
		{
			for (int i = 0; i < (digits - length); ++i)
			{
	    		Append(0);
			}

			Append(number);
		}
		else
			Append(number / (int)LFMath::Pow(10, length - digits));
	}

	LFString LFString::AppendStr(int number, int digits)
	{
		LFString result;
		result.Append(number, digits);

		return result;
	}

	int LFString::Length() const
	{
		return (size - 1);
	}

	int LFString::LengthNoSpace() const
	{
		int result = 0;

		for (int i = 0; i < Length(); ++i)
			if (data[i] != ' ')
				++result;

		return result;
	}

	int LFString::HashCode() const
	{
		return hashCode;
	}

	int LFString::GetCharLength(const char *text)
	{
		int result = 0;
		for (; text[result] != '\0'; result++)
			;

		return result + 1;
	}

	bool LFString::IsDigitFromChar(char character)
	{
		return ((int)character >= 0 && (int)character <= 9);
	}

	bool LFString::IsDigitFromCharArray(char character)
	{
		return (character >= '0' && character <= '9');
	}

	bool LFString::IsAlphabetChar(char character)
	{
		return ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'));
	}

	bool LFString::IsEqual(const char *text1, const char *text2)
	{
		int index1 = 0, index2 = 0;
		for (; text1[index1] != '\0' || text2[index2] != '\0'; index1++, index2++)
			if (text1[index1] != text2[index2])
				return false;

		return (index1 == index2);
	}

	bool LFString::Search(const char *text, int counter)
	{
		bool isFirstMatch = false;
		for (; data[counter] != '\0'; counter++)
			if (data[counter] == text[0])
			{
				isFirstMatch = true;
				break;
			}

		if (isFirstMatch)
		{
			int index1 = counter, index2 = 0;
			for (; data[index1] != '\0' || text[index2] != '\0'; index1++, index2++)
				if (text[index2] == '\0' || data[index1] != text[index2])
					break;

			if (index2 == GetCharLength(text) - 1)
				return true;
			else if (index1 < Length())
				return Search(text, counter + 1);
		}

		return false;
	}

	bool LFString::Search(const LFString &text)
	{
		return Search(text.ToChar());
	}
}}
