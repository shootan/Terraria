#include "Scene_Main.h"
#include "Scene_Load.h"
#include "MouseManager.h"

CCScene* Scene_Main::scene()
{
	CCScene *scene = CCScene::node();

	Scene_Main *layer = Scene_Main::node();

	scene->addChild(layer);

	return scene;
}

bool Scene_Main::init()
{
	if(!CCLayer::init()) return false;
	this->setIsTouchEnabled(true);
	this->setIsMouseEnabled(true);

	SoundManager::sharedManager()->init();
	SoundManager::sharedManager()->sndLoad();
	SoundManager::sharedManager()->play(SOUND_MAIN_BGM);

	Change = false;
	PlayTime = 0.f;

	pItem01 = CCMenuItemImage::itemFromNormalImage("Start.png" 
		,"Start.png", this, menu_selector(Scene_Main::ButtonCallback1));
	pItem01->setPosition(ccp(0,-100));
	pItem01->setScale(0.7);

	MainBga = CCSprite::spriteWithFile("BGA/MainBga.png");
	MainBga->setPosition(ccp(0,0));
	MainBga->setAnchorPoint(ccp(0,0));
	
	this->addChild(MainBga);

	Cloud[0] = CCSprite::spriteWithFile("BGA/Cloud.png");
	Cloud[0]->setPosition(ccp(0,400));
	Cloud[0]->setAnchorPoint(ccp(0,0));
	Cloud[0]->setScale(0.5);
	MainBga->addChild(Cloud[0]);

	Cloud[1] = CCSprite::spriteWithFile("BGA/Cloud.png");
	Cloud[1]->setPosition(ccp(1024,400));
	Cloud[1]->setAnchorPoint(ccp(0,0));
	Cloud[1]->setScale(0.5);
	MainBga->addChild(Cloud[1]);

	Logo = CCSprite::spriteWithFile("BGA/Logo.png");
	Logo->setPosition(ccp(512, 400));
	Logo->setScale(0.5);

	Ani = new CCAnimation;
	Ani->initWithName("SUN");
	Ani->addFrameWithFileName("BGA/Sun.png");
	Ani->addFrameWithFileName("BGA/Moon.png");

	Sun = new CCSprite;
	Sun->init();
	Sun->addAnimation(Ani);
	Sun->setPosition(ccp(0,300));
	Sun->setDisplayFrame("SUN", 0);
	SunCheck = 1;
	SunMoveCheck = 0;
	
	MainBga->addChild(Sun);

	CHAR szTemp[128] = {0};
	for(int i=0; i<5; i++)
	{
		sprintf_s(szTemp, "BGA/Background_%d.png", i);
		
		Bga[i] = CCSprite::spriteWithFile(szTemp);
		Bga[i]->setPosition(ccp(0,-50));
		Bga[i]->setAnchorPoint(ccp(0,0));
		Bga[i]->setOpacity(0);
		Bga[i]->setIsVisible(false);
		MainBga->addChild(Bga[i]);
	}
	BgaCheck = 0;

	Ani = new CCAnimation;
	Ani->initWithName("TREE");
	for(int i=0; i<4; i++)
	{
		sprintf_s(szTemp, "BGA/Tree_%d.png", i);
		Ani->addFrameWithFileName(szTemp);
	}

	for(int i=0; i<2; i++)
	{
		Tree[i] = new CCSprite;
		Tree[i]->init();
		Tree[i]->addAnimation(Ani);
		Tree[i]->setPosition(ccp(2048*i,0));
		Tree[i]->setAnchorPoint(ccp(0,0));
		Tree[i]->setDisplayFrame("TREE", 0);
		MainBga->addChild(Tree[i]);
	}
	
	CCMenu* pMenu = CCMenu::menuWithItems(pItem01,NULL);

	Bga[0]->setIsVisible(true);
	Bga[0]->runAction(CCFadeTo::actionWithDuration(1.f, 255));
	this->addChild(pMenu);

	MainBga->addChild(Logo);

	CCScaleTo* LogoScale1 = CCScaleTo::actionWithDuration(5.f, 0.8f);
	CCScaleTo* LogoScale2 = CCScaleTo::actionWithDuration(5.f, 0.5f);
	CCRotateTo* LogoRotate1 = CCRotateTo::actionWithDuration(5.f, 10.f);
	CCRotateTo* LogoRotate3 = CCRotateTo::actionWithDuration(5.f, 0.f);
	CCRotateTo* LogoRotate2 = CCRotateTo::actionWithDuration(5.f, -10.f);
	CCSpawn* Logo1 = CCSpawn::actionOneTwo(LogoScale1, LogoRotate1);
	CCSpawn* Logo2 = CCSpawn::actionOneTwo(LogoScale2, LogoRotate3);
	CCSpawn* Logo3 = CCSpawn::actionOneTwo(LogoScale1, LogoRotate2);

	CCFiniteTimeAction* Logoseq = CCSequence::actions(Logo1, Logo2, Logo3, NULL);
	CCRepeatForever* LogoRepeat = CCRepeatForever::actionWithAction((CCActionInterval*) Logoseq);
	Logo->runAction(LogoRepeat);

	this->schedule(schedule_selector(Scene_Main::tick));
	return true;
}

