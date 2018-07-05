/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LF2DObject.h"
#include "..\Input\LFInputSystem.h"
#include "..\Script\LFLuaType.h"

namespace LFEngine { namespace Graphics { namespace LF2D
{
	class LFSprite;
}}}

namespace LFEngine { namespace GameEngine
{
	class LFLayer;

	class LFENGINE_LIBRARY LFMaterial
	{
	public:
		const char *textureName;
		int textureWidth;
		int textureHeight;
		int atlasWidth;
		int atlasHeight;
	};

	class LFENGINE_LIBRARY LFFontMaterial : public LFMaterial
	{
	public:
		const char *alphabet;
		int alphabetSize;
		LFCore::Math::LFVector2D alphabetData[128];

		LFCore::Math::LFVector2D GetAtlasPos(char character) { return alphabetData[(int)character]; }
	};

	class LFENGINE_LIBRARY LFControlMaterial : public LFMaterial
	{
	public:
		LFCore::Math::LFRectangle atlasPosSize;
	};

	template <typename T> class LFENGINE_LIBRARY LFObserverEventArgs
	{
	public:
		T subject;
	};

	class LFENGINE_LIBRARY LFControl : public LF2DObject, 
		public LFEngine::Input::LFIPointerPressReleaseEventHandler,
		public LFEngine::Input::LFIPointerMoveEventHandler
	{
	protected:
		LFEngine::Script::LFLuaType controlType;
		LFCore::Math::LFRectangle posSize;
		bool isPressable, isPressMovable;
		enum SpriteItemsStorage { SIS_NONE, SIS_NONTOUCHED, SIS_TOUCHED, SIS_NONTOUCHED_UNCHECKED, SIS_TOUCHED_UNCHECKED };
		LFCore::Collections::LFList<LFEngine::Graphics::LF2D::LFSprite *> nonTouchedSpriteItems /*checked*/, touchedSpriteItems /*checked*/, nonTouchedUncheckedSpriteItems, touchedUncheckedSpriteItems; //for visible and pressing events
		
		void SetSpriteItems(bool isNonTouchedSpritesVisible, bool isTouchedSpritesVisible);
		void SetSpriteItems(bool isNonTouchedSpritesVisible, bool isTouchedSpritesVisible, bool isCheckedSpritesVisible);
		void SetSpriteChildrenPosition(const LFCore::Math::LFVector2D &position);

	public:
		static LFControl *lastTouchedControl;
		static LFControl *touchingControl;

		LFControl(const LFCore::Common::LFString &name, const LFCore::Math::LFRectangle &posSize = LFCore::Math::LFRectangle(), bool isChildrenDestructDelete = true, bool isPressMovable = false);
		virtual ~LFControl();

		void AttachSpriteChildren(const char *spriteName, LFLayer *layer, const LFCore::Common::LFString &textureAtlasName, const LFCore::Math::LFRectangle &posSize,
			const LFCore::Math::LFRectangle &atlasPosSize, const LFCore::Math::LFVector2D &spritesSize, const SpriteItemsStorage &spriteItemsStorage = LFControl::SIS_NONE);

		void PosSize(const LFCore::Math::LFRectangle &posSize) { this->posSize = posSize; }
		LFCore::Math::LFRectangle PosSize() { return posSize; }

		//LFIPointerPressReleaseEventHandler
		virtual void OnPointerPressRelease(const LFEngine::Input::LFPointerEventArgs &args);

		//LFIPointerMoveEventHandler
		virtual void OnPointerMove(const LFEngine::Input::LFPointerMoveEventArgs &args);

		//abstractions
		virtual void AttachChildren(LFLayer *layer) = 0; //attach children to components and layer

		virtual void OnControlPress(const LFEngine::Input::LFPointerEventArgs &args) = 0;
		virtual void OnControlRelease(const LFEngine::Input::LFPointerEventArgs &args) = 0;
		virtual void OnControlPressed(const LFEngine::Input::LFPointerEventArgs &args) = 0; //pressed and released on the control
		virtual void OnMouseMove(const LFEngine::Input::LFPointerMoveEventArgs &args) = 0; //move cursor on press control

		//LFGameCompositComponent
		virtual void IsAlive(bool isAlive);
	};
}}
