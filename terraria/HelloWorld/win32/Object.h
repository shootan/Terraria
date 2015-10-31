#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class Object : public CCSprite
{
public:
	bool	initWithCollision(float _range, CGSize _BoundSize);
	bool	PointInRect(CGPoint _point);
	bool	RectInRect(CGRect _rect);
	CGRect	getBoundBox();

	

protected:
	float	m_fCloseDistance;
	CGSize	m_cgBoundSize;
	
public:
	int m_iState;
	int m_iPrevState;
	float m_fFrame;
	float m_fAcceleration;
	float m_fSpeed;
	int m_iDirection;
};

enum 
{
	IDLE, WALK, JUMP, DOWN, ATTACK, BOWATTACK, LEFT, RIGHT, ITEM, KNOCKBACK
};