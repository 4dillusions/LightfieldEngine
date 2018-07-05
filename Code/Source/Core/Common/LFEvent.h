/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\Collections\LFList.h"

namespace LFCore { namespace Common
{
	//The Event won't delete receiver object
	template <typename TReceiver> class LFEvent
	{
	private:
		LFCore::Collections::LFList<TReceiver *> receiverList;
		void (TReceiver::*receiverFunction)();

	public:
		explicit LFEvent(void (TReceiver::*receiverFunction)()) : receiverList(false), receiverFunction(receiverFunction)
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

		void operator () ()
		{
			for (receiverList.First(); receiverList.IsDone(); receiverList.Next())
				(receiverList.Current()->*receiverFunction)();
		}
	};
}}
