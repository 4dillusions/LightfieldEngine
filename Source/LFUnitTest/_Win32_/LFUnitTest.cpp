/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC

#if DEBUG
#pragma comment (lib, "..//Bin//Debug//Win32//Lib//ThirdParty//Audiere//audiere.lib")
#pragma comment (lib, "..//Bin//Debug//Win32//Lib//ThirdParty//cURL//libcurl_debug.lib")
#pragma comment (lib, "..//Bin//Debug//Win32//Lib//ThirdParty//D3D9//d3d9.lib")
#pragma comment (lib, "..//Bin//Debug//Win32//Lib//ThirdParty//D3D9//d3dx9d.lib")
#pragma comment (lib, "..//Bin//Release//Win32//Lib//ThirdParty//GLEW//glew32.lib")
#pragma comment (lib, "..//Bin//Release//Win32//Lib//ThirdParty//GLFW//glfw3.lib")
#pragma comment (lib, "..//Bin//Release//Win32//Lib//ThirdParty//GLFW//glfw3dll.lib")

#pragma comment (lib, "opengl32.lib")
#else
#pragma comment (lib, "..//Bin//Release//Win32//Lib//ThirdParty//Audiere//audiere.lib")
#pragma comment (lib, "..//Bin//Release//Win32//Lib//ThirdParty//cURL//libcurl.lib")
#pragma comment (lib, "..//Bin//Release//Win32//Lib//ThirdParty//D3D9//d3d9.lib")
#pragma comment (lib, "..//Bin//Release//Win32//Lib//ThirdParty//D3D9//d3dx9.lib")
#pragma comment (lib, "..//Bin//Release//Win32//Lib//ThirdParty//GLEW//glew32.lib")
#pragma comment (lib, "..//Bin//Release//Win32//Lib//ThirdParty//GLFW//glfw3.lib")
#pragma comment (lib, "..//Bin//Release//Win32//Lib//ThirdParty//GLFW//glfw3dll.lib")

#pragma comment (lib, "opengl32.lib")
#endif

#endif
