#include "Scene_Logo.h"
#include "Scene_Main.h"


CCScene* Scene_Logo::scene()
{
	CCScene *scene = CCScene::node();

	Scene_Logo *layer = Scene_Logo::node();

	scene->addChild(layer);

	return scene;
}

bool Scene_Logo::init()
{
	if(!CCLayer::init()) return false;
	this->setIsTouchEnabled(true);
	this->setIsMouseEnabled(true);	

	m_pLogo = CCSprite::spriteWithFile("BGA/MainLogo.png");
	m_pLogo->setAnchorPoint(ccp(0,0));
	m_pLogo->setPosition(ccp(0,0));
	this->addChild(m_pLogo);

	CheckTime = false;
	m_fTime = 0.f;
	this->schedule(schedule_selector(Scene_Logo::tick));
	return true;
}

void Scene_Logo::tick(ccTime dt)
{
	m_fTime += dt;

	if(m_fTime > 2.f)
	{
		if(CheckTime == false)
		{
			CCScene* TranScene = CCTransitionFade::transitionWithDuration( 2.f, Scene_Main::scene()); 
			CCDirector::sharedDirector()->replaceScene(TranScene);
			CheckTime = true;
			m_fTime = 0.f;
		}
	}
	
}

