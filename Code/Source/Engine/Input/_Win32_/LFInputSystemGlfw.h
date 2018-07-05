/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "..\LFInputSystem.h"

struct GLFWwindow;

namespace LFEngine { namespace Input
{
	/*
	Keyboard and mouse handling
	*/
	class LFENGINE_LIBRARY LFInputSystemGlfw : public LFInputSystem
	{ 
	public:
		LFInputSystemGlfw() { }
		LFInputSystemGlfw(GLFWwindow *window);
		virtual ~LFInputSystemGlfw() { }

		static void CreateInstance(GLFWwindow *window);
		static void ReleaseInstance();
	};
}}

#endif