void Scene_Main::SunMove(ccTime dt)
{
	CGPoint SunPos = Sun->getPosition();
	CGPoint pos1 = ccp(0, 300);
	CGPoint pos2 = ccp(200, 470);
	CGPoint pos3 = ccp(312, 530);
	CGPoint pos4 = ccp(512, 590);
	CGPoint pos5 = ccp(712, 530);
	CGPoint pos6 = ccp(824, 470);
	CGPoint pos7 = ccp(1024, 300);
	CGPoint Vec;
	float fDistance;

	switch(SunMoveCheck)
	{
	case 0:
		{
			Vec = ccp(SunPos.x - pos2.x, SunPos.y - pos2.y);
			fDistance = sqrtf(Vec.x*Vec.x + Vec.y*Vec.y);
			Vec.x /= fDistance;
			Vec.y /= fDistance;

			SunPos.x -= Vec.x*dt*100.f;
			SunPos.y -= Vec.y*dt*100.f;

			if(fDistance < 1.0f) SunMoveCheck = 1;
			break;
		}
	case 1:
		{
			Vec = ccp(SunPos.x - pos3.x, SunPos.y - pos3.y);
			fDistance = sqrtf(Vec.x*Vec.x + Vec.y*Vec.y);
			Vec.x /= fDistance;
			Vec.y /= fDistance;

			SunPos.x -= Vec.x*dt*100.f;
			SunPos.y -= Vec.y*dt*100.f;

			if(fDistance < 1.0f) SunMoveCheck = 2;
			break;
		}
	case 2:
		{
			Vec = ccp(SunPos.x - pos4.x, SunPos.y - pos4.y);
			fDistance = sqrtf(Vec.x*Vec.x + Vec.y*Vec.y);
			Vec.x /= fDistance;
			Vec.y /= fDistance;

			SunPos.x -= Vec.x*dt*100.f;
			SunPos.y -= Vec.y*dt*100.f;

			if(fDistance < 1.0f) SunMoveCheck = 3;
			break;
		}
	case 3:
		{
			Vec = ccp(SunPos.x - pos5.x, SunPos.y - pos5.y);
			fDistance = sqrtf(Vec.x*Vec.x + Vec.y*Vec.y);
			Vec.x /= fDistance;
			Vec.y /= fDistance;

			SunPos.x -= Vec.x*dt*100.f;
			SunPos.y -= Vec.y*dt*100.f;

			if(fDistance < 1.0f) SunMoveCheck = 4;
			break;
		}
	case 4:
		{
			Vec = ccp(SunPos.x - pos6.x, SunPos.y - pos6.y);
			fDistance = sqrtf(Vec.x*Vec.x + Vec.y*Vec.y);
			Vec.x /= fDistance;
			Vec.y /= fDistance;

			SunPos.x -= Vec.x*dt*100.f;
			SunPos.y -= Vec.y*dt*100.f;

			if(fDistance < 1.0f) SunMoveCheck = 5;
			break;
		}
	case 5:
		{
			Vec = ccp(SunPos.x - pos7.x, SunPos.y - pos7.y);
			fDistance = sqrtf(Vec.x*Vec.x + Vec.y*Vec.y);
			Vec.x /= fDistance;
			Vec.y /= fDistance;

			SunPos.x -= Vec.x*dt*100.f;
			SunPos.y -= Vec.y*dt*100.f;

			if(fDistance < 1.0f)
			{
				SunMoveCheck = 0;
				SunPos = ccp(0,300);
				if(SunCheck == 0) SunCheck = 1;
				else if(SunCheck == 1) SunCheck = 0;
				ActionInit();
			}
			break;
		}
	case 6:
		{
			/*Vec = ccp(SunPos.x - pos8.x, SunPos.y - pos8.y);
			fDistance = sqrtf(Vec.x*Vec.x + Vec.y*Vec.y);
			Vec.x /= fDistance;
			Vec.y /= fDistance;

			SunPos.x -= Vec.x*dt*100.f;
			SunPos.y -= Vec.y*dt*100.f;

			if(fDistance < 1.0f) SunMoveCheck = 4;*/
			break;
		}
	case 7:
		{

			break;
		}
	}

	Sun->setPosition(SunPos);
}

