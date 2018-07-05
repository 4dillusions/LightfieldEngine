/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCore.h"

#define LFSTRINGIFY(x) #x
#define LFTOSTRING(x) LFSTRINGIFY(x)
#define AT "[!!Leak!!] "  __FILE__ ":" LFTOSTRING(__LINE__)

#include <iostream>

namespace LFCore { namespace Common
{
	/*
	Avoid memory leaks with LFNew/LFDelete instead of new/delete operators
	*/
	class LFCORE_LIBRARY LFMemoryManager
	{
	private:
		static LFMemoryManager instance;

	public:
		static LFMemoryManager &Instance() { return instance; }

		void Add(int address, const char *info);
		void Remove(int address);
		int MemoryLeakCount();
		void CheckMemoryLeaks();
	};
	
	template <typename T, typename A> T *LFNew(A at)
	{
		T *result;
		result = new T;

		#if defined(DEBUG)
			LFMemoryManager::Instance().Add(reinterpret_cast<unsigned int>(result), at);
		#endif

		return result;
	}

	template <typename T, typename A, typename P1> T *LFNew(A at, P1 p1)
	{
		T *result;
		result = new T(p1);

		#if defined(DEBUG)
			LFMemoryManager::Instance().Add(reinterpret_cast<unsigned int>(result), at);
		#endif

		return result;
	}

	template <typename T, typename A, typename P1, typename P2> T *LFNew(A at, P1 p1, P2 p2)
	{
		T *result;
		result = new T(p1, p2);

		#if defined(DEBUG)
			LFMemoryManager::Instance().Add(reinterpret_cast<unsigned int>(result), at);
		#endif

		return result;
	}

	template <typename T, typename A, typename P1, typename P2, typename P3> T *LFNew(A at, P1 p1, P2 p2, P3 p3)
	{
		T *result;
		result = new T(p1, p2, p3);

		#if defined(DEBUG)
			LFMemoryManager::Instance().Add(reinterpret_cast<unsigned int>(result), at);
		#endif

		return result;
	}

	template <typename T, typename A, typename P1, typename P2, typename P3, typename P4> T *LFNew(A at, P1 p1, P2 p2, P3 p3, P4 p4)
	{
		T *result;
		result = new T(p1, p2, p3, p4);

		#if defined(DEBUG)
			LFMemoryManager::Instance().Add(reinterpret_cast<unsigned int>(result), at);
		#endif

		return result;
	}

	template <typename T, typename A, typename P1, typename P2, typename P3, typename P4, typename P5> T *LFNew(A at, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
	{
		T *result;
		result = new T(p1, p2, p3, p4, p5);

		#if defined(DEBUG)
			LFMemoryManager::Instance().Add(reinterpret_cast<unsigned int>(result), at);
		#endif

		return result;
	}

	template <typename T, typename A, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6> T *LFNew(A at, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
	{
		T *result;
		result = new T(p1, p2, p3, p4, p5, p6);

		#if defined(DEBUG)
			LFMemoryManager::Instance().Add(reinterpret_cast<unsigned int>(result), at);
		#endif

		return result;
	}

	template <typename T> void LFDelete(T &obj)
	{
		#if defined(DEBUG)
			LFMemoryManager::Instance().Remove(reinterpret_cast<unsigned int>(obj));
		#endif

		delete obj;
		obj = nullptr;
	}

	template <typename T, typename A> T *LFNewArray(A at, int size)
	{
		T *result;
		result = new T[size];

		#if defined(DEBUG)
			LFMemoryManager::Instance().Add(reinterpret_cast<unsigned int>(result), at);
		#endif

		return result;
	}

	template <typename T> void LFDeleteArray(T &obj)
	{
		#if defined(DEBUG)
			LFMemoryManager::Instance().Remove(reinterpret_cast<unsigned int>(obj));
		#endif

		delete []obj;
		obj = nullptr;
	}

	template <typename T, typename A> T **LFNewMatrix(A at, int sizeX, int sizeY)
	{
		T **result;

		result = new T *[sizeX];

		for (int x = 0; x < sizeX; ++x)
			result[x] = new T[sizeY];

		#if defined(DEBUG)
			LFMemoryManager::Instance().Add(reinterpret_cast<unsigned int>(result), at);
		#endif

		return result;
	}

	template <typename T> void LFDeleteMatrix(T &obj, int sizeX, int sizeY)
	{
		#if defined(DEBUG)
			LFMemoryManager::Instance().Remove(reinterpret_cast<unsigned int>(obj));
		#endif

		for (int x = 0; x < sizeX; ++x)
			delete []obj[x];

		delete []obj;

		obj = nullptr;
	}
}}
