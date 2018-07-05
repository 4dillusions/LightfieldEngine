/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "..//..//..//Source//Depencies//Glfw//SDK//lib-msvc110//glfw3dll.lib")
#pragma comment (lib, "..//..//..//Source//Depencies//Glfw//SDK//lib-msvc110//glfw3.lib")
#pragma comment (lib, "..//..//..//Source//Depencies//D3D9//Lib//d3dx9.lib")
#pragma comment (lib, "..//..//..//Source//Depencies//Audiere//lib//audiere.lib")

#if DEBUG
#pragma comment (lib, "..//Debug//LFCore.lib")
#pragma comment (lib, "..//Debug//Lua.lib")
#pragma comment (lib, "..//Debug//soil.lib")
#else
#pragma comment (lib, "..//Release//LFCore.lib")
#pragma comment (lib, "..//Release//Lua.lib")
#pragma comment (lib, "..//Release//soil.lib")
#endif

#endif