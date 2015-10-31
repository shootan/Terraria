#include "Scene_Load.h"
#include "Scene_Play.h"
#include "ResourceManager.h"


CCScene* Scene_Load::scene()
{
	CCScene *scene = CCScene::node();

	Scene_Load *layer = Scene_Load::node();

	scene->addChild(layer);

	return scene;
}

bool Scene_Load::init()
{
	if(!CCLayer::init()) return false;
	this->setIsTouchEnabled(true);
	this->setIsMouseEnabled(true);	
	m_pBGA = CCSprite::spriteWithFile("BGA/MainBga.png");
	m_pBGA->setAnchorPoint(ccp(0,0));
	m_pBGA->setPosition(ccp(0,0));
	this->addChild(m_pBGA);


	CCSprite* m_pBack = CCSprite::spriteWithFile("BGA/Background_1.png");
	m_pBack->setPosition(ccp(0,0));
	m_pBack->setAnchorPoint(ccp(0,0));
	this->addChild(m_pBack);

	CCSprite* m_pBga2 = CCSprite::spriteWithFile("BGA/Background_61.png");
	m_pBga2->setPosition(ccp(0,0));
	m_pBga2->setAnchorPoint(ccp(0,0));
	m_pBga2->setScale(0.5);
	this->addChild(m_pBga2);

	CCSprite* m_pBga3 = CCSprite::spriteWithFile("BGA/Background_61.png");
	m_pBga3->setPosition(ccp(512,0));
	m_pBga3->setAnchorPoint(ccp(0,0));
	m_pBga3->setScale(0.5);
	this->addChild(m_pBga3);

	CGSize m_winSize = CCDirector::sharedDirector()->getWinSize();
	BackLogo = CCSprite::spriteWithFile("BGA/Logo.png");
	BackLogo->setColor(ccc3(30,30,30));
	BackLogo->setScale(0.7f);
	
	BackLogo->setPosition(ccp(m_winSize.width/2, m_winSize.height/2));
	this->addChild(BackLogo);
	Guage = 0.f;
	m_pLoadingBar = CCProgressTimer::progressWithFile("BGA/Logo.png");
	m_pLoadingBar->setType(kCCProgressTimerTypeHorizontalBarLR);
	m_pLoadingBar->setPosition( ccp(m_winSize.width/2, m_winSize.height/2));
	m_pLoadingBar->setScale(0.7f);
	m_pLoadingBar->setPercentage(Guage);

	this->addChild(m_pLoadingBar);

	Count  = -1;

	/*m_debug = CCLabelTTF::labelWithString("none", "Arial", 30.f);
	m_debug->setAnchorPoint(ccp(0,0));
	m_debug->setColor(ccc3(0,255,10));
	m_debug->setPosition(ccp(800,100));
	this->addChild(m_debug);

	CHAR TEXT[128];
	sprintf_s(TEXT, "¸Ê ·Îµù Áß");
	m_debug->setString(TEXT);*/

	Change = false;

	Text = new CCSprite;
	Text->init();
	Text->setPosition(ccp(650,0));
	Text->setAnchorPoint(ccp(0,0));
	Text->setScale(0.5);
	this->addChild(Text);

	CHAR TEXT[128];
	CCAnimation* ani = new CCAnimation;
	ani->initWithName("LOGO");
	for(int i=0; i<9; i++)
	{
		sprintf_s(TEXT, "Load/Load_%d.png", i);
		ani->addFrameWithFileName(TEXT);
	}

	Text->addAnimation(ani);
	Text->setDisplayFrame("LOGO", 0);

	m_fTime = 0.f;

	this->schedule(schedule_selector(Scene_Load::tick));
	return true;
}

void Scene_Load::tick(ccTime dt)
{
	
	this->LoadAnimation(dt);
}

void Scene_Load::LoadAnimation(ccTime dt)
{
	switch(Count)
	{
	case -1:
		Count = ResourceManager::sharedManager()->AllLoading();
		Guage = 9.f;
		Text->setDisplayFrame("LOGO", 1);
		m_pLoadingBar->setPercentage(Guage);
		break;
	case 0:
		Count = ResourceManager::sharedManager()->AllLoading();
		Guage = 18.f;
		Text->setDisplayFrame("LOGO", 2);
		m_pLoadingBar->setPercentage(Guage);
		break;
	case 1:
		Count = ResourceManager::sharedManager()->AllLoading();
		Guage = 27.f;
		Text->setDisplayFrame("LOGO", 0);
		m_pLoadingBar->setPercentage(Guage);
		break;
	case 2:
		Count = ResourceManager::sharedManager()->AllLoading();
		Guage = 36.f;
		Text->setDisplayFrame("LOGO", 1);
		m_pLoadingBar->setPercentage(Guage);
		break;
	case 3:
		Count = ResourceManager::sharedManager()->AllLoading();
		Guage = 45.f;
		Text->setDisplayFrame("LOGO", 3);
		m_pLoadingBar->setPercentage(Guage);
		break;
	case 4:
		Count = ResourceManager::sharedManager()->AllLoading();
		Guage = 54.f;
		Text->setDisplayFrame("LOGO", 4);
		m_pLoadingBar->setPercentage(Guage);
		break;
	case 5:
		Count = ResourceManager::sharedManager()->AllLoading();
		Guage = 63.f;
		Text->setDisplayFrame("LOGO", 5);
		m_pLoadingBar->setPercentage(Guage);
		break;
	case 6:
		Count = ResourceManager::sharedManager()->AllLoading();
		Guage = 72.f;
		Text->setDisplayFrame("LOGO", 3);
		m_pLoadingBar->setPercentage(Guage);
		break;
	case 7:
		Count = ResourceManager::sharedManager()->AllLoading();
		Guage = 81.f;
		Text->setDisplayFrame("LOGO", 4);
		m_pLoadingBar->setPercentage(Guage);
		break;

	case 8:
		Count = ResourceManager::sharedManager()->AllLoading();
		Guage = 90.f;
		Text->setDisplayFrame("LOGO", 5);
		m_pLoadingBar->setPercentage(Guage);
		break;

	case 9:
		Count = ResourceManager::sharedManager()->AllLoading();
		Guage = 94.f;
		Text->setDisplayFrame("LOGO", 6);
		m_pLoadingBar->setPercentage(Guage);
		break;

	case 10:
		Count = ResourceManager::sharedManager()->AllLoading();
		Guage = 100.f;
		Text->setDisplayFrame("LOGO", 7);
		m_pLoadingBar->setPercentage(Guage);
		break;

	case 11:
		m_fTime += dt;
		
		if(m_fTime>1.7f)
		{
			if(Change == false)
			{
				CCScene* TranScene = CCTransitionFade::transitionWithDuration( 2.f, Scene_Play::scene()); 
				CCDirector::sharedDirector()->replaceScene(TranScene);
				Change = true;
			}
		}
		break;
	}

}

