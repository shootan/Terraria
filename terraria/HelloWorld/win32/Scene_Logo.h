#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Scene_Logo : public CCLayer
{
public:

	static CCScene* scene();
	virtual bool init();
	virtual void tick(ccTime dt);

	LAYER_NODE_FUNC(Scene_Logo);

protected:
	CCSprite* m_pLogo;
	bool	CheckTime;
	float	m_fTime;


};