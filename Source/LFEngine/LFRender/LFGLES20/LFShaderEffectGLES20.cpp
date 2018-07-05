/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC
#include "..\..\..\ThirdParty\_Win32_\GLEW\glew.h"
#endif

#include "LFShaderEffectGLES20.h"
#include "LFVertexTextureDataGLES20.h"
#include "LFTextureGLES20.h"
#include "..\LFTexture.h"
#include "..\LFRenderComponentList.h"
#include "..\LFVertexTextureData.h"
#include "..\..\LFCore\LFPatterns\LFIoc.h"
#include "..\..\LFCore\LFIO\LFTextRW.h"
#include "..\..\LFCore\LFIO\LFLogger.h"
#include "..\..\LFCore\LFCommon\LFVFSManager.h"

using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFMath;
using namespace LF3Engine::LFEngine::LFCore::LFIO;

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFGLES20
{
#ifdef WINCLASSIC
	LFShaderEffectGLES20::LFShaderEffectGLES20(const LFString &effectName, const LFString &textureName, const LFVector2D &vertexSize, const LFVector2D &atlasSize)
		: LFShaderEffect(effectName, textureName, vertexSize, atlasSize),
		glColor{}
	{ }
#endif

#ifdef TIZEN
	LFShaderEffectGLES20::LFShaderEffectGLES20(Evas_Object *glview, const LFString &effectName, 
		const LFString &textureName, const LFVector2D &vertexSize, const LFVector2D &atlasSize)
			: LFShaderEffect(effectName, textureName, vertexSize, atlasSize), 
			glview(glview), glColor{}
	{ }
#endif

	GLuint LFShaderEffectGLES20::LoadShaders(const LFString &vertexFilePath, const LFString &fragmentFilePath, Evas_Object *glview)
	{
#ifdef TIZEN
		ELEMENTARY_GLVIEW_USE(glview);
#endif

		GLint result = GL_FALSE;
		int infoLogLength;
		int errors = 0;
		LFTextRW textRW;

		LFString log("Create new effect ");
		log += GetKeyName() + " - ";

		//Create the shaders
		GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		//Read the Vertex Shader code from the file
		LFString vertexShaderCode = textRW.Read(vertexFilePath);

		//Read the Fragment Shader code from the file
		LFString fragmentShaderCode = textRW.Read(fragmentFilePath);

		//Compile Vertex Shader
		char const *vertexSourcePointer = vertexShaderCode.ToChar();
		glShaderSource(vertexShaderID, 1, &vertexSourcePointer, nullptr);
		glCompileShader(vertexShaderID);

		//Check Vertex Shader
		glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
		glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			errors++;

			std::vector<char> vertexShaderErrorMessage(infoLogLength + 1);
			glGetShaderInfoLog(vertexShaderID, infoLogLength, nullptr, &vertexShaderErrorMessage[0]);

			log += &vertexShaderErrorMessage[0];
			log += "vertex shader error: ";
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, log);
		}

		//Compile Fragment Shader
		char const *fragmentSourcePointer = fragmentShaderCode.ToChar();
		glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, nullptr);
		glCompileShader(fragmentShaderID);

		//Check Fragment Shader
		glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
		glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			errors++;

			std::vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
			glGetShaderInfoLog(fragmentShaderID, infoLogLength, nullptr, &fragmentShaderErrorMessage[0]);

			log += &fragmentShaderErrorMessage[0];
			log += "fragment shader error: ";
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, log);
		}

		//Link the program
		GLuint programID = glCreateProgram();
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);
		glLinkProgram(programID);

		// Check the program
		glGetProgramiv(programID, GL_LINK_STATUS, &result);
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			errors++;

			std::vector<char> programErrorMessage(infoLogLength + 1);
			glGetProgramInfoLog(programID, infoLogLength, nullptr, &programErrorMessage[0]);

			log += &programErrorMessage[0];
			log += "shader program error: ";
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, log);
		}

		glDetachShader(programID, vertexShaderID);
		glDetachShader(programID, fragmentShaderID);

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);

		//Info
		if (errors == 0)
		{
			log += "shader effect compiled";
			LFIoc<LFLogger>::Get().WriteOutput(log);
		}
		else
			return -1;

		return programID;
	}

	bool LFShaderEffectGLES20::Create()
	{
#ifdef TIZEN
		ELEMENTARY_GLVIEW_USE(glview);
#endif

		//initShape: create vertexData, create/load Texture
		if (LFVertexTextureData *vtData = dynamic_cast<LFVertexTextureData *>(LFIoc<LFRenderComponentList *>::Get()->
			GetItem(LFVertexTextureData::GenerateName(vertexSize, atlasSize))))
		{
			vertexTextureData = vtData;
		}
		else
		{
#ifdef WINCLASSIC
			vertexTextureData = LFMemoryManager::New<LFVertexTextureDataGLES20>(INFO, vertexSize, atlasSize);
#endif

#ifdef TIZEN
			vertexTextureData = LFMemoryManager::New<LFVertexTextureDataGLES20>(INFO, glview, vertexSize, atlasSize);
#endif

			vertexTextureData->Create();
		}
		vertexTextureDataName = vertexTextureData->GetName();

		if (LFTexture *tData = dynamic_cast<LFTexture *>(LFIoc<LFRenderComponentList *>::Get()->GetItem(LFTexture::CreateName(textureName))))
		{
			texture = tData;
		}
		else
		{
#ifdef WINCLASSIC
			texture = LFMemoryManager::New<LFTextureGLES20>(INFO, textureName);
#endif

#ifdef TIZEN
			texture = LFMemoryManager::New<LFTextureGLES20>(INFO, glview, textureName);
#endif

			texture->Create();
		}

		if (auto tex = dynamic_cast<LFTextureGLES20 *>(texture))
			textureIndex = tex->GetTextureIndex();
		else
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, LFString("Null Texture! LFShaderEffectGLES20::Create "));

		//init shader
		LFString effectPath(vfsManager->GetPath(LFVFSPath::ShaderEffect));
		LFString vertexShader = effectPath + name + ".vert";
		LFString fragmentShader = effectPath + name + ".frag";

