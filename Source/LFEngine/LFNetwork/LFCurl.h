/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCore\LFCommon\LFString.h"

namespace LF3Engine { namespace LFEngine { namespace LFNetwork
{
	/**
		@brief
		Curl wrapper for communication between client and PHP server with JSON
	*/
	class LFCurl final
	{
		static char *response;

		LFCurl() = delete;
		LFCurl(const LFCurl&) = delete;
		LFCurl(LFCurl &&) = delete;
		LFCurl &operator=(const LFCurl &) = delete;
		LFCurl &operator=(LFCurl &&) = delete;
		~LFCurl() = delete;

		static size_t OnResponse(void *ptr, size_t size, size_t nmemb, void *stream);
		
	public:
		static LFCore::LFCommon::LFString GetResponse(const char *serverURL, const LFCore::LFCommon::LFString &jsonRequest);
	};
}}}
