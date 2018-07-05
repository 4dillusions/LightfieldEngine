/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFString.h"
#include "LFMemoryManager.h"
#include "..\LFCore.h"
#include "..\LFMath\LFMath.h"

#ifdef WINCLASSIC
#include "winnls.h"
#endif

using namespace LF3Engine::LFEngine::LFCore::LFCollections;

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon
{
	LFString::LFString()
	{
		data = LFMemoryManager::NewArray<char>(INFO, dataSize);
		data[0] = NullCharacter;
	}

	LFString::LFString(const LFString &value)
	{
		*this = value;
	}

	LFString::LFString(const LFString &&value)
	{
		*this = std::move(value);
	}

	LFString::LFString(const char *text)
	{
		textLenght = GetTextLength(text);

		if (textLenght + 1 > dataSize)
			dataSize = (textLenght + 1) * 2;
	
		data = LFMemoryManager::NewArray<char>(INFO, dataSize);

		if (text == nullptr)
			data[0] = NullCharacter;
		else
		{
			for (int i = 0; i < textLenght + 1; i++)
				data[i] = text[i];

			hashCode += GetHashCode(text, textLenght, 0);
		}
	}

	LFString::LFString(char letter)
	{
		textLenght = 1;
		dataSize = MinDataSize;
		data = LFMemoryManager::NewArray<char>(INFO, dataSize);

		data[0] = letter;
		data[1] = NullCharacter;

		hashCode += GetHashCode(letter, 0);
	}

	LFString::LFString(int number)
	{
		*this = number;
	}

	LFString::LFString(float floatNumber)
	{
		*this = floatNumber;
	}

	LFString::~LFString()
	{
		LFMemoryManager::DeleteArray(data);

#ifdef WINCLASSIC
		if (winString != nullptr)
			LFMemoryManager::DeleteArray(winString);
#endif
	}

	LFString &LFString::operator=(const LFString &value)
	{
		if (this != &value)
		{
			LFMemoryManager::DeleteArray(data);

			textLenght = value.textLenght;
			dataSize = value.dataSize;
			hashCode = value.hashCode;

			data = LFMemoryManager::NewArray<char>(INFO, dataSize);
			for (int i = 0; i < textLenght + 1; i++)
				data[i] = value.data[i];
		}

		return *this;
	}

	LFString &LFString::operator=(LFString &&value)
	{
		if (this != &value)
		{
			LFMemoryManager::DeleteArray(data);

			textLenght = value.textLenght;
			dataSize = value.dataSize;
			hashCode = value.hashCode;
			data = value.data;

			value.textLenght = 0;
			value.dataSize = MinDataSize;
			value.hashCode = 0;
			value.data = nullptr;
		}

		return *this;
	}

	LFString &LFString::operator=(const char *text)
	{
		LFMemoryManager::DeleteArray(data);

		textLenght = 0;
		dataSize = MinDataSize;
		hashCode = 0;

		data = LFMemoryManager::NewArray<char>(INFO, dataSize);
		*this += text;

		return *this;
	}

	LFString &LFString::operator=(char letter)
	{
		LFMemoryManager::DeleteArray(data);

		textLenght = 0;
		dataSize = MinDataSize;
		hashCode = 0;

		data = LFMemoryManager::NewArray<char>(INFO, dataSize);
		*this += letter;

		return *this;
	}

	LFString &LFString::operator=(int number)
	{
		LFMemoryManager::DeleteArray(data);

		textLenght = 0;
		dataSize = MinDataSize;
		hashCode = 0;

		data = LFMemoryManager::NewArray<char>(INFO, dataSize);
		*this += number;

		return *this;
	}

	LFString &LFString::operator=(float floatNumber)
	{
		LFMemoryManager::DeleteArray(data);

		textLenght = 0;
		dataSize = MinDataSize;
		hashCode = 0;

		data = LFMemoryManager::NewArray<char>(INFO, dataSize);
		*this += floatNumber;

		return *this;
	}

	LFString LFString::operator+(const LFString &value) const
	{
		LFString result(*this);
		result += value;
	
		return result;
	}

	LFString LFString::operator+(char letter) const
	{
		LFString result(*this);
		result += letter;

		return result;
	}

	LFString LFString::operator+(const char* text) const
	{
		LFString result(*this);
		result += text;

		return result;
	}

	LFString LFString::operator+(int number) const
	{
		LFString result(*this);
		result += number;

		return result;
	}

	LFString LFString::operator+(float floatNumber) const
	{
		LFString result(*this);
		result += floatNumber;

		return result;
	}

	LFString &LFString::operator+=(const LFString &value)
	{
		int newTextSize = textLenght + value.textLenght + 1;
		if (dataSize < newTextSize)
			IncrementDataSize(newTextSize * 2);

		for (int currentIndex = textLenght, valueIndex = 0; currentIndex < newTextSize; currentIndex++, valueIndex++)
			data[currentIndex] = value.data[valueIndex];

		hashCode += GetHashCode(value.data, value.textLenght, textLenght);
		textLenght += value.textLenght;

		return *this;
	}

	LFString &LFString::operator+=(const char *text)
	{
		*this += LFString(text);
		return *this;
	}

	LFString &LFString::operator+=(char letter)
	{
		if (dataSize < textLenght + 1)
			IncrementDataSize();

		data[textLenght] = letter;
		data[textLenght + 1] = NullCharacter;

		hashCode += GetHashCode(letter, textLenght);
		textLenght++;

		return *this;
	}

	LFString &LFString::operator+=(int number)
	{
		int numberLenght = GetNumberLength(number);
		if (numberLenght <= MaxNumberDigits)
		{
			int newTextSize = textLenght + numberLenght + 1;
			if (dataSize < newTextSize)
				IncrementDataSize();

			char digitsTemp[MaxNumberDigits];
			for (int i = MaxNumberDigits - 1; i > 0; i--)
			{
				if (number >= 10)
				{
					digitsTemp[i] = static_cast<char>(number % 10) + NumberToChar;
					number /= 10;
				}
				else
				{
					digitsTemp[i] = static_cast<char>(number) + NumberToChar;
					break;
				}
			}

			char digits[MaxNumberDigits];
			for (int digitsIndex = 0, tempIndex = MaxNumberDigits - numberLenght; digitsIndex < numberLenght; digitsIndex++, tempIndex++)
				digits[digitsIndex] = digitsTemp[tempIndex];

			for (int currentIndex = textLenght, digitsIndex = 0; digitsIndex < numberLenght; currentIndex++, digitsIndex++)
				data[currentIndex] = digits[digitsIndex];

			data[textLenght + numberLenght] = NullCharacter;

			hashCode += GetHashCode(digits, numberLenght, textLenght);
			textLenght += numberLenght;
		}

		return *this;
	}

	LFString &LFString::operator+=(float floatNumber)
	{
		*this += static_cast<int>(floatNumber);
		*this += FloatNumberSplit;

		float rightNum = floatNumber - static_cast<int>(floatNumber);
		int num = 0;
		for (int pow = 1; pow < MaxNumberDigits; ++pow)
		{
			num = static_cast<int>(rightNum * LFMath::LFMath::Pow(10, static_cast<float>(pow)));

			if (num % 10 == 0)
				break;
		}
	
		*this += num;

		return *this;
	}

	char LFString::operator[](int index) const
	{
		return data[index];
	}

	char &LFString::operator[](int index)
	{
		return data[index];
	}

	bool LFString::operator<(const LFString &value) const
	{
		return hashCode < value.hashCode;
	}

	bool LFString::operator==(const LFString &value) const
	{
		return hashCode == value.hashCode;
	}

	bool LFString::operator!=(const LFString &value) const
	{
		return hashCode != value.hashCode;
	}

	LFString::operator int() const
	{
		return hashCode;
	}

	const char *LFString::ToChar() const
	{
		return data;
	}

	std::wstring LFString::ToWString() const
	{
		std::string stdText(data);
		std::wstring wsText;
		wsText.assign(stdText.begin(), stdText.end());
		wsText.append(L"\r\n");

		return wsText;
	}

#ifdef WINCLASSIC
	LPCWSTR LFString::ToLpcwstr()
	{
		if (winString != nullptr)
			LFMemoryManager::DeleteArray(winString);

		int length = strlen(data) + 1;
		winString = LFMemoryManager::NewArray<wchar_t>(INFO, length);
		memset(winString, 0, length);
		MultiByteToWideChar(0, NULL, data, -1, winString, length);

		return winString;
	}

	LPCTSTR LFString::ToLpctstr()
	{
		return static_cast<LPCTSTR>(ToLpcwstr());
	}
#endif

	int LFString::ToInt() const
	{
		int result = 0;
		int digits[MaxNumberDigits];
		int digitIndex = 0;

		while (data[digitIndex] != NullCharacter)
			if (data[digitIndex] >= '0' && data[digitIndex] <= '9' && digitIndex < MaxNumberDigits)
            {
                digits[digitIndex] = data[digitIndex] - '0';
                digitIndex++;
            }
			else
                return 0;

		for (int index = digitIndex - 1, pow = 1; index >= 0; --index, pow *= 10)
			result += digits[index] * pow;

		return result;
	}

	float LFString::ToFloat() const
	{
		float result = 0;

		int leftCount = 0;
		int rightCount = 0;
	
		for (int i = 0; i < textLenght; i++)
			if (IsNumberDigit(data[i]))
				leftCount++;
			else
			{
				if (data[i] == FloatNumberSplit)
					break;

				return 0;
			}
	
		for (int i = leftCount + 1; i < textLenght; i++)
			if (IsNumberDigit(data[i]))
				rightCount++;
			else
				return 0;

		if (leftCount == 0 || rightCount == 0)
			return 0;

		for (int dataIndex = leftCount + 1, pow = 1; dataIndex < textLenght; dataIndex++, pow++)
			result += (static_cast<int>(data[dataIndex]) - NumberToChar) / LFMath::LFMath::Pow(10, pow);

		for (int dataIndex = 0, pow = leftCount - 1; dataIndex < leftCount; dataIndex++, pow--)
			result += (static_cast<int>(data[dataIndex]) - NumberToChar) * LFMath::LFMath::Pow(10, pow);

		return result;
	}

	void LFString::IncrementDataSize(int dataSize)
	{
		if (dataSize == 0)
			this->dataSize *= 2;
		else
			this->dataSize = dataSize;

		LFString temp(*this);
		*this = temp;
	}

	int LFString::GetHashCode(const char *text, int lenght, int hashIndex)
	{
		int result = 0;

		for (int i = 0; i < lenght; i++, hashIndex++)
			result += (static_cast<int>(text[i]) * 31 ^ hashIndex);

		return result;
	}

	int LFString::GetHashCode(const char letter, int hashIndex)
	{
		return (static_cast<int>(letter) * 31 ^ hashIndex);
	}

	int LFString::GetNumberLength(int number)
	{
		int result = 1;
	
		while (number /= 10)
			result++;

		return result;
	}

	int LFString::GetTextLength(const char *text)
	{
		int result = 0;

		if (text != nullptr)
			for (; text[result] != NullCharacter; result++)
				;

		return result;
	}

	bool LFString::IsAbcLetter(char letter)
	{
		return (letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z');
	}

	bool LFString::IsNumberDigit(char num)
	{
		return (num >= '0' && num <= '9');
	}

	void LFString::CopyToArray(const char *text, char *textArray)
	{
		int index = 0;
		for (; text[index] != NullCharacter; index++)
			textArray[index] = text[index];

		textArray[index] = NullCharacter;
	}

	int LFString::GetTextLength() const
	{
		return textLenght;
	}

	int LFString::GetTextLenghtWithoutSpace() const
	{
		int result = 0;
		for (int i = 0; i < textLenght; i++)
			if (data[i] != SpaceCharacter)
				result++;

		return result;
	}

	bool LFString::IsEmpty() const
	{
		return textLenght == 0;
	}

	int LFString::GetDataSize() const
	{
		return dataSize;
	}

	int LFString::GetHashCode() const
	{
		return hashCode;
	}

	bool LFString::IsExist(const LFString &text) const
	{
		if (text.textLenght > textLenght)
			return false;

		for (int currentDataIndex = 0; currentDataIndex < textLenght; currentDataIndex++)
			if (data[currentDataIndex] == text.data[0] && (textLenght - currentDataIndex + 1 - text.textLenght) > 0)
			{
				int matchCharacterCount = 0;
				for (int dataIndex = currentDataIndex, textIndex = 0; textIndex < text.textLenght; dataIndex++, textIndex++)
					if (data[dataIndex] == text.data[textIndex])
						matchCharacterCount++;

				if (matchCharacterCount == text.textLenght)
					return true;
			}

		return false;
	}

	bool LFString::IsExist(char letter) const
	{
		for (int i = 0; i < textLenght; i++)
			if (data[i] == letter)
				return true;

		return false;
	}

	int LFString::GetExistCount(const LFString &text) const
	{
		int result = 0;

		if (text.textLenght > textLenght)
			return result;

		for (int currentDataIndex = 0; currentDataIndex < textLenght; currentDataIndex++)
			if (data[currentDataIndex] == text.data[0] && (textLenght - currentDataIndex + 1 - text.textLenght) > 0)
			{
				int matchCharacterCount = 0;
				for (int dataIndex = currentDataIndex, textIndex = 0; textIndex < text.textLenght; dataIndex++, textIndex++)
					if (data[dataIndex] == text.data[textIndex])
						matchCharacterCount++;

				if (matchCharacterCount == text.textLenght)
					result++;
			}

		return result;
	}

	int LFString::GetExistCount(char letter) const
	{
		int result = 0;

		for (int i = 0; i < textLenght; i++)
			if (data[i] == letter)
				result++;

		return result;
	}

	bool LFString::IsStartsWith(const LFString &text) const
	{
		if (text.textLenght > textLenght)
			return false;

		for (int i = 0; i < text.textLenght; i++)
			if (data[i] != text.data[i])
				return false;

		return true;
	}

	bool LFString::IsStartsWith(char letter) const
	{
		return data[0] == letter;
	}

	bool LFString::IsEndsWith(const LFString &text) const
	{
		if (text.textLenght > textLenght)
			return false;

		for (int textIndex = 0, dataIndex = textLenght - text.textLenght; textIndex < text.textLenght; textIndex++, dataIndex++)
			if (data[dataIndex] != text.data[textIndex])
				return false;

		return true;
	}

	bool LFString::IsEndsWith(char letter) const
	{
		return data[textLenght - 1] == letter;
	}

	void LFString::Replace(const LFString &oldText, const LFString &newText)
	{
		if (textLenght > 0)
		{
			int tempTextLenght = 0;
			int tempDataSize = dataSize;
			auto tempData = LFMemoryManager::NewArray<char>(INFO, tempDataSize);

			int existCount = 0;

			for (int dataIndex = 0, tempDataIndex = 0; dataIndex < textLenght; dataIndex++, tempDataIndex++)
			{
				tempData[tempDataIndex] = data[dataIndex];
				tempTextLenght++;

				int oldTextCounter = 0;
				for (int oldTextIndex = 0, currentIndex = dataIndex; oldTextIndex < oldText.textLenght; oldTextIndex++, currentIndex++)
					if (data[currentIndex] == oldText.data[oldTextIndex])
						oldTextCounter++;

				if (oldTextCounter == oldText.textLenght)
				{
					existCount++;
					tempTextLenght--;
					dataIndex += oldText.textLenght - 1;

					for (int newTextIndex = 0; newTextIndex < newText.textLenght; newTextIndex++)
					{
						if (tempTextLenght + 1 > tempDataSize)
						{
							LFString tempString(tempData);

							tempDataSize *= 2;
							LFMemoryManager::DeleteArray(tempData);
							tempData = LFMemoryManager::NewArray<char>(INFO, tempDataSize);

							for (int i = 0; i < tempTextLenght; i++)
								tempData[i] = tempString[i];
						}

                        tempData[tempDataIndex++] = newText.data[newTextIndex];
						tempTextLenght++;
					}

					tempDataIndex--;
				}
			}

			if (existCount == 0)
				LFMemoryManager::DeleteArray(tempData);
			else
			{
				LFMemoryManager::DeleteArray(data);
				data = tempData;
				dataSize = tempDataSize;

				textLenght = tempTextLenght;
				data[textLenght] = NullCharacter;
				hashCode = GetHashCode(data, textLenght, 0);
			}
		}
	}

	void LFString::Replace(char oldLetter, char newLetter)
	{
		if (textLenght > 0)
			for (int dataIndex = 0; dataIndex < textLenght; dataIndex++)
				if (data[dataIndex] == oldLetter)
				{
					hashCode -= GetHashCode(oldLetter, dataIndex);
					data[dataIndex] = newLetter;
					hashCode += GetHashCode(newLetter, dataIndex);
				}
	}

	void LFString::Replace(char letter, int index)
	{
		if (textLenght > index)
		{
			hashCode -= GetHashCode(data[index], index);
			data[index] = letter;
			hashCode += GetHashCode(letter, index);
		}
	}

	void LFString::Replace(int number, int digits)
	{
		Clear();

		if (digits <= MaxNumberDigits)
		{
			int numberLenght = GetNumberLength(number);

			if (numberLenght < digits)
				for (int i = 0; i < (digits - numberLenght); ++i)
				{
					data[textLenght] = '0';
					hashCode += GetHashCode('0', textLenght++);
				}

			*this += number;
		}
	}

	void LFString::Remove(int startIndex, int count)
	{
		if (startIndex + count <= textLenght)
		{
			auto tempText = LFMemoryManager::NewArray<char>(INFO, textLenght + 1);

			int tempIndex = 0;
			for (int dataIndex = 0; dataIndex < startIndex; tempIndex++, dataIndex++)
				tempText[tempIndex] = data[dataIndex];

			for (int dataIndex = startIndex + count; dataIndex < textLenght + 1; tempIndex++, dataIndex++)
				tempText[tempIndex] = data[dataIndex];

			LFMemoryManager::DeleteArray(data);
			data = tempText;
			textLenght -= count;
			hashCode = GetHashCode(data, textLenght, 0);
		}
	}

	void LFString::Remove(const LFString &text)
	{
		if (text.textLenght <= textLenght)
		{
			auto tempText = LFMemoryManager::NewArray<char>(INFO, textLenght + 1);

			int tempIndex = 0;
			for (int dataIndex = 0; dataIndex < textLenght + 1; dataIndex++)
			{
				tempText[tempIndex++] = data[dataIndex];

				bool isExist = true;
				for (int i = 0; i < text.textLenght; i++)
					if (data[dataIndex + i] != text.data[i])
					{
						isExist = false;
						break;
					}

				if (isExist)
				{
					tempIndex--;
					dataIndex += (text.textLenght - 1);
				}
			}

			LFMemoryManager::DeleteArray(data);
			data = tempText;
			textLenght = tempIndex - 1;
			hashCode = GetHashCode(data, textLenght, 0);
		}
	}

	void LFString::Remove(char Letter)
	{
		if (textLenght > 0)
		{
			auto tempText = LFMemoryManager::NewArray<char>(INFO, textLenght + 1);

			int tempIndex = 0;
			for (int dataIndex = 0; dataIndex < textLenght + 1; dataIndex++)
				if (data[dataIndex] != Letter)
					tempText[tempIndex++] = data[dataIndex];

			LFMemoryManager::DeleteArray(data);
			data = tempText;
			textLenght = tempIndex - 1;
			hashCode = GetHashCode(data, textLenght, 0);
		}
	}

	void LFString::Trim()
	{
		/*
			White space characters
			' ' (0x20) space(SPC)
			'\t' (0x09) horizontal tab(TAB)
			'\n' (0x0a) newline(LF)
			'\v' (0x0b) vertical tab(VT)
			'\f' (0x0c) feed(FF)
			'\r' (0x0d) carriage return (CR)
		*/
		char whiteSpaceCharacters[] = " \t\n\v\f\r";
		auto tempText = LFMemoryManager::NewArray<char>(INFO, textLenght + 1);

		bool isWhiteCpaceCharacter;
		int newTextLenght = 0;
		for (int tempIndex = 0, dataIndex = 0; dataIndex < textLenght + 1; dataIndex++)
		{
			isWhiteCpaceCharacter = false;
            for (unsigned int i = 0; i < sizeof(whiteSpaceCharacters) - 1; i++)
				if (data[dataIndex] == whiteSpaceCharacters[i])
				{
					isWhiteCpaceCharacter = true;
					break;
				}

			if (!isWhiteCpaceCharacter)
			{
				tempText[tempIndex++] = data[dataIndex];
				newTextLenght++;
			}
		}

		textLenght = newTextLenght - 1;

		LFMemoryManager::DeleteArray(data);
		data = tempText;
		hashCode = GetHashCode(data, textLenght, 0);
	}

	void LFString::Clear()
	{
		data[0] = NullCharacter;
		textLenght = 0;
		hashCode = 0;
	}

	LFList<LFString> LFString::Split(char separator) const
	{
		LFList<LFString> result;

		if (textLenght > 0)
		{
			LFString temp;
			for (int i = 0; i < textLenght + 1; i++)
			{
				if (data[i] == separator || i == textLenght)
				{
					result.Add(temp);
					temp.Clear();

					continue;
				}

				temp += data[i];
			}
		}
		
		return result;
	}

	LFList<LFString> LFString::Split(const LFString &text) const
	{
		LFString temp(*this);
		temp.Replace(text, LFString("~"));
		
		return temp.Split('~');
	}
}}}}
