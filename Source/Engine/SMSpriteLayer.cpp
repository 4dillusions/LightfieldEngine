#include "SMSpriteLayer.h"
#include "..\\IO\\SMLogger.h"

using namespace SMEngine::IO;

namespace SMEngine { namespace Engine
{
    SMSpriteLayer::SMSpriteLayer(const SMString &name) : SMGameCompositComponent(name)
    { }

    SMSpriteLayer::~SMSpriteLayer()
    { }

    void SMSpriteLayer::Add(SMGameComponent *gameComponent)
    {
		if (dynamic_cast<SMSprite *>(gameComponent) != nullptr)
		{
			SMString spriteGroupCode = ((SMSprite*)gameComponent)->GroupCode();
			SMSpriteGroup *spriteGroup = (SMSpriteGroup *)Find(spriteGroupCode); //A Layer SpriteGroup-okat tárol

    		if (spriteGroup == nullptr)
    		{
    			spriteGroup = new SMSpriteGroup(spriteGroupCode);
    			spriteGroup->Add(gameComponent);
				SMGameCompositComponent::Add(spriteGroup);
    		}
    		else
    			spriteGroup->Add(gameComponent);
		}
    }

	void SMSpriteLayer::WriteReport()
	{
		SMLogger::Instance().WriteOutput("SpriteGroupList:");
		SMGameCompositComponent::WriteReport();
	}
};};
