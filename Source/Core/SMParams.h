#pragma once

#include <vector>
#include <stdio.h>
#include <stdarg.h>

namespace SMEngine { namespace Core
{
	/*
	Függvény paraméter lista.

	Használat:
	void Write(SMParams<const char *> params)
	{
		for (int i = 0; i < params.Lenght(); ++i)
			SMLogger::Instance()->WriteOutput(params[i]);
	}
	...
	Write(SMParams<const char *>("ho", "hahah", "hehehhhh", nullptr));
	*/
	template <typename T> class SMParams
	{
	private:
		std::vector<T> data;

	public:
		SMParams(T param, ...)
		{
			va_list va;
			va_start(va, param);

			data.push_back(param);

			while (T arg = va_arg(va, T))
				data.push_back(arg);

			va_end(va);
		}

		int Lenght() const
		{
			return data.size();
		}

		T operator[] (int index) const //int a = params[i];
		{
			return data[index];
		}
	};
};};