void Scene_Main::ActionInit()
{
	switch(SunCheck)
	{
	case 0:
		{
			Sun->setDisplayFrame("SUN", 1);
			MainBga->runAction(CCTintTo::actionWithDuration(3.f, 95, 95, 95));
			for(int i=0; i<5; i++)
			{
				Bga[i]->runAction(CCTintTo::actionWithDuration(3.f, 95, 95, 95));
			}
			Cloud[0]->runAction(CCTintTo::actionWithDuration(3.f, 95, 95, 95));
			Cloud[1]->runAction(CCTintTo::actionWithDuration(3.f, 95, 95, 95));
			Tree[0]->runAction(CCTintTo::actionWithDuration(3.f, 95, 95, 95));
			Tree[1]->runAction(CCTintTo::actionWithDuration(3.f, 95, 95, 95));
			Logo->runAction(CCTintTo::actionWithDuration(3.f, 150, 150, 150));
			pItem01->runAction(CCTintTo::actionWithDuration(3.f, 95, 95, 95));
			break;
		}

	case 1:
		{
			Sun->setDisplayFrame("SUN", 0);
			MainBga->runAction(CCTintTo::actionWithDuration(3.f, 255, 255, 255));
			for(int i=0; i<5; i++)
			{
				Bga[i]->runAction(CCTintTo::actionWithDuration(3.f, 255, 255, 255));
			}
			Cloud[0]->runAction(CCTintTo::actionWithDuration(3.f, 255, 255, 255));
			Cloud[1]->runAction(CCTintTo::actionWithDuration(3.f, 255, 255, 255));
			Tree[0]->runAction(CCTintTo::actionWithDuration(3.f, 255, 255, 255));
			Tree[1]->runAction(CCTintTo::actionWithDuration(3.f, 255, 255, 255));
			Logo->runAction(CCTintTo::actionWithDuration(3.f, 255, 255, 255));
			pItem01->runAction(CCTintTo::actionWithDuration(3.f, 255, 255, 255));
			BgaCheck++;
			if(BgaCheck ==4) BgaCheck = 0;
			break;
		}
	}
}

