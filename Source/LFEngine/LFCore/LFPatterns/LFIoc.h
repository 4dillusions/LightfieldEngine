/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include <functional>
#include "..\LFCommon\LFMemoryManager.h"
#include "..\..\..\LFEngine\LFCore\LFCore.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFPatterns
{
	/**
		@brief
		Static IOC for Logging etc. <br>
		Ioc implements prototype, factory and singleton patterns together, called Inversion Of Control and Dependency Injection pattern (DI) <br>
		This Ioc supports one instance -> one prototype implementation <br>
	*/
	template <typename TInstance> class LFIoc final
	{
	public:
		LFIoc() = delete;
		LFIoc(const LFIoc &) = delete;
		LFIoc(LFIoc &&) = delete;
		LFIoc &operator=(const LFIoc &) = delete;
		LFIoc &operator=(LFIoc &&) = delete;
		~LFIoc() = delete;

		static TInstance &Get()
		{
			static TInstance instance;

			return instance;
		}
	};

	/**
		@brief
		Dynamic IOC for subsystems and other dynamic main objects <br>
		Ioc implements prototype, factory and singleton patterns together, called Inversion Of Control and Dependency Injection pattern (DI) <br>
		This Ioc supports one instance -> one prototype implementation <br>
	*/
	template <typename TInstance> class LFIoc<TInstance *> final
	{
		static TInstance *instance;
		static std::function<TInstance *()> prototype;

	public:
		LFIoc() = delete;
		LFIoc(const LFIoc &) = delete;
		LFIoc(LFIoc &&) = delete;
		LFIoc &operator=(const LFIoc &) = delete;
		LFIoc &operator=(LFIoc &&) = delete;

		template <typename TType> static void Register()
		{
			if (prototype == nullptr && instance == nullptr)
				prototype = []() { return LFCommon::LFMemoryManager::New<TType>(INFO); };
		}

		template <typename TType> static void Register(const std::function<TInstance *()> &prototype)
		{
			if (prototype != nullptr && LFIoc<TInstance *>::prototype == nullptr && instance == nullptr)
				LFIoc<TInstance *>::prototype = prototype;
		}

		static void Create()
		{
			if (prototype != nullptr && instance == nullptr)
				instance = prototype();
		}

		static void Release()
		{
			LFCommon::LFMemoryManager::Delete(instance);
			prototype = nullptr;
		}

		static TInstance *Get()
		{
			return instance;
		}

		static bool IsExist()
		{
			return instance != nullptr;
		}
	};

	template <typename TInstance> TInstance *LFIoc<TInstance *>::instance = nullptr;
	template <typename TInstance> std::function<TInstance *()> LFIoc<TInstance *>::prototype = nullptr;
}}}}
