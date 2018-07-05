/*
Copyright (c) 2013 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#pragma warning(disable: 4251) //Disable annoying visual studio warning: "<type> needs to have dll-interface to be used by clients"
	
	/*
	Error	4	error C4996: 'localtime': This function or variable may be unsafe. Consider using localtime_s instead. 
	To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.	
	D:\Robi\Gamedev\Projects\GameEngine\Lightfield2\Code\Source\Core\Common\LFSystemInfo.cpp	129	1	LFCore
	*/
	#define _CRT_SECURE_NO_WARNINGS 
	
	#include <Windows.h>
	#include <sstream>
#endif

#ifndef CPP0X
	#define nullptr 0
#endif