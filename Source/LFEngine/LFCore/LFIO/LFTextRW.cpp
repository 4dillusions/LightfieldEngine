/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include <fstream>
#include <string>

#include "LFTextRW.h"
#include "LFLogger.h"
#include "..\LFCommon\LFString.h"
#include "..\LFPatterns\LFIoc.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFIO
{
	LFString LFTextRW::Read(const LFString &pathAndName) const
	{
		LFString result;

		std::ifstream stream(pathAndName.ToChar(), std::ios::in);
		if (stream.is_open())
		{
			std::string line;
			while (getline(stream, line))
				result += LFString(line.c_str()) + "\n";

			stream.close();
		}
		else
		{
			LFString log = LFString("couldn't open: ");
			log += pathAndName;

			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, log);

			return LFString();
		}

		return result;
	}
}}}}
