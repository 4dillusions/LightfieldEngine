/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#if DEBUG
#pragma comment (lib, "..//Debug//LFCore.lib")
#pragma comment (lib, "..//Debug//LFEngine.lib")
#else
#pragma comment (lib, "..//Release//LFCore.lib")
#pragma comment (lib, "..//Release//LFEngine.lib")
#endif

#endif