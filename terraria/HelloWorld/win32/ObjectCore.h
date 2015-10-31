#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#include "Object_block.h"
#include "Object_Hero.h"
#include "Object_Item.h"
#include "BlockManager.h"
#include "AttackManager.h"
#include "ItemManager.h"
#include "EnemyManager.h"
#include "RenderingManager.h"

class ObjectCore 
{
private:
	ObjectCore()
	{
		
	}
	~ObjectCore()
	{
		delete instance;
		instance = NULL;	
	}

	Object_Hero*		m_pHero;
	Object_Item*		m_pItem;
	CCLayer*			m_pScene;
	CCSprite*			BACK;
	CCSprite*			Cloud[2][2];
	CCProgressTimer*	m_pHeart;
	int					m_iHeartGuage;
	CCLabelTTF*			m_pHeartDebug;
	
public:
	static ObjectCore* instance;
	static ObjectCore* sharedManager()
	{
		if( instance == NULL ) instance = new ObjectCore;
		return instance;
	}
	void SetScene(CCLayer* _scene)
	{
		m_pScene = _scene;
	}
	CGPoint GetHeroPosition()
	{
		return m_pHero->getPosition();
	}
	void initObject();

	void tick(ccTime dt);
	
	void SetMainBga(CGPoint _pos)
	{
		BACK->setPosition(_pos);
	}

	void CheckDistance(ccTime dt);
	void MoveCloud(ccTime dt);
	void DebugHeart(CGPoint _pos);
};