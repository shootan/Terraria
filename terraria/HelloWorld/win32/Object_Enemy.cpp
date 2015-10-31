#include "Object_Enemy.h"
#include "BlockManager.h"

bool Object_Enemy::init()
{
	if(!CCSprite::init()) return false;

	m_fFrame			= 0.f;

	m_fSpeed			= 1.2f;
	m_fAcceleration		= 0.f;
	m_iState			= DOWN;
	m_iPrevState		= DOWN;

	m_iDirection		= LEFT;

	Pattern = 0;
	PrevPattern = 0;

	m_fAcceleration = 0.f;
	m_fTime = 0.f;

	return true;
}

void Object_Enemy::animation(ccTime dt)
{
	if(m_iPrevState != m_iState)
	{
		m_iPrevState	= m_iState;
		m_fFrame		= 0.f;
	}
	switch(m_iState)
	{
	case IDLE:
		{
			m_pRender->setDisplayFrame("WALK", 1);
			break;
		}
	case JUMP:
		{
			m_fFrame += 10.f * dt;
			int MaxFrame = m_pRender->animationByName("WALK")->getFrames()->count();
			if(m_fFrame> MaxFrame) m_fFrame = 0.f;
			m_pRender->setDisplayFrame("WALK", m_fFrame);
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
			int MaxFrame = m_pRender->animationByName("WALK")->getFrames()->count();
			if(m_fFrame> MaxFrame) m_fFrame = 0.f;
			m_pRender->setDisplayFrame("WALK", m_fFrame);
			break;
		}
	}
}

void Object_Enemy::IdleAction(ccTime dt)
{
	CGPoint pos = this->getPosition();
	raycast hit;
	m_pRender->setColor(ccc3(255,255,255));

	m_fTime += dt;

	if(m_fTime > 1.f)
	{
		if(Pattern != 4) 
			Pattern = rand()%3;
		m_fTime = 0.f;
	}

	if(m_iDirection == LEFT)
	{
		BlockManager::sharedManager()->PointRaycast(pos, ccp(0,-1), 5.f, &hit, 1, 1);
	}
	if(m_iDirection == RIGHT)
	{
		BlockManager::sharedManager()->PointRaycast(pos, ccp(0,-1), 5.f, &hit, 1, 2);
	}

	if(hit.Vdistance > 0.1)
		pos.y -= hit.Vdistance;
	else
	{
		if(PrevPattern == 3)
		{
			Pattern = 4;
			m_fAcceleration = 8.5f;
		}
	}

	switch(Pattern)
	{
	case 0:
		{
			m_iState = IDLE;
			
			break;
		}
	case 1:
		{
			m_iState = WALK;
			m_iDirection = LEFT;
			BlockManager::sharedManager()->PointRaycast(pos, ccp(-1,0), 1.f, &hit, 0, 1);
			if(hit.Hdistance < 0.1f)
			{
				PrevPattern = 3;
				break;
			}

			pos.x -= hit.Hdistance;
			m_pRender->setFlipX(false);
			break;
		}
	case 2:
		{
			m_iState = WALK;
			m_iDirection = RIGHT;
			BlockManager::sharedManager()->PointRaycast(pos, ccp(1,0), 1.f, &hit, 0, 2);
			if(hit.Hdistance < 0.1f)
			{
				PrevPattern = 3;
				break;
			}

			pos.x += hit.Hdistance;
			m_pRender->setFlipX(true);

			break;
		}
	case 3:
		{
			break;
		}
	case 4:
		{
			if(m_iDirection == LEFT)
			{
				pos.y += 46;
				pos.x += 13;
				BlockManager::sharedManager()->PointRaycast(pos, ccp(0,1), m_fAcceleration, &hit, 1, 1);
				pos.y += hit.Vdistance;
				m_fAcceleration -= 11.7f *dt;

				pos.x -= 13;
				pos.y -= 46;
				BlockManager::sharedManager()->PointRaycast(pos, ccp(-1,0), 1.6f, &hit, 0, 1);

				if(m_fAcceleration < 0.1f)
				{
					Pattern = 1;
					PrevPattern = 4;
				}
				pos.x -= hit.Hdistance;
			}

			if(m_iDirection == RIGHT)
			{
				pos.y += 46;

				pos.x += 13;
				BlockManager::sharedManager()->PointRaycast(pos, ccp(0,1), m_fAcceleration, &hit, 1, 1);
				pos.y += hit.Vdistance;
				m_fAcceleration -= 11.7f *dt;

				pos.x -= 13;
				pos.y -= 46;
				BlockManager::sharedManager()->PointRaycast(pos, ccp(1,0),1.6f, &hit, 0, 2);

				if(m_fAcceleration < 0.1f)
				{
					Pattern = 1;
					PrevPattern = 4;
				}

				pos.x += hit.Hdistance;
			}
			break;
		}
	}
	if(pos.x < 1.f) pos.x = 1.f;
	this->setPosition( pos );
	
}

