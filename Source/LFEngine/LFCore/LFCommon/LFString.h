/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCollections\LFList.h"

#ifdef WINCLASSIC
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon
{
    /**
        @brief
        Basic string object for platform-independent fast using <br>
        note: <br>
            Clear and operator+= functions are realatively fast operations for string building
    */
    class LFString final
    {
        static const char NullCharacter = '\0';
        static const char FloatNumberSplit = '.';
        static const char SpaceCharacter = ' ';

        static const int MinDataSize = 512;
        static const int MaxNumberDigits = 10;
        static const int NumberToChar = 48;

        char *data = nullptr;

#ifdef WINCLASSIC
		wchar_t *winString = nullptr;
#endif

        int textLenght = 0;
        int dataSize = MinDataSize;
        int hashCode = 0;

    public:
        LFString();

        LFString(const LFString &value);
        LFString(const LFString &&value);

        explicit LFString(const char *text);
        explicit LFString(char letter);
        explicit LFString(int number);
        explicit LFString(float floatNumber);

        ~LFString();

        LFString &operator = (const LFString &value);
        LFString &operator = (LFString &&value);

        LFString &operator = (const char *text);
        LFString &operator = (char letter);
        LFString &operator = (int number);
        LFString &operator = (float floatNumber);

        LFString operator + (const LFString &value) const;
        LFString operator + (char letter) const;
        LFString operator + (const char *text) const;
        LFString operator + (int number) const;
        LFString operator + (float floatNumber) const;

        LFString &operator += (const LFString &value);
        LFString &operator += (const char *text);
        LFString &operator += (char letter);
        LFString &operator += (int number);
        LFString &operator += (float floatNumber);

        char operator [] (int index) const; //char c = text[0];
        char &operator [] (int index); //text[0] = 'A';

        bool operator < (const LFString &value) const;
        bool operator == (const LFString &value) const;
        bool operator != (const LFString &value) const;

        explicit operator int() const; //hash code

        const char *ToChar() const;
        std::wstring ToWString() const;
#ifdef WINCLASSIC
		LPCWSTR ToLpcwstr();
		LPCTSTR ToLpctstr();
#endif
        int ToInt() const;
        float ToFloat() const;

    private:
        void IncrementDataSize(int dataSize = 0);

    public:
        static int GetHashCode(const char *text, int lenght, int hashIndex);
        static int GetHashCode(const char letter, int hashIndex);
        static int GetNumberLength(int number);
        static int GetTextLength(const char *text);
        static bool IsAbcLetter(char letter);
        static bool IsNumberDigit(char num);
		static void CopyToArray(const char *text, char *textArray);

        int GetTextLength() const;
        int GetTextLenghtWithoutSpace() const;
        bool IsEmpty() const;
        int GetDataSize() const;
        int GetHashCode() const;

        bool IsExist(const LFString &text) const;
        bool IsExist(char letter) const;
        int GetExistCount(const LFString &text) const;
        int GetExistCount(char letter) const;
        bool IsStartsWith(const LFString &text) const;
        bool IsStartsWith(char letter) const;
        bool IsEndsWith(const LFString &text) const;
        bool IsEndsWith(char letter) const;

        void Replace(const LFString &oldText, const LFString &newText);
        void Replace(char oldLetter, char newLetter);
        void Replace(char letter, int index);
        void Replace(int number, int digits); //s.ReplaceToLcdNumber(3, 4) => 0003
        void Remove(int startIndex, int count);
        void Remove(const LFString &text);
        void Remove(char Letter);
        void Trim();
        void Clear();

        LFCollections::LFList<LFString> Split(char separator) const;
        LFCollections::LFList<LFString> Split(const LFString &text) const;
    };
}}}}
