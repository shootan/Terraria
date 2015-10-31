#include "BlockManager.h"
#include "ItemManager.h"
#include "RenderingManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"

void BlockManager::loadResource()
{
	CHAR szTemp[128] = {0};
	CCAnimation* Ani = new CCAnimation;

	m_pBgaSprite = CCSprite::spriteWithTexture(ResourceManager::sharedManager()->getMap(67));
	m_pBgaSprite->setAnchorPoint(ccp(0,0));
	m_pBgaSprite->setPosition(ccp(-1000,-1000));
	m_pGround->addChild(m_pBgaSprite);

	Ani->initWithName("TILE");

	for(int i=0; i<6; i++)
	{
		sprintf_s(szTemp, "Tile/Tile_Ground_%d.png",i);
		Ani->addFrameWithFileName(szTemp);
	}

	m_pBlockSprite = new CCSprite;
	m_pBlockSprite->init();
	m_pBlockSprite->setAnchorPoint(ccp(0,0));
	m_pBlockSprite->addAnimation(Ani);
	m_pBlockSprite->setIsVisible(false);
	m_pBlockSprite->setPosition(ccp(-1000,-1000));
	m_pGround->addChild(m_pBlockSprite);

	m_bLoaded = true;
	m_bLook	 = false;

	m_pBlock = new Object_block;
	m_pBlock->initWithBlock();
}

void BlockManager::SetBlockColor()
{

	bool change;
	for(int i=0; i<MAX_BLOCK_X; i++)
	{
		change = false;

		for(int j=0; j<MAX_BLOCK_Y; j++)
		{
			if(m_pBlock->m_Block[j][i].LiveFlag == 0)
			{
				for(int z = 0; z < 11; z++)
				{
					if(j-z-1 < 0) break;
					m_pBlock->m_Block[(j-1)-z][i].Color = z;
				}
				change = true;
				break;
			}
		}

		if(change == false)
		{
			for(int a = 0; a < 11; a++)
			{
				m_pBlock->m_Block[(MAX_BLOCK_Y-1)-a][i].Color = a;
			}
		}
	}

}

void BlockManager::Rendering()
{
	CGPoint pos = m_pGround->getPosition();
	m_pBlockSprite->setIsVisible(true);
	for(int i = 0; i<MAX_BLOCK_Y; i++)
	{
		for(int j=0; j<MAX_BLOCK_X; j++)
		{
			if(m_pBlock->m_Block[i][j].Active == true)
			{
				m_pBlockSprite->setDisplayFrame("TILE", m_pBlock->m_Block[i][j].index);
				m_pBlockSprite->setPosition(ccp(m_pBlock->m_Block[i][j].rc.origin.x, m_pBlock->m_Block[i][j].rc.origin.y ));
				int a ;
				switch(m_pBlock->m_Block[i][j].Color)
				{
				case 0:
					a = 255 - m_pBlock->m_Block[i][j].Color * 25;
					m_pBlockSprite->setColor(ccc3(a,a,a));
					break;
				case 1:
					a = 255 - m_pBlock->m_Block[i][j].Color * 25;
					m_pBlockSprite->setColor(ccc3(a,a,a));
					break;
				case 2:
					a = 255 - m_pBlock->m_Block[i][j].Color * 25;
					m_pBlockSprite->setColor(ccc3(a,a,a));
					break;
				case 3:
					a = 255 - m_pBlock->m_Block[i][j].Color * 25;
					m_pBlockSprite->setColor(ccc3(a,a,a));
					break;
				case 4:
					a = 255 - m_pBlock->m_Block[i][j].Color * 25;
					m_pBlockSprite->setColor(ccc3(a,a,a));
					break;
				case 5:
					a = 255 - m_pBlock->m_Block[i][j].Color * 25;
					m_pBlockSprite->setColor(ccc3(a,a,a));
					break;
				case 6:
					a = 255 - m_pBlock->m_Block[i][j].Color * 25;
					m_pBlockSprite->setColor(ccc3(a,a,a));
					break;
				case 7:
					a = 255 - m_pBlock->m_Block[i][j].Color * 25;
					m_pBlockSprite->setColor(ccc3(a,a,a));
					break;
				case 8:
					a = 255 - m_pBlock->m_Block[i][j].Color * 25;
					m_pBlockSprite->setColor(ccc3(a,a,a));
					break;
				case 9:
					a = 255 - m_pBlock->m_Block[i][j].Color * 25;
					m_pBlockSprite->setColor(ccc3(a,a,a));
					break;
				case 10:
					a = 255 - m_pBlock->m_Block[i][j].Color * 25;
					m_pBlockSprite->setColor(ccc3(a,a,a));
					break;
				}

				m_pBlockSprite->visit();
			}
		}
	}
	m_pBlockSprite->setIsVisible(false);
}

