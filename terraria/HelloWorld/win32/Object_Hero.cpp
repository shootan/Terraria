#include "Object_Hero.h"
#include "BlockManager.h"
#include "ResourceManager.h"
#include "RenderingManager.h"
#include "SoundManager.h"

bool Object_Hero::init()
{
	if(!CCSprite::init()) return false;

	m_fSpeed = 270.f;
	m_fFrame = 0.f;
	
	m_fAcceleration	= 0.f;
	m_iState		= DOWN;
	m_iPrevState	= DOWN;

	JumpCheck = false;

	RealSpeed = 0.f;

	AttackOn = false;
	//WeaponRotate = 45.f;
	AttackTime = 0.f;

	this->LoadingAnimation();
	m_cgBoundSize = m_pRender->getContentSize();
	m_iLiveFlag = 100;
	RecentDamage = false;
	DamageTime= 0.f;
	EnemyDir = 1;

	this->schedule(schedule_selector(Object_Hero::tick));
	return true;
}

void Object_Hero::LoadingAnimation()
{
	m_pRender = new CCSprite;
	m_pRender->init();
	m_pRender->setAnchorPoint(ccp(0, 0));

	for(int i=0; i<4; i++)
	{
		m_pRender->addAnimation(ResourceManager::sharedManager()->GetHeroAni(i));
	}

	this->addChild(m_pRender);

	m_pRender->setDisplayFrame("IDLE", 0);

	CHAR szTemp[128] = {0};

	Weapon = CCSprite::spriteWithFile("Item/Item_5.png");
	CGPoint pos = this->getPosition();
	Weapon->setPosition(ccp(pos.x+5, pos.y+18));
	Weapon->setAnchorPoint(ccp(-1, 0.5));
	Weapon->setIsVisible(true);
	this->addChild(Weapon);
}

void Object_Hero::tick(ccTime dt)
{
	animation(dt);
	action(dt);
	Attack(dt);
	if(RecentDamage == true)
	{
		
		DamageTime += dt;
		if(DamageTime > 0.1f && DamageTime < 0.2f)
		{
			m_iState = KNOCKBACK;
			m_fAcceleration = 2.f;
		}
		if(DamageTime > 0.2f)
			m_pRender->setIsVisible(false);
		if(DamageTime > 0.4f)
			m_pRender->setIsVisible(true);
		if(DamageTime > 0.6f)
			m_pRender->setIsVisible(false);
		if(DamageTime > 0.8f)
			m_pRender->setIsVisible(true);
		if(DamageTime > 1.0f)
		{
			RecentDamage = false;
			DamageTime = 0.f;
			m_iState = IDLE;
		}
		if(GetAsyncKeyState('A')||GetAsyncKeyState('D')) m_iState = WALK;
		this->KnockBack(dt);
	}
}

void Object_Hero::KnockBack(ccTime dt)
{
	CGRect VirtualRect = this->getBoundBox();
	CGPoint pos = this->getPosition();
	raycast hit;

	if(m_iState != JUMP && m_iState != DOWN)
	{
		if(m_fAcceleration > 0.f)
		{
			if(EnemyDir == 1)
			{
				VirtualRect.size.width-=16.f;
				BlockManager::sharedManager()->Raycast(VirtualRect, ccp(-1,0), m_fAcceleration, &hit, 0, 1);
				VirtualRect.size.width+=16.f;
				if(hit.Hdistance < 0.1f) hit.Hdistance = 0.f;
				RealSpeed = hit.Hdistance;
				pos.x -= hit.Hdistance;
				m_fAcceleration -= 1.5f*dt;
			}
			if(EnemyDir == 2)
			{
				VirtualRect.origin.x+=16.f;
				VirtualRect.size.width -= 16.f;
				BlockManager::sharedManager()->Raycast(VirtualRect, ccp(1,0), m_fAcceleration, &hit, 0, 1);
				VirtualRect.origin.x-=16.f;
				VirtualRect.size.width += 16.f;
				if(hit.Hdistance < 0.1f) hit.Hdistance = 0.f;
				RealSpeed = hit.Hdistance;
				pos.x += hit.Hdistance;
				m_fAcceleration -= 1.5*dt;
			}
		}
	}

	this->setPosition(pos);
}

