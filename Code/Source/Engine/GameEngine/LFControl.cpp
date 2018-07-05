/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFControl.h"
#include "LFLayer.h"
#include "..\Script\Engine\Input\LFInputLua.h"
#include "..\Script\LFScriptSystem.h"
#include "..\Graphics\LF2D\LFSprite.h"
#include "..\..\Core\\IO\LFLogger.h"
#include "..\GameEngine\LFScreen.h"

using namespace LFEngine::Input;
using namespace LFCore::Common;
using namespace LFEngine::Script;
using namespace LFCore::Math;
using namespace LFEngine::Graphics::LF2D;
using namespace LFCore::Collections;

namespace LFEngine { namespace GameEngine
{
	LFControl *LFControl::lastTouchedControl = nullptr;
	LFControl *LFControl::touchingControl = nullptr;

	LFControl::LFControl(const LFString &name, const LFRectangle &posSize, bool isChildrenDestructDelete, bool isPressMovable) : LF2DObject(name, isChildrenDestructDelete),
		posSize(posSize), isPressable(posSize != LFRectangle()), isPressMovable(isPressMovable), nonTouchedSpriteItems(false), touchedSpriteItems(false), nonTouchedUncheckedSpriteItems(false), touchedUncheckedSpriteItems(false)
	{
		if (isPressable)
		{	
			LFInputSystem::Instance()->PointerPressReleaseEvent += this;

			if (isPressMovable)
				LFInputSystem::Instance()->PointerMoveEvent += this;
		}
	}

	LFControl::~LFControl()
	{ }

	void LFControl::SetSpriteItems(bool isNonTouchedSpritesVisible, bool isTouchedSpritesVisible)
	{
		for (nonTouchedSpriteItems.First(); nonTouchedSpriteItems.IsDone(); nonTouchedSpriteItems.Next())
			nonTouchedSpriteItems.Current()->SetIsVisible(isNonTouchedSpritesVisible);

		for (touchedSpriteItems.First(); touchedSpriteItems.IsDone(); touchedSpriteItems.Next())
			touchedSpriteItems.Current()->SetIsVisible(isTouchedSpritesVisible);
	}

	void LFControl::SetSpriteItems(bool isNonTouchedSpritesVisible, bool isTouchedSpritesVisible, bool isCheckedSpritesVisible)
	{
		if (isCheckedSpritesVisible)
		{
			for (nonTouchedSpriteItems.First(); nonTouchedSpriteItems.IsDone(); nonTouchedSpriteItems.Next())
				nonTouchedSpriteItems.Current()->SetIsVisible(isNonTouchedSpritesVisible);

			for (touchedSpriteItems.First(); touchedSpriteItems.IsDone(); touchedSpriteItems.Next())
				touchedSpriteItems.Current()->SetIsVisible(isTouchedSpritesVisible);

			for (nonTouchedUncheckedSpriteItems.First(); nonTouchedUncheckedSpriteItems.IsDone(); nonTouchedUncheckedSpriteItems.Next())
				nonTouchedUncheckedSpriteItems.Current()->SetIsVisible(false);

			for (touchedUncheckedSpriteItems.First(); touchedUncheckedSpriteItems.IsDone(); touchedUncheckedSpriteItems.Next())
				touchedUncheckedSpriteItems.Current()->SetIsVisible(false);
		}
		else
		{
			for (nonTouchedUncheckedSpriteItems.First(); nonTouchedUncheckedSpriteItems.IsDone(); nonTouchedUncheckedSpriteItems.Next())
				nonTouchedUncheckedSpriteItems.Current()->SetIsVisible(isNonTouchedSpritesVisible);

			for (touchedUncheckedSpriteItems.First(); touchedUncheckedSpriteItems.IsDone(); touchedUncheckedSpriteItems.Next())
				touchedUncheckedSpriteItems.Current()->SetIsVisible(isTouchedSpritesVisible);

			for (nonTouchedSpriteItems.First(); nonTouchedSpriteItems.IsDone(); nonTouchedSpriteItems.Next())
				nonTouchedSpriteItems.Current()->SetIsVisible(false);

			for (touchedSpriteItems.First(); touchedSpriteItems.IsDone(); touchedSpriteItems.Next())
				touchedSpriteItems.Current()->SetIsVisible(false);
		}
	}

