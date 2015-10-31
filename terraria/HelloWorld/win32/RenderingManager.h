#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#include "BlockManager.h"
#include "Object_Hero.h"
#include "ResourceManager.h"

#define  MAP_X_SIZE		2000
#define	MAP_Y_SIZE		2000

class RenderingManager
{
private:
	RenderingManager()
	{
		instance = NULL;
	}
	~RenderingManager()
	{
		delete instance;
		instance = NULL;
	}
	
	CCRenderTexture* m_pRender;
	CCNode* m_pScene;
	CCSprite* MainBack;
	CCSprite* m_pBga;
	Object_Hero* m_pHero;
	CCSprite* Back[2];

public:
	static RenderingManager* instance;
	static RenderingManager* sharedManager()
	{
		if( instance == NULL ) instance = new RenderingManager;
		return instance;
	}

	CCRenderTexture* GetBuffer()
	{
		return m_pRender;
	}

	void SetMainBack(CCSprite* _pBack)
	{
		MainBack = _pBack;
	}

	void SetHero(Object_Hero* _pHero)
	{
		m_pHero = _pHero;
	}

	void SetBga(CCSprite* _pBga)
	{
		m_pBga = _pBga;
	}

	void SetScene(CCNode* _pScene)
	{
		m_pScene = _pScene;
	}

	void initBackBuffer()
	{
		CGSize winsize = CCDirector::sharedDirector()->getWinSize();
		m_pRender = CCRenderTexture::renderTextureWithWidthAndHeight(2000, 2000, kCCTexture2DPixelFormat_RGBA8888);
		m_pRender->setPosition(ccp(1000, 1000));
		m_pScene->addChild(m_pRender);
		for(int i=0; i<2; i++)
		{
			Back[i] = CCSprite::spriteWithTexture(ResourceManager::sharedManager()->getMap(3));
			Back[i]->setAnchorPoint(ccp(0,0));
			Back[i]->setPosition(ccp(i*1024,960));
			m_pRender->addChild(Back[i]);
		}
	}

	void SetBufferPosition(CGPoint _pos)
	{
		m_pRender->setPosition(_pos);
	}

	void Rendering()
	{
		m_pBga->setIsVisible(true);
		m_pRender->begin();

		MainBack->visit();
		m_pBga->visit();

		for(int i=0; i<2; i++)
		{
			Back[i]->visit();
		}

		BlockManager::sharedManager()->SetBlockColor();
		//BlockManager::sharedManager()->BgaRendering();
		BlockManager::sharedManager()->Rendering();

		m_pRender->end();
		m_pBga->setIsVisible(false);
	}
};