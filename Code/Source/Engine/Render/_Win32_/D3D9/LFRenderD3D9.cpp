/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#include "LFRenderD3D9.h"
#include "..\..\..\..\..\Source\Depencies\D3D9\Include\d3dx9.h"
#include "LFVertexTextureDataD3D9.h"
#include "LFTextureD3D9.h"
#include "..\LFRenderWindowWin32.h"
#include "..\..\..\..\Core\\Math\LFVector2D.h"
#include "..\..\..\..\Core\\Math\LFMatrix4.h"
#include "..\..\..\..\Core\\Math\LFRectangle.h"
#include "..\..\..\..\Core\Common\LFMemoryManager.h"
#include "..\..\..\..\Engine\Common\LFSystemInfo.h"
#include "..\..\..\..\Core\\IO\LFLogger.h"

using namespace LFCore::Common;
using namespace LFCore::Math;
using namespace LFEngine::Common;
using namespace LFCore::IO;

namespace LFEngine { namespace Render { namespace D3D9
{
	LFRenderD3D9::LFRenderD3D9() : d3d9(nullptr), d3d9Device(nullptr)
	{  
		d3dBackgroundColor = D3DCOLOR_XRGB(backgroundColor.r, backgroundColor.g, backgroundColor.b);
	}

	LFRenderD3D9::~LFRenderD3D9()
	{ 
		d3d9Device->Release();
		d3d9->Release();
	}

	void LFRenderD3D9::CreateInstance()
	{
		if (instance == nullptr)
			instance = LFNew<LFRenderD3D9>(AT);
	}

	void LFRenderD3D9::ReleaseInstance()
	{
		if (instance != nullptr)
			LFDelete(instance);
	}

	void LFRenderD3D9::Init()
	{
		LFLogger::Instance().WriteOutput("Initialize D3D9 Render");

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

		if (LFSystemInfo::Vsync()) d3dParameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
		else d3dParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, ((LFRenderWindowWin32 *)LFRenderWindow::Instance())->Hwnd(), D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dParameters, &d3d9Device);
		
		d3d9Device->SetRenderState(D3DRS_LIGHTING, 0); 
		d3d9Device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		d3d9Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		d3d9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		d3d9Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		d3d9Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		d3d9Device->SetSamplerState(0, D3DSAMP_MINFILTER,  D3DTEXF_LINEAR);
		d3d9Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		d3d9Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
		d3d9Device->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 0);
		d3d9Device->SetSamplerState(0, D3DSAMP_MAXMIPLEVEL, 0);
		
		D3DXMATRIX projection;
		D3DXMatrixOrthoLH(&projection, (float)LFSystemInfo::WindowWidth(), (float)LFSystemInfo::WindowHeight(), 0.0f, 1.0f);
		d3d9Device->SetTransform(D3DTS_PROJECTION, &projection);

		d3d9Device->SetFVF(LFFVF);
	}

	void LFRenderD3D9::BeginScene()
	{
		d3d9Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, d3dBackgroundColor, 1.0f, 0);
		d3d9Device->BeginScene();
	}

	void LFRenderD3D9::EndScene()
	{
		d3d9Device->EndScene();
		d3d9Device->Present(0, 0, 0, 0);
	}

	LFVertexTextureData *LFRenderD3D9::CreateVertexTextureData(const LFVector2D &vertexSize, const LFVector2D &atlasSize)
	{
		if (LFVertexTextureData *result = dynamic_cast<LFVertexTextureDataD3D9 *>(LFVertexTextureData::Find(vertexSize, atlasSize)))
			return result;

		LFVertexTextureData *result = LFNew<LFVertexTextureDataD3D9>(AT, d3d9Device);
		result->CreateVertexTextureData(vertexSize, atlasSize);

		return result;
	}

	LFTexture *LFRenderD3D9::CreateTexture(const LFCore::Common::LFString &textureName)
	{
		if (LFTexture *result = dynamic_cast<LFTextureD3D9 *>(LFTexture::Find(textureName)))
			return result;

		LFTexture *result = LFNew<LFTextureD3D9>(AT, d3d9Device);
		result->CreateTexture(textureName);

		return result;
	}

	void LFRenderD3D9::OffsetRelativePosition(LFRectangle &posVertexSize)
	{
		posVertexSize.position.x -= ((LFSystemInfo::WindowWidth()  / 2.0f) - (posVertexSize.width / 2.0f));
		posVertexSize.position.y = -posVertexSize.position.y;
		posVertexSize.position.y += ((LFSystemInfo::WindowHeight() / 2.0f) - (posVertexSize.height / 2.0f));
	}

	void LFRenderD3D9::Draw2DObject(const LFVector2D &position, int startVertex)
	{
		static D3DXMATRIX translation;
		D3DXMatrixTranslation(&translation, position.x, position.y, 0);
		d3d9Device->SetTransform(D3DTS_WORLD, &translation);
		d3d9Device->DrawPrimitive(D3DPT_TRIANGLELIST, startVertex, 2);
	}
}}}

#endif