void BlockManager::setGround(CCNode *_ground)
{
	m_pGround = _ground;
	WinRect.origin = m_pGround->getPosition();
	WinRect.size.height = CCDirector::sharedDirector()->getWinSize().height;
	WinRect.size.width = CCDirector::sharedDirector()->getWinSize().width;
}

int BlockManager::attackBlock(CGPoint _pos)
{
	SoundManager::sharedManager()->play(SOUND_ATTACK);
	for(int i = 0; i < MAX_BLOCK_Y; i++)
	{
		for(int j=0; j<MAX_BLOCK_X; j++)
		{
			if(m_pBlock->m_Block[i][j].AttackRange == false) continue;

			CGRect block = m_pBlock->m_Block[i][j].rc;

			if(block.origin.x < _pos.x && block.origin.x+block.size.width > _pos.x && block.origin.y < _pos.y 
				&& block.origin.y + block.size.height > _pos.y)
			{
				SoundManager::sharedManager()->play(SOUND_DIG);
				if(m_pBlock->m_Block[i][j].LiveFlag > 0)
				{
					if(ItemManager::sharedManager()->GetSelectItemIndex()==6)
					{
						m_pBlock->m_Block[i][j].LiveFlag -= 1;
						if(m_pBlock->m_Block[i][j].LiveFlag < 1)
						{
							
							CGPoint pos = m_pBlock->m_Block[i][j].rc.origin;
							ItemManager::sharedManager()->DropItem(pos, 1);
							pos.x += 16;
							pos.y += 16;

							Particle(pos);

							//m_pBlockSprite[m_pBlock->m_Block[i][j].Number]->setIsVisible(false);

							m_pBlock->m_Block[i][j].Active = false;
							m_pBlock->m_Block[i][j].Close = false;
							m_pBlock->m_Block[i][j].EnemyClose = false;

							//m_pBlockSprite[m_pBlock->m_Block[i][j].Number]->setIsVisible(false);
							//m_pBlockSprite[m_pBlock->m_Block[i][j].Number]->setPosition(ccp(0,0));

							CloseBlock[m_pBlock->m_Block[i][j].CloseIndex] =NULL;
							EnemyBlock[m_pBlock->m_Block[i][j].EnemyCloseIndex] =NULL;
							break;
						}
					}
				}
				else
				{
					if(ItemManager::sharedManager()->GetSelectItemIndex()==1)
					{
						m_pBlock->m_Block[i][j].LiveFlag = 1;	
						ItemManager::sharedManager()->ReduceItemCount();
					}
				}
				return i;
			}
		}
	}
	return false;
}


void BlockManager::setBlock(Object_block* _block)
{
	m_pBlock = _block;
}

