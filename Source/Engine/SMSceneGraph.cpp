#include "SMSceneGraph.h"

namespace SMEngine { namespace Engine
{
	SMSceneGraph *SMSceneGraph::instance = nullptr;

    SMSceneGraph::SMSceneGraph() : SMGameCompositComponent("SceneGraph"), mainScreen(nullptr)
    { }

    SMSceneGraph::~SMSceneGraph()
    { }

    void SMSceneGraph::CreateInstance()
    {
    	if (instance == nullptr)
       		instance = new SMSceneGraph();
    }

    void SMSceneGraph::ReleaseInstance()
    {
        if (instance != nullptr)
        {
           	delete instance;
           	instance = nullptr;
        }
    }

    void SMSceneGraph::MainScreen(const SMString &name)
    {
    	SMScreen *screen = (SMScreen *)Find(name);

    	if (screen != nullptr)
    		mainScreen = screen;
    }

    void SMSceneGraph::Add(SMGameComponent *gameComponent)
    {
    	if (dynamic_cast<SMScreen *>(gameComponent) != nullptr)
    	{
			SMScreen *screen = (SMScreen *)Find(gameComponent->Name());

			if (screen == nullptr)
			{
				SMGameCompositComponent::Add(gameComponent);
				mainScreen = (SMScreen *)gameComponent;
			}
    	}
    }

    void SMSceneGraph::Update(double deltaTime)
    {
    	if (mainScreen != nullptr)
    		mainScreen->Update(deltaTime);
    }
};};