void Scene_Main::tick(ccTime dt)
{
	PlayTime += 100.f * dt;
	BackgroundChange(BgaCheck);
	BackgroundAnimation(BgaCheck, dt);
	SunMove(dt);

	if(GetAsyncKeyState(VK_SPACE) && Change != true)
	{
		if(Change == false )
		{
			CCDirector::sharedDirector()->replaceScene(Scene_Load::scene());
			Change = true;
		}
	}
	
}

void Scene_Main::ButtonSound()
{
	CGPoint pos = MouseManager::sharedManager()->GetMousePos();


}

void Scene_Main::BackgroundChange(int _check)
{
	switch(_check)
	{
	case 0:
		{
			if(Bga[0]->getIsVisible() == false)
			{
				Bga[0]->setIsVisible(true);
				Bga[0]->runAction(CCFadeTo::actionWithDuration(0.4f, 255));
				Bga[3]->setOpacity(0);
				Bga[3]->setIsVisible(false);
			}
			break;
		}
	case 1:
		{
			if(Bga[1]->getIsVisible() == false)
			{
				Bga[1]->setIsVisible(true);
				Bga[1]->runAction(CCFadeTo::actionWithDuration(0.4f, 255));
				Bga[0]->setOpacity(0);
				Bga[0]->setIsVisible(false);
			}
			break;
		}
	case 2:
		{
			if(Bga[2]->getIsVisible() == false)
			{
				Bga[2]->setIsVisible(true);
				Bga[2]->runAction(CCFadeTo::actionWithDuration(0.4f, 255));
				Bga[1]->setOpacity(0);
				Bga[1]->setIsVisible(false);
			}
			break;
		}
	case 3:
		{
			if(Bga[3]->getIsVisible() == false)
			{
				Bga[3]->setIsVisible(true);
				Bga[3]->runAction(CCFadeTo::actionWithDuration(0.4f, 255));
				Bga[2]->setOpacity(0);
				Bga[2]->setIsVisible(false);
			}
			break;
		}
	}
}

void Scene_Main::BackgroundAnimation(int _check, ccTime dt)
{
	switch(_check)
	{
	case 0:
		{
			for(int i=0; i<2; i++)
			{
				Tree[i]->setDisplayFrame("TREE", 0);
			}

			break;
		}
	case 1:
		{

			for(int i=0; i<2; i++)
			{
				Tree[i]->setDisplayFrame("TREE", 1);
			}
			break;
		}
	case 2:
		{

			for(int i=0; i<2; i++)
			{
				Tree[i]->setDisplayFrame("TREE", 2);
			}
			break;
		}
	case 3:
		{

			for(int i=0; i<2; i++)
			{
				Tree[i]->setDisplayFrame("TREE", 3);
			}
			break;
		}
	}

	CGPoint CloudPos = Cloud[0]->getPosition();
	CloudPos.x -= 50.f * dt;
	if(CloudPos.x < -1042.f) CloudPos.x += 2048.f;
	Cloud[0]->setPosition(CloudPos);

	CloudPos = Cloud[1]->getPosition();
	CloudPos.x -= 50.f * dt;
	if(CloudPos.x < -1042.f) CloudPos.x += 2048.f;
	Cloud[1]->setPosition(CloudPos);


	CGPoint TreePos = Tree[0]->getPosition();
	TreePos.x -= 30.f * dt;
	if(TreePos.x < -2048.f) TreePos.x += 4096.f;
	Tree[0]->setPosition(TreePos);

	TreePos = Tree[1]->getPosition();
	TreePos.x -= 30.f * dt;
	if(TreePos.x < -2048.f) TreePos.x += 4096.f;
	Tree[1]->setPosition(TreePos);
	
}

void Scene_Main::ButtonCallback1(NSObject* pSender)
{
	if(Change == false )
	{
		//CCScene* TranScene = CCTransitionFade::transitionWithDuration( 1.f, Scene_Play::scene()); 
		CCDirector::sharedDirector()->replaceScene(Scene_Load::scene());
		Change = true;
	}
	
}