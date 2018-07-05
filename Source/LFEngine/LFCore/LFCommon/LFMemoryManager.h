/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include <unordered_map>

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon
{
	#define UNITTEST

	/**
	@brief
	Avoid memory leaks with New/Delete instead of new/delete naked operators
	*/
	class LFMemoryManager final
	{
		static std::unordered_map<int, const char *> memoryList;

		LFMemoryManager() = delete;
		LFMemoryManager(const LFMemoryManager&) = delete;
		LFMemoryManager(LFMemoryManager &&) = delete;
		LFMemoryManager &operator=(const LFMemoryManager &) = delete;
		LFMemoryManager &operator=(LFMemoryManager &&) = delete;
		~LFMemoryManager() = delete;

	public:
		static void Add(int address, const char *info);
		static void Remove(int address);
		static int GetMemoryLeakCount();
		static void WriteStatistics(bool isTest);

		template <typename T, typename TInfo> static T *New(TInfo info)
		{
			T *result;
			result = new T;

			#if defined(UNITTEST) || defined(DEBUG) || defined(_DEBUG)
				LFMemoryManager::Add(reinterpret_cast<unsigned int>(result), info);
			#endif

			return result;
		}

		template <typename T, typename TInfo, typename P1> static T *New(TInfo info, P1 p1)
		{
			T *result;
			result = new T(p1);

			#if defined(UNITTEST) || defined(DEBUG) || defined(_DEBUG)
				LFMemoryManager::Add(reinterpret_cast<unsigned int>(result), info);
			#endif

			return result;
		}

		template <typename T, typename TInfo, typename P1, typename P2> static T *New(TInfo info, P1 p1, P2 p2)
		{
			T *result;
			result = new T(p1, p2);

			#if defined(UNITTEST) || defined(DEBUG) || defined(_DEBUG)
				LFMemoryManager::Add(reinterpret_cast<unsigned int>(result), info);
			#endif

			return result;
		}

		template <typename T, typename TInfo, typename P1, typename P2, typename P3> static T *New(TInfo info, P1 p1, P2 p2, P3 p3)
		{
			T *result;
			result = new T(p1, p2, p3);

			#if defined(UNITTEST) || defined(DEBUG) || defined(_DEBUG)
				LFMemoryManager::Add(reinterpret_cast<unsigned int>(result), info);
			#endif

			return result;
		}

		template <typename T, typename TInfo, typename P1, typename P2, typename P3, typename P4> static T *New(TInfo info, P1 p1, P2 p2, P3 p3, P4 p4)
		{
			T *result;
			result = new T(p1, p2, p3, p4);

			#if defined(UNITTEST) || defined(DEBUG) || defined(_DEBUG)
				LFMemoryManager::Add(reinterpret_cast<unsigned int>(result), info);
			#endif

			return result;
		}

		template <typename T, typename TInfo, typename P1, typename P2, typename P3, typename P4, typename P5> static T *New(TInfo info, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
		{
			T *result;
			result = new T(p1, p2, p3, p4, p5);

			#if defined(UNITTEST) || defined(DEBUG) || defined(_DEBUG)
				LFMemoryManager::Add(reinterpret_cast<unsigned int>(result), info);
			#endif

			return result;
		}

		template <typename T, typename TInfo, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6> static T *New(TInfo info, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6)
		{
			T *result;
			result = new T(p1, p2, p3, p4, p5, p6);

			#if defined(UNITTEST) || defined(DEBUG) || defined(_DEBUG)
				LFMemoryManager::Add(reinterpret_cast<unsigned int>(result), info);
			#endif

			return result;
		}

		template <typename T> static void Delete(T &obj)
		{
			#if defined(UNITTEST) || defined(DEBUG) || defined(_DEBUG)
				Remove(reinterpret_cast<unsigned int>(obj));
			#endif

			delete obj;
			obj = nullptr;
		}

		template <typename T, typename TInfo> static T *NewArray(TInfo info, int size)
		{
			T *result;
			result = new T[size];

			#if defined(UNITTEST) || defined(DEBUG) || defined(_DEBUG)
				LFMemoryManager::Add(reinterpret_cast<unsigned int>(result), info);
			#endif

			return result;
		}

		template <typename T> static void DeleteArray(T &obj)
		{
			#if defined(UNITTEST) || defined(DEBUG) || defined(_DEBUG)
				Remove(reinterpret_cast<unsigned int>(obj));
			#endif

			delete[]obj;
			obj = nullptr;
		}

		template <typename T, typename TInfo> static T **NewMatrix(TInfo info, int sizeX, int sizeY)
		{
			T **result;

			result = new T *[sizeX];
			#if defined(UNITTEST) || defined(DEBUG) || defined(_DEBUG)
				LFMemoryManager::Add(reinterpret_cast<unsigned int>(result), info);
			#endif

			for (int x = 0; x < sizeX; ++x)
			{
				result[x] = new T[sizeY];

			#if defined(UNITTEST) || defined(DEBUG) || defined(_DEBUG)
				LFMemoryManager::Add(reinterpret_cast<unsigned int>(result[x]), info);
			#endif
			}

			return result;
		}

		template <typename T> static void DeleteMatrix(T &obj, int sizeX)
		{
			for (int x = 0; x < sizeX; ++x)
			{
				#if defined(UNITTEST) || defined(DEBUG) || defined(_DEBUG)
					Remove(reinterpret_cast<unsigned int>(obj[x]));
				#endif
				delete[]obj[x];
			}

			#if defined(UNITTEST) || defined(DEBUG) || defined(_DEBUG)
				Remove(reinterpret_cast<unsigned int>(obj));
			#endif
			delete[]obj;

			obj = nullptr;
		}

		template <typename T, typename TInfo> static T **NewPointerArray(TInfo info, int size)
		{
			T **result;

			result = new T *[size];
			#if defined(UNITTEST) || defined(DEBUG) || defined(_DEBUG)
				LFMemoryManager::Add(reinterpret_cast<unsigned int>(result), info);
			#endif

			return result;
		}

		template <typename T> static void DeletePointerArray(T &obj)
		{
			#if defined(UNITTEST) || defined(DEBUG) || defined(_DEBUG)
				Remove(reinterpret_cast<unsigned int>(obj));
			#endif
			delete[] obj;

			obj = nullptr;
		}
	};
}}}}
