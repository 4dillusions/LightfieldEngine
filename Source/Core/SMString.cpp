#include "SMString.h"
#include "SMCore.h"

namespace SMEngine { namespace Core
{
	void SMString::CopyInThis(int index, const char *text)
	{
		if (size > 0)
			hashCode -= GetCharacterHashCode('\0', size);

		for (int dataIndex = index, textIndex = 0; ; ++dataIndex, ++textIndex)
		{
			data[dataIndex] = text[textIndex];
			hashCode += GetCharacterHashCode(data[dataIndex], dataIndex);
			size++;

			if (text[textIndex] == '\0') break;
		}
	}

	int SMString::GetDigits(int number)
	{
		for (int result = 1, numTemp = number; ; result++)
		{
			if (numTemp < 10) return result;
			numTemp = numTemp / 10;
		}
	}

	void SMString::CopyInThis(int number)
	{
		data[size] = number + 48;
		hashCode += GetCharacterHashCode(number + 48, size);
		size++;

		data[size] = '\0';
		hashCode += GetCharacterHashCode(data[size], size);
		size++;
	}

	void SMString::CopyInThis(int index, int number)
	{
		if (size > 0)
			hashCode -= GetCharacterHashCode('\0', size);

		if (number < 10)
		{
			CopyInThis(number);
		}
		else
		{
			int *numBuffer = new int[11];

			for (int digits = 1, numTemp = number; ; digits++)
			{
				numBuffer[11 - digits] = numTemp % 10;

				if (numTemp < 10)
				{
					for (int i = 11 - digits, dataIndex = index; i < 11; ++i, ++dataIndex)
					{
						data[dataIndex] = numBuffer[i] + 48;

						size++;
						hashCode += GetCharacterHashCode(data[dataIndex], dataIndex);
					}

					data[size] = '\0';
					hashCode += GetCharacterHashCode(data[size], size);
					size++;

					delete []numBuffer;
					break;
				}

				numTemp = numTemp / 10;
			}
		}
	}

	int SMString::GetCharacterHashCode(char character, int index)
    {
		return ((int)character * 31 ^ index);
    }

	SMString::SMString() : data(nullptr), size(0), hashCode(0)
	{
		data = new char[dataSize];
	}

	SMString::SMString(int size) : data(nullptr), size(0), hashCode(0)
	{
		data = new char[size];
	}

	SMString::SMString(const char *text) : data(nullptr), size(0), hashCode(0)
	{
		data = new char[strlen(text) + 1];
		CopyInThis(size, text);
	}

	SMString::SMString(const SMString &value) : size(0), hashCode(0)
	{
		//if (data != nullptr)
			//delete []data;

		data = new char[value.size];
		CopyInThis(size, value.data);
	}

	SMString::~SMString()
	{
		delete []data;
		data = nullptr;
	}

	SMString &SMString::operator = (const SMString &value)
	{
		if (this == &value)
			return *this;

		if (data != nullptr)
			delete []data;

		size = 0;
		hashCode = 0;
		data = new char[value.size];
		CopyInThis(size, value.data);

		return *this;
	}

	char SMString::operator [] (int index) const
	{
		return data[index];
	}

	bool SMString::operator < (const SMString &value) const
	{
		return (hashCode < value.HashCode());
	}

	bool SMString::operator == (const SMString &value) const
	{
		return (hashCode == value.HashCode());
	}

	#ifdef BADA_PLATFORM
	const mchar *const SMString::ToBadaChar()
	{
		badaString = Osp::Base::String(data);
		return badaString.GetPointer();
	}

	Osp::Base::String SMString::ToBadaString()
	{
		badaString = Osp::Base::String(data);
		return badaString;
	}
	#endif

	void SMString::Clear()
	{
		data[0] = '\0';
		size = 0;
		hashCode = 0;
	}

	void SMString::Append(const char *text)
	{
		if (size > 0) size--;
		CopyInThis(size, text);
	}

	SMString SMString::AppendStr(const char *text)
	{
		SMString result;
		result.Append(text);

		return result;
	}

	void SMString::Append(const SMString &value)
	{
		if (size > 0) size--;
		CopyInThis(size, value.data);
	}

	SMString SMString::AppendStr(const SMString &value)
	{
		SMString result;
		result.Append(value);

		return result;
	}

	void SMString::Append(int number)
	{
		if (size > 0) size--;
		CopyInThis(size, number);
	}

	SMString SMString::AppendStr(int number)
	{
		SMString result;
		result.Append(number);

		return result;
	}

	void SMString::Append(int number, int digits)
	{
		int lenght = GetDigits(number);

		if (lenght < digits)
		{
			for (int i = 0; i < (digits - lenght); ++i)
			{
		    	Append(0);
			}

			Append(number);
		}
		else
			Append(number);
	}

	SMString SMString::AppendStr(int number, int digits)
	{
		SMString result;
		result.Append(number, digits);

		return result;
	}
};};