int BlockManager::CheckCloseBlock(CGPoint _pos, CCNode* _bga)
{
	m_bLook = false;
	WinRect.origin.x = -(_bga->getPosition().x);
	WinRect.origin.y = -(_bga->getPosition().y);

	CGPoint Pos = m_pEnemy->getPosition();

	for (int i=0; i<MAX_BLOCK_Y; i++)
	{
		for(int j=0; j<MAX_BLOCK_X; j++)
		{
			if(m_pBlock->m_Block[i][j].LiveFlag < 1) continue;

			CGPoint vec = ccp(_pos.x - m_pBlock->m_Block[i][j].rc.origin.x,
				_pos.y - m_pBlock->m_Block[i][j].rc.origin.y);

			m_pBlock->m_Block[i][j].fDinstance = sqrtf( vec.x * vec.x + vec.y * vec.y );
			
			if(m_pBlock->m_Block[i][j].fDinstance <  100.f) m_pBlock->m_Block[i][j].AttackRange = true;
			else m_pBlock->m_Block[i][j].AttackRange = false;

			if(m_pBlock->m_Block[i][j].Active == false)
			{
				if(CGRect::CGRectIntersectsRect(WinRect, m_pBlock->m_Block[i][j].rc))
				{
					m_pBlock->m_Block[i][j].Active = true;
					m_bLook = true;
				}
			}
			else
			{
				if(!CGRect::CGRectIntersectsRect(WinRect, m_pBlock->m_Block[i][j].rc))
				{
					m_pBlock->m_Block[i][j].Active=false;
				}
			}

			if(m_pBlock->m_Block[i][j].Active==true)
			{
				for(int z=0; z<20; z++)
				{
					if(CloseBlock[z] == NULL)
					{
						if(m_pBlock->m_Block[i][j].Close == true) continue;
						CloseBlock[z] = &m_pBlock->m_Block[i][j];
						m_pBlock->m_Block[i][j].Close = true;
						m_pBlock->m_Block[i][j].CloseIndex = z;
						break;
					}
					else if( CloseBlock[z]->fDinstance > m_pBlock->m_Block[i][j].fDinstance )
					{
						if(m_pBlock->m_Block[i][j].Close == true) continue;
						CloseBlock[z]->Close = false;
						CloseBlock[z]->CloseIndex = 21;
						CloseBlock[z] = &m_pBlock->m_Block[i][j];
						m_pBlock->m_Block[i][j].Close = true;
						m_pBlock->m_Block[i][j].CloseIndex = z;
						break;
					}
				}
			}

			vec = ccp(Pos.x - m_pBlock->m_Block[i][j].rc.origin.x,
				Pos.y - m_pBlock->m_Block[i][j].rc.origin.y);

			m_pBlock->m_Block[i][j].eDistance = sqrtf( vec.x * vec.x + vec.y * vec.y );

			for(int a= 0; a < 14; a ++)
			{
				if(EnemyBlock[a] == NULL)
				{
					if(m_pBlock->m_Block[i][j].EnemyClose == true) continue;
					EnemyBlock[a] = &m_pBlock->m_Block[i][j];
					m_pBlock->m_Block[i][j].EnemyClose = true;
					m_pBlock->m_Block[i][j].EnemyCloseIndex = a;
					break;
				}
				else if( EnemyBlock[a]->eDistance > m_pBlock->m_Block[i][j].eDistance )
				{
					if(m_pBlock->m_Block[i][j].EnemyClose == true) continue;
					EnemyBlock[a]->EnemyClose = false;
					EnemyBlock[a]->EnemyCloseIndex = 15;
					EnemyBlock[a] = &m_pBlock->m_Block[i][j];
					m_pBlock->m_Block[i][j].EnemyClose = true;
					m_pBlock->m_Block[i][j].EnemyCloseIndex = a;
					break;
				}
			}
		}
	}

	if(m_bLook==true)	return 1;
	else				return 0;
}

void BlockManager::PaintSprite(int _indexX, int _indexY)
{
		m_pBlockSprite->setDisplayFrame("TILE", m_pBlock->m_Block[_indexY][_indexX].index);
		m_pBlockSprite->setPosition(ccp(m_pBlock->m_Block[_indexY][_indexX].rc.origin.x, m_pBlock->m_Block[_indexY][_indexX].rc.origin.y));
		m_pBlockSprite->visit();

	/*for(int i=0; i<MAX_BLOCK; i++)
	{
		if( m_pBlock->m_Block[i].Active == true )
		{
			for(int j=0; j<30; j++)
			{
				if(m_pBlockSprite[j]->getIsVisible() == true) continue;
				m_pBlockSprite[j]->setIsVisible(true);
				m_pBlockSprite[j]->setPosition(m_pBlock->m_Block[i].rc.origin);
				m_pBlock->m_Block[i].Number = j;
				m_pBlockSprite[j]->setDisplayFrame("TILE", m_pBlock->m_Block[i].index);
				break;
			}
		}
	}*/
}

void BlockManager::Raycast(CGRect _rc, CGPoint _vec, float _distance, raycast* _ray, int _dir, int _type)
{
	float detail = 0.1f;
	if(_dir == 0)
	{
		for( _ray->Hdistance = 0 ; _ray->Hdistance < _distance ; _ray->Hdistance+=detail )
		{
			int index = CollisionChack(_rc, _type);

			if( index > -1 ) 
			{
				_ray->Hdistance -= detail;
				return;
			}
			_rc.origin.x += _vec.x * detail;	
		}
	}
	if(_dir == 1)
	{
		for( _ray->Vdistance = 0 ; _ray->Vdistance < _distance ; _ray->Vdistance+=detail )
		{
			int index = CollisionChack(_rc, _type);

			if( index > -1 ) 
			{
				_ray->Vdistance -= detail;
				//_ray->m_pBlock = m_pBlock[index];
				return;
			}
			_rc.origin.y += _vec.y * detail;
		}
	}	
}