void Object_Hero::animation(ccTime dt)
{
	if(m_iPrevState!=m_iState)
	{
		m_iPrevState = m_iState;
		m_fFrame = 0.f;
	}
	switch(m_iState)
	{
	case IDLE:
		{
			m_fFrame += 10.f * dt;
			int MaxFrame = m_pRender->animationByName("IDLE")->getFrames()->count();
			if(m_fFrame> MaxFrame) m_fFrame = 0.f;
			m_pRender->setDisplayFrame("IDLE", m_fFrame);
			break;
		}
	case KNOCKBACK:
		{
			m_pRender->setDisplayFrame("JUMP", 0);
			break;
		}
	case JUMP:
		{
			m_fFrame += 10.f * dt;
			int MaxFrame = m_pRender->animationByName("JUMP")->getFrames()->count();
			if(m_fFrame> MaxFrame) m_fFrame = 0.f;
			m_pRender->setDisplayFrame("JUMP", m_fFrame);
			break;
		}
	case WALK:
		{
			m_fFrame += 30.f * dt;
 			int MaxFrame = m_pRender->animationByName("WALK")->getFrames()->count();
			if(m_fFrame> MaxFrame) m_fFrame = 0.f;
			m_pRender->setDisplayFrame("WALK", m_fFrame);
			break;
		}
	case DOWN:
		{
			m_fFrame += 10.f * dt;
			int MaxFrame = m_pRender->animationByName("JUMP")->getFrames()->count();
			if(m_fFrame> MaxFrame) m_fFrame = 0.f;
			m_pRender->setDisplayFrame("JUMP", m_fFrame);
			break;
		}
	case ATTACK:
		{
			m_fFrame += 10.f * dt;
			int MaxFrame = m_pRender->animationByName("ATTACK")->getFrames()->count()-1;
			if(m_fFrame> MaxFrame)
			{
				m_fFrame = 0.f;
				m_iState = IDLE;
			}
			m_pRender->setDisplayFrame("ATTACK", m_fFrame);
			
			break;
		}
	case ITEM:
		{
			m_fFrame += 10.f * dt;
			int MaxFrame = m_pRender->animationByName("ATTACK")->getFrames()->count();
			if(m_fFrame> MaxFrame)
			{
				m_fFrame = 0.f;
				m_iState = IDLE;
			}
			m_pRender->setDisplayFrame("ATTACK", 3);

			break;
		}
	case BOWATTACK:
		{
			AttackTime += 10.f * dt;
			if(WeaponRotate < 20.f && WeaponRotate > -20.f) m_fFrame = 3;
			if(WeaponRotate < -20.f && WeaponRotate > -60.f) m_fFrame = 2;
			if(WeaponRotate < -60.f && WeaponRotate > -120.f) m_fFrame = 1;
			if(WeaponRotate < -120.f && WeaponRotate > -160) m_fFrame = 2;
			if(WeaponRotate < -160.f && WeaponRotate > -200.f) m_fFrame = 3;
			if(WeaponRotate < -200.f || WeaponRotate > 20.f) m_fFrame = 4;
			m_pRender->setDisplayFrame("ATTACK", m_fFrame);
			if(AttackTime > 5.f) 
			{
				m_iState = IDLE;
				AttackTime = 0.f;
			}
			break;
		}
	}
}

void Object_Hero::Attack(ccTime dt)
{
	if(m_iState == BOWATTACK)
	{
		Weapon->setIsVisible(true);

		Weapon->setRotation(WeaponRotate);
		//m_pRender->setFlipX(true);
	}

	if( m_iState!=BOWATTACK )
	{
		Weapon->setIsVisible(false);
	}
}

float Object_Hero::getSpeed()
{
	return RealSpeed;
}

