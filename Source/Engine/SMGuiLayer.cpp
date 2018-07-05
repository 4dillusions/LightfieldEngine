#include "SMGuiLayer.h"
#include "..\\IO\\SMLogger.h"
#include "..\\Gui\\SMControl.h"

using namespace SMEngine::IO;
using namespace SMEngine::Gui;

namespace SMEngine { namespace Engine
{
    SMGuiLayer::SMGuiLayer(const SMString &name) : SMGameCompositComponent(name)
    { }

    SMGuiLayer::~SMGuiLayer()
    { }

    void SMGuiLayer::Add(SMGameComponent *gameComponent)
    {
		if (SMControl *control = dynamic_cast<SMControl *>(gameComponent))
		{
			//sprite-ok hozzáadása
			SMList<SMSprite *> spriteList;
			control->GetSprites(spriteList);

			for (spriteList.First(); spriteList.IsDone(); spriteList.Next())
			{
				SMSprite *sprite = spriteList.Current();

				SMString spriteGroupCode = sprite->GroupCode();
				SMSpriteGroup *spriteGroup = (SMSpriteGroup *)Find(spriteGroupCode); //A Layer SpriteGroup-okat tárol

				if (spriteGroup == nullptr)
				{
					spriteGroup = new SMSpriteGroup(spriteGroupCode);
					spriteGroup->Add(sprite);
					SMGameCompositComponent::Add(spriteGroup);
				}
				else
					spriteGroup->Add(sprite);
			}

			//controlok hozzáadása, ahol: isUpdatable == true
			SMList<SMControl *> controlList;
			control->GetControls(controlList);

			for (controlList.First(); controlList.IsDone(); controlList.Next())
				SMGameCompositComponent::Add(controlList.Current());
		}
    }

	void SMGuiLayer::WriteReport()
	{
		SMLogger::Instance().WriteOutput("SpriteGroupList:");
		SMGameCompositComponent::WriteReport();
	}
};};