void Object_Enemy::WalkAction(ccTime dt)
{
	CGPoint pos = this->getPosition();
	if(Pattern == 0)
	{
		m_iState = WALK;
		Pattern = 1;
	}
	
	m_pRender->setColor(ccc3(255,100,0));
	raycast hit;
	if(m_iState != JUMP)
	{
		if(m_iDirection == LEFT)
		{
			BlockManager::sharedManager()->PointRaycast(this->getPosition(), ccp(0,-1), 5.f, &hit, 1, 1);
		}
		if(m_iDirection == RIGHT)
		{
			BlockManager::sharedManager()->PointRaycast(this->getPosition(), ccp(0,-1), 5.f, &hit, 1, 2);
		}


		if(hit.Vdistance > 0.1f)
			pos.y -= hit.Vdistance;
		else
		{
			if(m_iDirection == LEFT)
			{
				BlockManager::sharedManager()->PointRaycast(this->getPosition(), ccp(-1,0), m_fSpeed, &hit, 0, 1);
				pos.x -= hit.Hdistance;
				m_pRender->setFlipX(false);

				if(hit.Hdistance<0.1f)
				{
					m_iState = JUMP;
					m_fAcceleration = 4.f;
				}
			}
			if(m_iDirection == RIGHT)
			{
				BlockManager::sharedManager()->PointRaycast(this->getPosition(), ccp(1,0), m_fSpeed, &hit, 0, 2);
				pos.x += hit.Hdistance;
				m_pRender->setFlipX(true);
				if(hit.Hdistance<0.1f)
				{
 					m_iState = JUMP;
					m_fAcceleration = 4.f;
				}
			}
		}
	}

	else 
	{
		if(m_iDirection == LEFT)
		{
			pos.y += 46;
			BlockManager::sharedManager()->PointRaycast(pos, ccp(0,1), m_fAcceleration, &hit, 1, 1);
			pos.y += hit.Vdistance;
			m_fAcceleration -= 11.7f *dt;

			pos.y -= 46;
			BlockManager::sharedManager()->PointRaycast(pos, ccp(-1,0), 1.8f, &hit, 0, 1);

			if(m_fAcceleration < 0.1f)
				m_iState = WALK;
			pos.x -= hit.Hdistance;
		}

		if(m_iDirection == RIGHT)
		{
			pos.y += 46;

			BlockManager::sharedManager()->PointRaycast(pos, ccp(0,1), m_fAcceleration, &hit, 1, 1);
			pos.y += hit.Vdistance;
			m_fAcceleration -= 11.7f *dt;

			pos.y -= 46;
			BlockManager::sharedManager()->PointRaycast(pos, ccp(1,0),1.8f, &hit, 0, 2);

			if(m_fAcceleration < 0.1f)
				m_iState = WALK;
				
			pos.x += hit.Hdistance;
		}
	}

	this->setPosition( pos );
}