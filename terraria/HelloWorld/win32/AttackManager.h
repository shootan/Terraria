#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#include "ItemManager.h"
#include "Object_Hero.h"


class AttackManager
{
private:
	AttackManager()
	{
		m_pHero		= NULL;
		instance	= NULL;
		
	}
	~AttackManager()
	{
		m_pHero		= NULL;
		instance	= NULL;
	}	

	Object_Hero*	m_pHero;

public:
	static AttackManager* instance;
	static AttackManager* sharedManager()
	{
		if( instance == NULL ) instance = new AttackManager;
		return instance;
	}

	void SetHero(Object_Hero* _hero)
	{
		m_pHero = _hero;
	}
	
	void Attack(CGPoint _MousePos)
	{
		CGPoint pos = m_pHero->getPosition();

		CGPoint m_Vector2D = ccp(_MousePos.x - pos.x, _MousePos.y- pos.y);

		float fDistance = sqrtf(m_Vector2D.x*m_Vector2D.x + m_Vector2D.y*m_Vector2D.y);

		m_Vector2D.x /= fDistance;
		m_Vector2D.y /= fDistance;

		pos.x += m_Vector2D.x *  2.f;
		pos.y += m_Vector2D.y * 2.f;

		float r = atan2(m_Vector2D.x, m_Vector2D.y);

		r = r / 3.141592f * 180.f;
	
		if(m_pHero->m_iState != JUMP && m_pHero->m_iState != DOWN)
		{
			if(ItemManager::sharedManager()->GetSelectItemIndex()== 0 )
				m_pHero->m_iState = IDLE;
			if(ItemManager::sharedManager()->GetSelectItemIndex()!= 0 &&
				ItemManager::sharedManager()->GetSelectItemIndex()<3)
			{
				m_pHero->setWeapon(r);
				m_pHero->m_iState = ITEM;
			}
			if(ItemManager::sharedManager()->GetSelectItemIndex() == 5)
			{
				m_pHero->setWeapon(r);
				m_pHero->m_iState = BOWATTACK;
			}
			if(ItemManager::sharedManager()->GetSelectItemIndex() == 6)
			{
				m_pHero->setWeapon(r);
				m_pHero->m_iState = ATTACK;
			}
		}		
	}
	
};