/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFEngine { namespace LFData
{
	class LFControlData final
	{
	public:
		struct Coords
		{
			const int PosX;
			const int PosY;
			const int SizeX;
			const int SizeY;

			Coords(int posX, int posY, int sizeX, int sizeY) : PosX(posX), PosY(posY), SizeX(sizeX), SizeY(sizeY)
			{ }
		};

		LFControlData() = delete;
		LFControlData(const LFControlData&) = delete;
		LFControlData(LFControlData &&) = delete;
		LFControlData &operator=(const LFControlData &) = delete;
		LFControlData &operator=(LFControlData &&) = delete;
		~LFControlData() = delete;
		
		
	};
}}}
