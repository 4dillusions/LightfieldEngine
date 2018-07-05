/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFFile.h"
#include "..\LFCommon\LFString.h"
#include "..\LFPatterns\LFIoc.h"
#include "..\LFCommon\LFVFSManager.h"

#include <stdio.h>
#include <sys\stat.h>

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFIO 
{
    bool LFFile::IsFileExist(LFVFSPath path, const char *fileName)
    {
        LFString fileFullName;
        if (path != LFVFSPath::No)
            fileFullName += LFIoc<LFVFSManager *>::Get()->GetPath(path);

        fileFullName += fileName;

        static struct stat buffer;
        return (stat(fileFullName.ToChar(), &buffer) == 0);
    }

    bool LFFile::Delete(LFVFSPath path, const char *fileName)
    {
        LFString fileFullName;
        if (path != LFVFSPath::No)
            fileFullName += LFIoc<LFVFSManager *>::Get()->GetPath(path);

        fileFullName += fileName;

        return remove(fileFullName.ToChar()) == 0;
    }
}}}}
