/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFEngine { namespace LFData
{
	struct LFEditorData
	{
		unsigned char levelSizeX; //all level width size
		unsigned char levelSizeY; //all level height size
		unsigned char tilesId; //which tile texture pack is
		unsigned char zoom; //level matrix zoom value
	};
}}}