void Object_Hero::action(ccTime dt)
{	
	CGRect VirtualRect = this->getBoundBox();
	CGPoint pos = this->getPosition();
	raycast hit;

	BlockManager::sharedManager()->Raycast(this->getBoundBox(), ccp(0,-1), 10.f, &hit, 1, 1);

	if(m_iState == ATTACK || m_iState == ITEM || m_iState == BOWATTACK)
	{
		CGPoint WeaPos = Weapon->getPosition();

		if(WeaponRotate < -90)
		{
			m_pRender->setFlipX(true);
			Weapon->setPosition(ccp(15, 18));
			Weapon->setAnchorPoint(ccp(-0.7, 0.6));
		}
		if(WeaponRotate > -90)
		{
			m_pRender->setFlipX(false);
			Weapon->setPosition(ccp(5, 18));
			Weapon->setAnchorPoint(ccp(-1, 0.5));
		}

		if(hit.Vdistance > 0.4f && m_iState != JUMP)
		{
			m_fAcceleration += 5.f * dt;
			if(m_fAcceleration>13.f) m_fAcceleration = 13.f;
			VirtualRect.size.height-=16.f;
			BlockManager::sharedManager()->Raycast(VirtualRect, ccp(0,-1), m_fAcceleration, &hit, 1, 1);
			VirtualRect.size.height+=16.f;
			if( hit.Vdistance< 0.2f )
			{
				hit.Vdistance = 0.f;
				m_iState = IDLE;
				m_fAcceleration = 0.f;
			}
			pos.y -= hit.Vdistance;
		}
	}
	else
	{
		if(hit.Vdistance > 0.4f && m_iState != JUMP)
		{
			m_iState = DOWN;
		}
		else if(m_iState != JUMP &&  m_iState != DOWN)
		{
			m_iState = IDLE;
		}

		switch(m_iState)
		{
		case DOWN:
			{
				m_fAcceleration += 5.f * dt;
				if(m_fAcceleration>13.f) m_fAcceleration = 13.f;
				VirtualRect.size.height-=16.f;
				BlockManager::sharedManager()->Raycast(VirtualRect, ccp(0,-1), m_fAcceleration, &hit, 1, 1);
				VirtualRect.size.height+=16.f;
				if( hit.Vdistance < 0.01f )
				{
					hit.Vdistance = 0.f;
 					m_iState = IDLE;
					m_fAcceleration = 0.f;
				}
				pos.y -= hit.Vdistance;
				break;
			}
		}

		if( GetAsyncKeyState('A') )
		{
			VirtualRect.size.width-=16.f;
			BlockManager::sharedManager()->Raycast(VirtualRect, ccp(-1,0), m_fSpeed*dt, &hit, 0, 1);
			VirtualRect.size.width+=16.f;
			if(hit.Hdistance < 0.1f) hit.Hdistance = 0.f;
			RealSpeed = hit.Hdistance;
			pos.x -= hit.Hdistance;
			m_pRender->setFlipX(true);
			if(m_iState != JUMP && m_iState != DOWN) m_iState = WALK;
		}

		if( GetAsyncKeyState('D') )
		{
			VirtualRect.origin.x+=16.f;
			VirtualRect.size.width -= 16.f;
			BlockManager::sharedManager()->Raycast(VirtualRect, ccp(1,0), m_fSpeed*dt, &hit, 0, 1);
			VirtualRect.origin.x-=16.f;
			VirtualRect.size.width += 16.f;
			if(hit.Hdistance < 0.1f) hit.Hdistance = 0.f;
			RealSpeed = hit.Hdistance;
			pos.x += hit.Hdistance;
			m_pRender->setFlipX(false);
			if(m_iState != JUMP && m_iState != DOWN) m_iState = WALK;
		}

		if( GetAsyncKeyState(VK_SPACE) && JumpCheck == false && m_iState != DOWN && m_iState != JUMP)
		{
			SoundManager::sharedManager()->play(SOUND_JUMP);
			m_iState = JUMP;
			m_fAcceleration = 4.5f;
			JumpCheck = true;
		}
		if(!GetAsyncKeyState(VK_SPACE))
		{
			JumpCheck = false;
		}

		if(m_iState == JUMP)
		{
			m_fAcceleration -= 12.f * dt;
			VirtualRect.origin.y+=16.f;
			BlockManager::sharedManager()->Raycast(VirtualRect, ccp(0,1), m_fAcceleration, &hit, 1, 1);
			VirtualRect.origin.y-=16.f;
			if(hit.Vdistance < 0.1f) hit.Vdistance = 0.f;
			pos.y += hit.Vdistance;
			if( m_fAcceleration < 0.f )
			{
				m_fAcceleration = 0.f;
				m_iState = DOWN;
			}
		}

	}

	if(pos.x < 0.1) pos.x = 0.1;
	if(pos.x > 1974.f) pos.x = 1974.f;
	this->setPosition( pos );
	

	/*if( GetAsyncKeyState(VK_UP) )
	{
		BlockManager::sharedManager()->Raycast(this->getBoundBox(), ccp(-1,0), m_fSpeed*dt, &hit);
		RealSpeed = hit.distance;
		pos.y += hit.distance;
		m_pRender->setFlipX(true);
		if(m_iState != JUMP && m_iState != DOWN) m_iState = WALK;
	}

	if( GetAsyncKeyState(VK_DOWN) )
	{
		BlockManager::sharedManager()->Raycast(this->getBoundBox(), ccp(-1,0), m_fSpeed*dt, &hit);
		RealSpeed = hit.distance;
		pos.y -= hit.distance;
		m_pRender->setFlipX(true);
		if(m_iState != JUMP && m_iState != DOWN) m_iState = WALK;
	}*/
}