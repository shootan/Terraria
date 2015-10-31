#pragma once
#include "cocos2d.h"
using namespace cocos2d;

#define PI 3.14159265

class MouseManager
{
private:
	MouseManager()
	{;}

public:
	~MouseManager()
	{
		delete instance;
	}

public:
	static MouseManager* instance;
	static MouseManager* sharedManager()
	{
		if(instance == NULL) instance = new MouseManager;
		return instance;
	}

private:
	CCSprite* m_pMouseItembox;
public:
	void initmouseitembox(CCLayer* _bg)
	{
		m_pMouseItembox = new CCSprite;
		_bg->addChild(m_pMouseItembox,3);
	}
	void setmouseitemboxpos()
	{
		m_pMouseItembox->setPosition(this->GetMousePos());
	}
	CCSprite* getmouseitembox()
	{
		return m_pMouseItembox;
	}
	CGPoint GetMousePos()
	{
		CGPoint mPos;
		POINT lpmPos;
		RECT lprect;
		GetCursorPos(&lpmPos);
		GetWindowRect(CCDirector::sharedDirector()->getOpenGLView()->getHWnd(),&lprect);

		mPos.x = lpmPos.x - lprect.left;
		mPos.y = lprect.bottom - lpmPos.y;

		return mPos;
	}

	CGPoint GetMousePosInsprite(CCSprite* _sprite)
	{
		CGPoint spritepos = _sprite->getPosition();
		CGPoint mPos = this->GetMousePos();

		mPos.x = mPos.x - spritepos.x;
		mPos.y = mPos.y - spritepos.y;

		return mPos;
	}

	float GetMouseAngle(CGPoint mapPos, CGPoint playerPos)
	{
		CGPoint mousePos = GetMousePos();
		float rad = atan2(mousePos.x-mapPos.x-playerPos.x, mousePos.y-mapPos.y-playerPos.y) * 180 / PI;
		if( rad < 0 )
			rad = 360 + rad;
		return rad;
	}

	float GetDistance(CGPoint f_pos, CGPoint s_pos)
	{
		CGPoint Vecter = ccp(f_pos.x - s_pos.x, f_pos.y - s_pos.y);
		float distance = sqrtf(Vecter.x*Vecter.x + Vecter.y*Vecter.y);
		return distance;
	}

	CGPoint GetVector(CGPoint f_pos, CGPoint s_pos)
	{
		CGPoint Vecter = ccp(f_pos.x - s_pos.x, f_pos.y - s_pos.y);

		float distance = GetDistance(f_pos, s_pos);

		Vecter.x /= distance;
		Vecter.y /= distance;

		return Vecter;
	}
	
};