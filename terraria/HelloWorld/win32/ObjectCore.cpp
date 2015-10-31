#include "ObjectCore.h"

void ObjectCore::initObject()
{
	BACK = CCSprite::spriteWithFile("BGA/MainBga.png");
	BACK->setPosition(ccp(0,0));
	BACK->setAnchorPoint(ccp(0,0));
	m_pScene->addChild(BACK);

	RenderingManager::sharedManager()->SetScene(m_pScene);
	RenderingManager::sharedManager()->initBackBuffer();
	RenderingManager::sharedManager()->SetMainBack(BACK);
	

	BlockManager::sharedManager()->setGround(m_pScene);
	BlockManager::sharedManager()->loadResource();

	CCSprite* BGA = CCSprite::spriteWithFile("BGA/C.png");
	BGA->setPosition(ccp(0,0));
	BGA->setAnchorPoint(ccp(0,0));
	
	RenderingManager::sharedManager()->GetBuffer()->addChild(BGA);

	RenderingManager::sharedManager()->SetBga(BGA);	

	m_pHero = new Object_Hero;
	m_pHero->init();
	m_pHero->setPosition(ccp(200,1200));
	AttackManager::sharedManager()->SetHero(m_pHero);

	m_pScene->addChild(m_pHero);

	EnemyManager::sharedManager()->SetScene(m_pScene);
	EnemyManager::sharedManager()->LoadEnemy();

	BlockManager::sharedManager()->CheckCloseBlock(m_pHero->getPosition(), m_pScene);

	for(int i=0; i<2; i++)
	{
		for(int j=0; j< 2; j++)
		{
			Cloud[i][j] = CCSprite::spriteWithFile("BGA/GameCloud.png");
			Cloud[i][j]->setPosition(ccp(-1024 +(j*1024)+(i*2048), 1300+(j*25)));
			Cloud[i][j]->setAnchorPoint(ccp(0,0));
			m_pScene->addChild(Cloud[i][j]);
		}
		
	}

	ItemManager::sharedManager()->SetScene(m_pScene);
	ItemManager::sharedManager()->LoadInventory();

	m_pHeart = CCProgressTimer::progressWithFile("terraria/Heart.png");
	m_pHeart->setType(kCCProgressTimerTypeHorizontalBarLR);
	m_pHeart->setPosition( ccp(950, 0));
	m_pHeart->setPercentage(m_pHero->GetLiveFlag());
	m_pScene->addChild(m_pHeart);

	m_pHeartDebug = CCLabelTTF::labelWithString("none", "Arial", 13.f);
	m_pHeartDebug->setAnchorPoint(ccp(0.5,0));
	m_pHeartDebug->setColor(ccc3(0,255,0));
	m_pHeartDebug->setPosition(ccp(950, 0));
	m_pScene->addChild(m_pHeartDebug);

	RenderingManager::sharedManager()->Rendering();
}

void ObjectCore::tick(ccTime dt)
{
	this->CheckDistance(dt);
	this->MoveCloud(dt);
	if(BlockManager::sharedManager()->CheckCloseBlock(ObjectCore::sharedManager()->GetHeroPosition(), m_pScene))
		RenderingManager::sharedManager()->Rendering();
	ItemManager::sharedManager()->OpenInventory(dt);
	ItemManager::sharedManager()->UpdateItemBox(ObjectCore::sharedManager()->GetHeroPosition(), dt);
	ItemManager::sharedManager()->UpdateFactory();
}

void ObjectCore::CheckDistance(ccTime dt)
{
	CGPoint HeroPos = m_pHero->getPosition();
	CGPoint EnemyPos = EnemyManager::sharedManager()->GetEnemyPos();

	CGPoint vec = ccp(HeroPos.x -EnemyPos.x, HeroPos.y -EnemyPos.y);

	float fDistance = sqrtf( vec.x * vec.x + vec.y * vec.y );

	if(fDistance < 250.f)
	{
		if(HeroPos.x > EnemyPos.x)
			EnemyManager::sharedManager()->CheckHero(7);
		else
			EnemyManager::sharedManager()->CheckHero(6);

		EnemyManager::sharedManager()->WalkTick(dt);
	}
	else
		EnemyManager::sharedManager()->IdleTick(dt);

	if(fDistance < 15.f)
	{
		if(HeroPos.x > EnemyPos.x )	m_pHero->SetDamage(2, 2);
		else	m_pHero->SetDamage(2, 1);
		//m_pHero->KnockBack();
	}
}

void ObjectCore::MoveCloud(ccTime dt)
{
	for(int i=0; i< 2; i++)
	{
		for(int j=0; j<2; j++)
		{
			CGPoint pos = Cloud[i][j]->getPosition();
			pos.x -= 10.f*((j+1)*3)*dt;
			if(pos.x < -2000.f) pos.x = 2000.f;
			Cloud[i][j]->setPosition(pos);
		}
	}
}

void ObjectCore::DebugHeart(CGPoint _pos)
{
	CGPoint pos = m_pHeartDebug->getPosition();
	pos.x = -_pos.x + 950.f;
	pos.y = -_pos.y + 535.f;
	m_pHeartDebug->setPosition(pos);

	pos = m_pHeart->getPosition();
	pos.x = -_pos.x + 950.f;
	pos.y = -_pos.y + 565.f;
	m_pHeart->setPosition(pos);
	m_pHeart->setPercentage(m_pHero->GetLiveFlag());

	CHAR TEXT[128];
	sprintf_s(TEXT, "HP : %d / 100", m_pHero->GetLiveFlag());
	m_pHeartDebug->setString(TEXT);
}