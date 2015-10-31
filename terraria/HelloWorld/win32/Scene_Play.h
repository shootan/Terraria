#pragma once
#include "cocos2d.h"

#include "ObjectCore.h"


using namespace cocos2d;

class Scene_Play : public CCLayer
{
public:
	static CCScene* scene();
	virtual bool init();
	virtual void tick(ccTime dt);

	void ccTouchesBegan(NSSet *pTouches, UIEvent *pEvent);
	void SceneScroll(ccTime dt);

	void dynamicTracking();

	LAYER_NODE_FUNC(Scene_Play);

protected:
	CGPoint cgDynamicTracking;
	CCSprite* m_pBGA;
	Object_Hero* m_pHero;
	CCSprite* BACK;
	CCSprite* BACK2;
	
	CCLabelTTF* m_debug;
	void DebugScreen();

	CCRenderTexture* m_pBuf;
	int BlockIndex;

	

};