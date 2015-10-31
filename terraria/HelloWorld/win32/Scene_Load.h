#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Scene_Load : public CCLayer
{
public:

	static CCScene* scene();
	virtual bool init();
	virtual void tick(ccTime dt);
	//void ButtonCallback1(NSObject* pSender);

	void LoadAnimation(ccTime dt);

	LAYER_NODE_FUNC(Scene_Load);

protected:
	int Count;

	bool Change;
	CCLabelTTF* m_debug;
	CCSprite* m_pBGA;

	CCProgressTimer* m_pLoadingBar;
	float Guage;
	CCSprite* BackLogo;
	CCSprite* Text;
	float m_fTime;


};