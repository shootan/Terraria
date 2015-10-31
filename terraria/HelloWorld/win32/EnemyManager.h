#pragma once
#include "cocos2d.h"
using namespace cocos2d;

#include "Enemy_Mira.h"
#include "BlockManager.h"

class EnemyManager
{
private:
	EnemyManager()
	{
		m_pMira = NULL;
	}
	~EnemyManager()
	{
		delete instance;
		instance = NULL;	
	}
	CCNode*			m_pGround;
	Enemy_Mira*		m_pMira;

public:
	static EnemyManager* instance;
	static EnemyManager* sharedManager()
	{
		if( instance == NULL ) instance = new EnemyManager;
		return instance;
	}

	void CheckHero(int _check)
	{
		if(_check == 7) m_pMira->SetDirection(_check);
		else m_pMira->SetDirection(_check);
	}


	void SetScene(CCNode* _pGround)
	{
		m_pGround = _pGround;
	}

	void LoadEnemy()
	{
		m_pMira =  new Enemy_Mira;
		m_pMira->init();
		m_pMira->setPosition(ccp(800,965));
		m_pGround->addChild(m_pMira);

		BlockManager::sharedManager()->SetEnemy(m_pMira);
	}

	void WalkTick(ccTime dt)
	{
		m_pMira->animation(dt);
		m_pMira->WalkAction(dt);
	}	

	void IdleTick(ccTime dt)
	{
		m_pMira->animation(dt);
		m_pMira->IdleAction(dt);
	}

	CGPoint GetEnemyPos()
	{
		return m_pMira->getPosition();
	}
};