#pragma once
#include "cocos2d.h"
#include "SoundManager.h"

using namespace cocos2d;

class Scene_Main : public CCLayer
{
public:

	static CCScene* scene();
	virtual bool init();
	virtual void tick(ccTime dt);
	void ButtonCallback1(NSObject* pSender);

	void ActionInit();
	void SunMove(ccTime dt);

	void BackgroundAnimation(int _check, ccTime dt);
	void BackgroundChange(int _check);

	void ButtonSound();

	LAYER_NODE_FUNC(Scene_Main);

protected:
	CCSprite* m_pBGA;
	bool Change;
	float PlayTime;
	CCSprite* MainBga;
	CCMenuItemImage* pItem01;

	
	CCSprite* Bga[5];
	int BgaCheck;
	CCSprite* Cloud[2];
	CCSprite* Logo;

	CCSprite* Tree[2];

	CCSprite* Sun;
	int SunCheck;
	CCAnimation* Ani;
	ccBezierConfig bz;
	
	
	int SunMoveCheck;

	
};