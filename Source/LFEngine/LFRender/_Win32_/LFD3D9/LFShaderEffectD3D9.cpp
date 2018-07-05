/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC

#include "LFShaderEffectD3D9.h"
#include "LFVertexTextureDataD3D9.h"
#include "LFTextureD3D9.h"
#include "..\..\LFRenderComponentList.h"
#include "..\..\LFVertexTextureData.h"
#include "..\..\..\LFCore\LFIO\LFLogger.h"
#include "..\..\..\LFCore\LFPatterns\LFIoc.h"
#include "..\..\..\LFCore\LFCommon\LFVFSManager.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFMath;

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFD3D9
{
	LFShaderEffectD3D9::LFShaderEffectD3D9(LPDIRECT3DDEVICE9 d3d9Device, const LFString &effectName, 
		const LFString &textureName, const LFVector2D &vertexSize, const LFVector2D &atlasSize)
			: LFShaderEffect(effectName, textureName, vertexSize, atlasSize), d3d9Device(d3d9Device)
	{ }

	bool LFShaderEffectD3D9::Create()
	{
		//initShape: create vertexData, create/load Texture
		if (LFVertexTextureData *vtData = dynamic_cast<LFVertexTextureData *>(LFIoc<LFRenderComponentList *>::Get()->
			GetItem(LFVertexTextureData::GenerateName(vertexSize, atlasSize))))
		{
			vertexTextureData = vtData;
		}
		else
		{
			vertexTextureData = LFMemoryManager::New<LFVertexTextureDataD3D9>(INFO, d3d9Device, vertexSize, atlasSize);
			vertexTextureData->Create();
		}
		vertexTextureDataName = vertexTextureData->GetName();
		
		if (LFTexture *tData = dynamic_cast<LFTexture *>(LFIoc<LFRenderComponentList *>::Get()->GetItem(LFTexture::CreateName(textureName))))
		{
			texture = tData;
		}
		else
		{
			texture = LFMemoryManager::New<LFTextureD3D9>(INFO, d3d9Device, textureName);
			texture->Create();
		}

		//init shader
		LFString effectFullName(vfsManager->GetPath(LFVFSPath::ShaderEffect));
		effectFullName += name + ".fx";

		ID3DXBuffer *errorBufferPtr = nullptr;
		
		int error = D3DXCreateEffectFromFile(d3d9Device, effectFullName.ToLpctstr(), nullptr, nullptr, 0, nullptr, &effect, &errorBufferPtr);

		LFString log("Create new effect ");
		log += GetKeyName() + " - ";

		if (errorBufferPtr)
		{
			log += static_cast<char *>(errorBufferPtr->GetBufferPointer());
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, log);

			return false;
		}
		
		if (error == 0)
		{
			log += "shader effect compiled";
			LFIoc<LFLogger>::Get().WriteOutput(log);
		}
		else
		{
			log += "error: " + error;
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, log);

			return false;
		}

		technique = effect->GetTechniqueByName(name.ToChar());
		gWorldViewProjection = effect->GetParameterByName(nullptr, "gWorldViewProjection");
		hTexture = effect->GetParameterByName(nullptr, "tex");
		hColor = effect->GetParameterByName(nullptr, "customColor");

		if (auto tex = dynamic_cast<LFTextureD3D9 *>(texture))
			textureD3D9 = tex->GetTexture();
		else
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, LFString("Null Texture! LFShaderEffectD3D9::Create "));

		effect->SetTexture(hTexture, textureD3D9);
		effect->SetTechnique(technique);

		return true;
	}

	void LFShaderEffectD3D9::BeginRender()
	{
		vertexTextureData->BeginRender();

		effect->SetTechnique(technique);
		effect->Begin(nullptr, 0);
	}

	void LFShaderEffectD3D9::Draw()
	{
		D3DXMatrixTranslation(&projection, relativePosition.x, relativePosition.y, 0.0f); //identity + translation
		effect->SetMatrix(gWorldViewProjection, &projection);

		d3dColor.x = color.r;
		d3dColor.y = color.g;
		d3dColor.z = color.b;
		d3dColor.w = color.a;
		effect->SetVector(hColor, &d3dColor);

		effect->BeginPass(0);
		effect->EndPass();
	}

	void LFShaderEffectD3D9::EndRender()
	{
		effect->End();
	}

	void LFShaderEffectD3D9::Release()
	{
		if (effect != nullptr)
		{
			effect->Release();
			effect = nullptr;
		}

		LFShaderEffect::Release();
	}
}}}}

#endif
