#pragma once
#include "cocos2d.h"

using namespace cocos2d;
#include "Object_Enemy.h"


class Enemy_Mira : public Object_Enemy
{
public:
	virtual bool init()
	{
		if(!Object_Enemy::init()) return false;
		this->LoadingAnimation();
		m_cgBoundSize = m_pRender->getContentSize();
		return true;
	}
	void LoadingAnimation()
	{

		m_pRender = new CCSprite;
		m_pRender->init();
		m_pRender->setAnchorPoint(ccp(0, 0));

		this->addChild(m_pRender);

		CHAR szTemp[128] = {0};

		CCAnimation* Ani = new CCAnimation;

		Ani = new CCAnimation;
		Ani->initWithName("WALK");
		for(int i=0; i<14; i++)
		{
			sprintf_s(szTemp,"Enemy/Mira_%d.png", i);
			Ani->addFrameWithFileName(szTemp);
		}
		m_pRender->addAnimation(Ani);


		m_pRender->setDisplayFrame("WALK", 0);

	}

protected:
	//CCSprite* m_pRender;

};
