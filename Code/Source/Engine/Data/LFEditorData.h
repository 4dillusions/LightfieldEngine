/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LFEngine { namespace Data 
{
	struct EditorData
	{
		unsigned char levelSizeX; //all level width size
		unsigned char levelSizeY; //all level height size
		unsigned char tilesId; //which tile texture pack is
		unsigned char zoom; //level matrix zoom value
	};
}}
