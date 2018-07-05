/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC

#include "LFRenderSystemD3D9.h"
#include "LFShaderEffectBasicD3D9.h"
#include "LFShaderEffectNormalD3D9.h"
#include "..\LFRenderWindowWin32.h"
#include "..\..\LFRenderComponentList.h"
#include "..\..\LFShaderEffect.h"
#include "..\..\LFVertexTextureData.h"
#include "..\..\..\LFCore\LFCommon\LFSystemData.h"
#include "..\..\..\LFCore\LFMath\LFRectangle.h"
#include "..\..\..\..\LFEngine\LFCore\LFIO\LFLogger.h"
#include "..\..\..\..\LFEngine\LFCore\LFPatterns\LFIoc.h"

using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFCore::LFMath;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;

namespace LF3Engine { namespace LFEngine { namespace LFRender { namespace LFD3D9
{
	LFRenderSystemD3D9::LFRenderSystemD3D9()
	{
		LFIoc<LFLogger>::Get().WriteOutput("Create RenderSystem D3D9");

		d3dBackgroundColor = D3DCOLOR_XRGB(static_cast<unsigned char>(backgroundColor.r), static_cast<unsigned char>(backgroundColor.g), static_cast<unsigned char>(backgroundColor.b));
	}

	LFRenderSystemD3D9::~LFRenderSystemD3D9()
	{
		LFIoc<LFLogger>::Get().WriteOutput("Release RenderSystem D3D9");

		if (d3d9Device != nullptr)
		{
			d3d9Device->Release();
			d3d9Device = nullptr;
		}

		if (d3d9 != nullptr)
		{
			d3d9->Release();
			d3d9 = nullptr;
		}
	}

	void LFRenderSystemD3D9::Init()
	{
		LFIoc<LFLogger>::Get().WriteOutput("Initialize RenderSystem D3D9");

		d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
		D3DDISPLAYMODE display;
		D3DPRESENT_PARAMETERS d3dParameters;

		ZeroMemory(&d3dParameters, sizeof(d3dParameters));
		d3d9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &display);

		d3dParameters.Windowed = true;
		d3dParameters.BackBufferFormat = display.Format;
		d3dParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dParameters.EnableAutoDepthStencil = true;
		d3dParameters.AutoDepthStencilFormat = D3DFMT_D16;

		d3dParameters.PresentationInterval = LFSystemData::LFIsVsync ? D3DPRESENT_INTERVAL_DEFAULT : D3DPRESENT_INTERVAL_IMMEDIATE;

		d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, dynamic_cast<LFRenderWindowWin32 *>(LFIoc<LFRenderWindow *>::Get())->GetHwnd(), 
			D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dParameters, &d3d9Device);

		d3d9Device->SetRenderState(D3DRS_LIGHTING, 0);
		d3d9Device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE); //Z buffer
		d3d9Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		d3d9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		d3d9Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		d3d9Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		d3d9Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		d3d9Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		d3d9Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
		d3d9Device->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 0);
		d3d9Device->SetSamplerState(0, D3DSAMP_MAXMIPLEVEL, 0);

		d3d9Device->SetFVF(LFFVF);

		static D3DADAPTER_IDENTIFIER9 adapter; //adapter.Description is a char array
		D3DCAPS9 caps;
		//auto numAdapters = d3d9->GetAdapterCount();
		d3d9->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &adapter);
		d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
		LFSystemData::SetGPUName(adapter.Description, "");
		LFSystemData::SetMaxTextureSize(caps.MaxTextureHeight);
	}

	void LFRenderSystemD3D9::BeginScene()
	{
		d3d9Device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, d3dBackgroundColor, 1.0f, 0);
		d3d9Device->BeginScene();
	}

	void LFRenderSystemD3D9::EndScene()
	{
		d3d9Device->EndScene();
		d3d9Device->Present(nullptr, nullptr, nullptr, nullptr);
	}

	void LFRenderSystemD3D9::OffsetRelativePosition(LFRectangle &posVertexSize)
	{
		float posX = posVertexSize.position.x == 0 ? 0 : (posVertexSize.position.x * LFSystemData::GetWindowWidthRelativeScale() * 2) / LFSystemData::GetWindowWidth();
		posVertexSize.position.x = -1;
		posVertexSize.position.x += posVertexSize.width;
		posVertexSize.position.x += posX;

		float posY = posVertexSize.position.y == 0 ? 0 : (posVertexSize.position.y * LFSystemData::GetWindowHeightRelativeScale() * 2) / LFSystemData::GetWindowHeight();
		posVertexSize.position.y = 1;
		posVertexSize.position.y -= posVertexSize.height;
		posVertexSize.position.y -= posY;
	}

	void LFRenderSystemD3D9::Draw2DObject(int startVertex)
	{
		d3d9Device->DrawPrimitive(D3DPT_TRIANGLELIST, startVertex, 2); //type, start vertex, primitive count
	}

	LFShaderEffect *LFRenderSystemD3D9::CreateShaderEffect(bool isBasic, const LFString &textureName, const LFVector2D &vertexSize, const LFVector2D &atlasSize)
	{
		LFShaderEffect *result;

		LFString shaderName = isBasic ? LFString(LFSystemData::LFShaderEffectBasicD3D9Name) : LFString(LFSystemData::LFShaderEffectNormalD3D9Name);
		if (auto shader = LFIoc<LFRenderComponentList *>::Get()->
			GetItem(LFShaderEffect::GenerateKeyName(shaderName, textureName, LFVertexTextureData::GenerateName(vertexSize, atlasSize))))
		{
			result = dynamic_cast<LFShaderEffectD3D9 *>(shader);
		}
		else
		{
			if (isBasic)
				result = LFMemoryManager::New<LFShaderEffectBasicD3D9>(INFO, d3d9Device, textureName, vertexSize, atlasSize);
			else
				result = LFMemoryManager::New<LFShaderEffectNormalD3D9>(INFO, d3d9Device, textureName, vertexSize, atlasSize);

			result->Create();
		}

		return result;
	}
}}}}

#endif
