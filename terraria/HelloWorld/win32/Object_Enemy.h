#pragma once
#include "cocos2d.h"

using namespace cocos2d;
#include "Object.h"

class Object_Enemy : public Object
{
public:
	virtual bool init();

	void SetDirection(int _direction)
	{
		if(_direction == 7) m_iDirection = RIGHT;
		else m_iDirection = LEFT;
	}

	void animation(ccTime dt);
	void IdleAction(ccTime dt);
	void WalkAction(ccTime dt);

protected:
	int Pattern;
	int PrevPattern;
	CCSprite* m_pRender;
	float m_fAcceleration;
	float m_fTime;
};