#ifdef WINCLASSIC
		programID = LoadShaders(vertexShader, fragmentShader);
#endif

#ifdef TIZEN
		programID = LoadShaders(vertexShader, fragmentShader, glview);
#endif

		if (programID == -1)
			return false;

		posID = glGetAttribLocation(programID, "pos");
		uvID = glGetAttribLocation(programID, "vertexUV");
		worldID = glGetUniformLocation(programID, "gWorldViewProjection");
		
		glUseProgram(programID);

		textureID = glGetUniformLocation(programID, "tex");
		glUniform1i(textureID, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureIndex);

		colorID = glGetUniformLocation(programID, "customColor");

		glEnableVertexAttribArray(posID);
		glEnableVertexAttribArray(uvID);

		return true;
	}

	void LFShaderEffectGLES20::BeginRender()
	{
#ifdef TIZEN
		ELEMENTARY_GLVIEW_USE(glview);
#endif

		vertexTextureData->BeginRender();
		glVertexAttribPointer(posID, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		vertexTextureData->Draw();
		glVertexAttribPointer(uvID, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureIndex);

		glUseProgram(programID);
	}

	void LFShaderEffectGLES20::Draw()
	{
#ifdef TIZEN
		ELEMENTARY_GLVIEW_USE(glview);
#endif

		gWorldViewProjection.MakeTranslation(relativePosition); //identity + translation
		gWorldViewProjection = gWorldViewProjection.Transpose(); //Tricky glUniformMatrix4fv works only without transpose on mobile GPU
		glUniformMatrix4fv(worldID, 1, GL_FALSE, &gWorldViewProjection.m[0][0]);

		glColor[0] = color.r;
		glColor[1] = color.g;
		glColor[2] = color.b;
		glColor[3] = color.a;
		glUniform4fv(colorID, 1, &glColor[0]);
	}

	void LFShaderEffectGLES20::EndRender()
	{ }

	void LFShaderEffectGLES20::Release()
	{
#ifdef TIZEN
		ELEMENTARY_GLVIEW_USE(glview);
#endif

#ifdef WINCLASSIC
		glDeleteProgram(programID);
#endif

		LFShaderEffect::Release();
	}
}}}}