	void LFControl::SetSpriteChildrenPosition(const LFVector2D &position)
	{
		for (nonTouchedSpriteItems.First(); nonTouchedSpriteItems.IsDone(); nonTouchedSpriteItems.Next())
			nonTouchedSpriteItems.Current()->PositionAbsolute(position);
		
		for (touchedSpriteItems.First(); touchedSpriteItems.IsDone(); touchedSpriteItems.Next())
			touchedSpriteItems.Current()->PositionAbsolute(position);

		for (nonTouchedUncheckedSpriteItems.First(); nonTouchedUncheckedSpriteItems.IsDone(); nonTouchedUncheckedSpriteItems.Next())
			nonTouchedUncheckedSpriteItems.Current()->PositionAbsolute(position);

		for (touchedUncheckedSpriteItems.First(); touchedUncheckedSpriteItems.IsDone(); touchedUncheckedSpriteItems.Next())
			touchedUncheckedSpriteItems.Current()->PositionAbsolute(position);
	}

	void LFControl::AttachSpriteChildren(const char *spriteName, LFLayer *layer, const LFString &textureAtlasName, const LFRectangle &posSize, const LFRectangle &atlasPosSize, 
		const LFVector2D &spritesSize, const SpriteItemsStorage &spriteItemsStorage)
	{
		int posX, posY, atlasPosX, atlasPosY;
		for (int x = 0, count = 0; x < spritesSize.x; x++)
			for (int y = 0; y < spritesSize.y; y++, count++)
			{
				LFString spriteGeneratedName;
				spriteGeneratedName += spriteName;
				spriteGeneratedName += "Sprite";
				spriteGeneratedName.Append(count);

				posX = posSize.position.x + (x * posSize.width);
				posY = posSize.position.y + (y * posSize.height);
				atlasPosX = atlasPosSize.position.x + x;
				atlasPosY = atlasPosSize.position.y + y;
				LFSprite *sprite = LFNew<LFSprite>(AT, spriteGeneratedName, textureAtlasName, LFRectangle(posX, posY, posSize.width, posSize.height),
					LFRectangle(atlasPosX, atlasPosY, atlasPosSize.width, atlasPosSize.height));
				componentList.Add(sprite); //for hierarchy
				layer->Add(sprite); //for render/update

				switch (spriteItemsStorage) //for visible and pressing events
				{
					case LFControl::SIS_NONTOUCHED: nonTouchedSpriteItems.Add(sprite); break;
					case LFControl::SIS_TOUCHED: touchedSpriteItems.Add(sprite); break;
					case LFControl::SIS_NONTOUCHED_UNCHECKED: nonTouchedUncheckedSpriteItems.Add(sprite); break;
					case LFControl::SIS_TOUCHED_UNCHECKED: touchedUncheckedSpriteItems.Add(sprite); break;
				}
			}
	}

	void LFControl::OnPointerPressRelease(const LFPointerEventArgs &args)
	{
		if (IsActive() && layer->Screen()->IsLastVisible(layer->GetName()))
		{
			static bool isContains;
			isContains = posSize.Contains(args.x, args.y);
			if (isVisible && args.touch == LFPointerEventArgs::TC_LEFT)
			{
				if (args.isPressed)
				{
					if (isContains)
					{
						auto n = this->name;
						OnControlPress(args);
						lastTouchedControl = this;
						touchingControl = this;
					}
				}
				else
				{
					if (lastTouchedControl == this)
					{
						OnControlRelease(args);

						if (isContains)
						{
							OnControlPressed(args);

							LFScriptSystem::Instance()->CallFunction(LFInputName, LFInputOnControlPressedName, controlType);
							lastTouchedControl = nullptr;
						}
					}

					touchingControl = nullptr;
				}
			}
		}
	}

	void LFControl::OnPointerMove(const LFPointerMoveEventArgs &args)
	{
		if (IsActive() && isVisible && touchingControl == this)
			OnMouseMove(args);
	}

	void LFControl::IsAlive(bool isAlive)
	{
		if (isPressable && !isAlive)
		{
			LFInputSystem::Instance()->PointerPressReleaseEvent -= this;

			if (isPressMovable)
				LFInputSystem::Instance()->PointerMoveEvent -= this;
		}

		LFGameCompositComponent::SetIsAlive(isAlive);
	}
}}