int BlockManager::CollisionChack(CGRect _rc, int _type)
{
	if(_type==1)
	{
		for( int i = 0 ; i < 20 ; i++ )
		{
			if(CloseBlock[i] == NULL) continue;
			if(CGRect::CGRectIntersectsRect( _rc, CloseBlock[i]->rc ))
				return i;
		}
	}
	
	return -1;
}

void BlockManager::PointRaycast(CGPoint _pos, CGPoint _vec, float _distance, raycast* _ray, int _dir, int _type)
{
	float detail = 0.1f;

	if(_dir == 0)
	{
		if(_type == 1)
		{
			_pos.y += 5;
			for( _ray->Hdistance = 0 ; _ray->Hdistance < _distance ; _ray->Hdistance+=detail )
			{
				int index = PointCollisionChack(_pos, _type);

				if( index > -1 ) 
				{
					_ray->Hdistance -= detail;
					return;
				}
				_pos.x += _vec.x * detail;	
			}
		}
		if(_type ==2)
		{
			_pos.y += 5;
			_pos.x += 36;
			for( _ray->Hdistance = 0 ; _ray->Hdistance < _distance ; _ray->Hdistance+=detail )
			{
				int index = PointCollisionChack(_pos, _type);

				if( index > -1 ) 
				{
					_ray->Hdistance -= detail;
					return;
				}
				_pos.x += _vec.x * detail;	
			}
		}
		
	}
	if(_dir == 1)
	{
		if(_type == 1)
		{
			_pos.x += 13;
			for( _ray->Vdistance = 0 ; _ray->Vdistance < _distance ; _ray->Vdistance+=detail )
			{
				int index = PointCollisionChack(_pos, _type);

				if( index > -1 ) 
				{
					_ray->Vdistance -= detail;
					//_ray->m_pBlock = m_pBlock[index];
					return;
				}
				_pos.y += _vec.y * detail;
			}
		}
		if(_type == 2)
		{	
			_pos.x += 25;
			for( _ray->Vdistance = 0 ; _ray->Vdistance < _distance ; _ray->Vdistance+=detail )
			{
				int index = PointCollisionChack(_pos, _type);

				if( index > -1 ) 
				{
					_ray->Vdistance -= detail;
					//_ray->m_pBlock = m_pBlock[index];
					return;
				}
				_pos.y += _vec.y * detail;
			}
		}
		
	}
}

int BlockManager::PointCollisionChack(CGPoint _pos, int _type)
{
	for( int i = 0 ; i < 14 ; i++ )
	{
		if(EnemyBlock[i] == NULL) continue;
		if(CGRect::CGRectContainsPoint( EnemyBlock[i]->rc, _pos ))
			return i;
	}
	return -1;
}

void BlockManager::Particle(CGPoint _pos)
{
	CCParticleSystemQuad* particle;
	particle = new CCParticleSystemQuad;
	particle->initWithTotalParticles(600);
	particle->autorelease();

	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("Tile/Tile_Ground_2.png");

	particle->setTexture(texture);
	particle->setEmissionRate(296.43);
	particle->setAngle(90.0);
	particle->setAngleVar(36.2);
	ccBlendFunc blendFunc={GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA};
	particle->setBlendFunc(blendFunc);
	particle->setDuration(0.10);
	particle->setEmitterMode(kCCParticleModeGravity);

	ccColor4F startColor={1.00,1.00,1.00,1.00};
	particle->setStartColor(startColor);

	ccColor4F startColorVar={0.00,0.00,0.00,0.00};
	particle->setStartColorVar(startColorVar);

	ccColor4F endColor={1.00,1.00,1.00,0.55};
	particle->setEndColor(endColor);

	ccColor4F endColorVar={0.00,0.00,0.00,0.00};
	particle->setEndColorVar(endColorVar);

	particle->setStartSize(6.03);
	particle->setStartSizeVar(0.00);
	particle->setEndSize(-1.00);
	particle->setEndSizeVar(0.00);
	particle->setGravity(ccp(0.00, -1837.19));
	particle->setRadialAccel(0.00);
	particle->setRadialAccelVar(0.00);
	particle->setSpeed(234);
	particle->setSpeedVar(300);
	particle->setTangentialAccel(0);
	particle->setTangentialAccelVar(0);
	particle->setTotalParticles(501);
	particle->setLife(1.69);
	particle->setLifeVar(0.10);
	particle->setStartSpin(0.00);
	particle->setEndSpin(0.00);
	particle->setEndSpinVar(0.00);
	particle->setPosition(_pos);
	particle->setPosVar(ccp(10.00,0.00));

	m_pGround->addChild(particle);

}