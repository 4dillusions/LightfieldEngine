/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\Collections\LFList.h"

namespace LFCore { namespace Common
{
	//The Event won't delete receiver object
	template <typename TReceiver, typename TArgs> class LFEventArgs
	{
	private:
		LFCore::Collections::LFList<TReceiver *> receiverList;
		void (TReceiver::*receiverFunctionWithArgs)(const TArgs &args);

	public:
		LFEventArgs(void (TReceiver::*receiverFunctionWithArgs)(const TArgs &args)) : receiverList(false), receiverFunctionWithArgs(receiverFunctionWithArgs)
		{ }

		void operator += (TReceiver *receiver)
		{
			receiverList.Add(receiver);
		}

		void operator -= (TReceiver *receiver)
		{
			for (receiverList.First(); receiverList.IsDone(); receiverList.Next())
				if (receiverList.Current() == receiver)
					receiverList.RemoveCurrent();
		}

		void operator () (const TArgs &args)
		{
			for (receiverList.First(); receiverList.IsDone(); receiverList.Next())
				(receiverList.Current()->*receiverFunctionWithArgs)(args);
		}
	};
}}
