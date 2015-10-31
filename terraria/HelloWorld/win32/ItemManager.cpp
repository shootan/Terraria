#include "ItemManager.h"
#include "SoundManager.h"

void ItemManager::LoadInventory()
{
	Inventory = CCSprite::spriteWithFile("Item/Inventory.png");
	Inventory->setPosition(ccp(0, 600));
	Inventory->setAnchorPoint(ccp(0, 1));
	m_pScene->addChild(Inventory);

	SelectItemSprite = CCSprite::spriteWithFile("Item/SelectItemSprite.png");
	SelectItemSprite->setPosition(ccp(0,600));
	SelectItemSprite->setAnchorPoint(ccp(0,1));
	m_pScene->addChild(SelectItemSprite);

	Inventory2 = CCSprite::spriteWithFile("Item/OpenInventory.png");
	Inventory2->setPosition(ccp(0, 549));
	Inventory2->setAnchorPoint(ccp(0, 1));
	Inventory2->setIsVisible(false);
	m_pScene->addChild(Inventory2);

	Factory = CCSprite::spriteWithFile("Item/Factory.png");
	Factory->setPosition(ccp(971,523));
	Factory->setAnchorPoint(ccp(0,1));
	Factory->setIsVisible(false);
	m_pScene->addChild(Factory);

	for(int i=0; i<MAX_ITEM; i++)
	{
		m_pDropItem[i] = new Object_Item;
		m_pDropItem[i]->initWithItem();
		
		m_pScene->addChild(m_pDropItem[i]);
	}

	for(int i=0; i<5; i++)
	{
		m_pFactoryItem[i] = new Object_Item;
		m_pFactoryItem[i]->initWithItem();
		m_pFactoryItem[i]->setPosition(ccp(0,0));
		m_pFactoryItem[i]->setIsVisible(false);
		m_pScene->addChild(m_pFactoryItem[i]);
	}

	for(int i=0; i<5; i++)
	{
		for(int j=0; j<10; j++)
		{
			m_pItem[i][j] = new Object_Item;
			m_pItem[i][j]->initWithItem();
			m_pItem[i][j]->setPosition(ccp( 26+(52*j),574-52*i ));
			//m_pItem[i][j]->setItemIndex(rand()%4);
			if(i>0) m_pItem[i][j]->setIsVisible(false);
			m_pScene->addChild(m_pItem[i][j]);
		}
	}
	m_pItem[0][0]->setItemIndex(6);
	m_pItem[0][0]->Quantity++;
	m_pItem[0][0]->Update();
	m_pItem[0][1]->setItemIndex(1);
	m_pItem[0][1]->Quantity = 200;
	m_pItem[0][1]->Update();
	m_pMouseItem = new Object_Item;
	m_pMouseItem->initWithItem();
	m_pScene->addChild(m_pMouseItem);	
	AltCheck = false;
	m_fTime = 0.f;
	m_bSelectItem = true;
	SelectItem = 1;
	MakeItem = 0;
	BlockJ = 0;
	BlockI = 0;
}

void ItemManager::SetScene(CCNode* _scene)
{
	m_pScene = _scene;
}

void ItemManager::UpdateFactory()
{
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<10; j++)
		{
			if(m_pItem[i][j]->getItemIndex() == 0 ) continue;
			if(m_pItem[i][j]->getItemIndex() == 1)
			{
				BlockI = i;
				BlockJ = j;
				if(m_pItem[i][j]->Quantity >= 5)
				{
					m_pFactoryItem[0]->setItemIndex(2);
					m_pFactoryItem[0]->Quantity = 1;
				}
				if(m_pItem[i][j]->Quantity >= 10)
				{
					m_pFactoryItem[1]->setItemIndex(3);
					m_pFactoryItem[1]->Quantity = 1;
				}
				if(m_pItem[i][j]->Quantity < 5)
				{
					m_pFactoryItem[0]->Quantity = 0;
					m_pFactoryItem[0]->setItemIndex(0);
					m_pFactoryItem[1]->Quantity = 0;
					m_pFactoryItem[1]->setItemIndex(0);
					
				}
				
			}
			if(m_pItem[i][j]->getItemIndex() ==3)
			{
				StoneI = i;
				StoneJ = j;

				if(m_pItem[i][j]->Quantity >= 5)
				{
					m_pFactoryItem[2]->setItemIndex(4);
					m_pFactoryItem[2]->Quantity = 1;
				}
				if(m_pItem[i][j]->Quantity >= 10)
				{
					m_pFactoryItem[3]->setItemIndex(5);
					m_pFactoryItem[3]->Quantity = 1;
				}
				if(m_pItem[i][j]->Quantity < 5)
				{
					m_pFactoryItem[2]->Quantity = 0;
					m_pFactoryItem[2]->setItemIndex(0);
					m_pFactoryItem[3]->Quantity = 0;
					m_pFactoryItem[3]->setItemIndex(0);
					
				}
			}
		}
	}
	for(int i=0; i<5; i++)
	{
		m_pFactoryItem[i]->Update();
	}
}
void ItemManager::OpenInventory(ccTime dt)
{
	if(GetAsyncKeyState('I') && InvenCheck == false)
	{
		if(Inventory2->getIsVisible() == false)
		{
			Factory->setIsVisible(true);
			Inventory2->setIsVisible(true);
			
			for(int i=1; i<5; i++)
			{
				for(int j=0; j<10; j++)
					m_pItem[i][j]->setIsVisible(true);
			}
			for(int i=0; i<5; i++)
				m_pFactoryItem[i]->setIsVisible(true);

		}
		else if(Inventory2->getIsVisible() == true)
		{
			Factory->setIsVisible(false);
			Inventory2->setIsVisible(false);
			for(int i=1; i<5; i++)
			{
				m_pFactoryItem[i]->setIsVisible(false);
				for(int j=0; j<10; j++)
					m_pItem[i][j]->setIsVisible(false);
			}
			for(int i=0; i<5; i++)
				m_pFactoryItem[i]->setIsVisible(false);
		}
		InvenCheck = true;
	}
	if(!GetAsyncKeyState('I')) InvenCheck = false;

	CGPoint pos = SelectItemSprite->getPosition();
	m_fTime += dt;
	
	if(m_fTime > 0.4f)
	{
		m_bSelectItem = true;
	}
	
	if(m_bSelectItem)
	{
		if(GetAsyncKeyState('1'))
		{
			SelectItem = 1;
			SelectItemSprite->setPosition(ccp(0,pos.y));
			m_bSelectItem = false;
			m_fTime = 0.f;
			SoundManager::sharedManager()->play(SOUND_BUTTON);
		}
		if(GetAsyncKeyState('2'))
		{
			SelectItem = 2;
			SelectItemSprite->setPosition(ccp(52*(SelectItem-1),pos.y));
			m_bSelectItem = false;
			m_fTime = 0.f;
			SoundManager::sharedManager()->play(SOUND_BUTTON);
		}
		if(GetAsyncKeyState('3'))
		{
			SelectItem = 3;
			m_bSelectItem = false;
			SelectItemSprite->setPosition(ccp(52*(SelectItem-1),pos.y));
			m_fTime = 0.f;
			SoundManager::sharedManager()->play(SOUND_BUTTON);
		}
		if(GetAsyncKeyState('4'))
		{
			SelectItem = 4;
			m_bSelectItem = false;
			m_fTime = 0.f;
			SelectItemSprite->setPosition(ccp(52*(SelectItem-1),pos.y));
			SoundManager::sharedManager()->play(SOUND_BUTTON);
		}
		if(GetAsyncKeyState('5'))
		{
			SelectItem = 5;
			SoundManager::sharedManager()->play(SOUND_BUTTON);
			m_fTime = 0.f;
			m_bSelectItem = false;
			SelectItemSprite->setPosition(ccp(52*(SelectItem-1),pos.y));
		}
		if(GetAsyncKeyState('6'))
		{
			m_fTime = 0.f;
			SoundManager::sharedManager()->play(SOUND_BUTTON);
			SelectItem = 6;
			m_bSelectItem = false;
			SelectItemSprite->setPosition(ccp(52*(SelectItem-1),pos.y));
		}
		if(GetAsyncKeyState('7'))
		{
			m_fTime = 0.f;
			SoundManager::sharedManager()->play(SOUND_BUTTON);
			SelectItem = 7;
			m_bSelectItem = false;
			SelectItemSprite->setPosition(ccp(52*(SelectItem-1),pos.y));
		}
		if(GetAsyncKeyState('8'))
		{
			m_fTime = 0.f;
			SoundManager::sharedManager()->play(SOUND_BUTTON);
			SelectItem = 8;
			m_bSelectItem = false;
			SelectItemSprite->setPosition(ccp(52*(SelectItem-1),pos.y));
		}
		if(GetAsyncKeyState('9'))
		{
			m_fTime = 0.f;
			SoundManager::sharedManager()->play(SOUND_BUTTON);
			SelectItem = 9;
			m_bSelectItem = false;
			SelectItemSprite->setPosition(ccp(52*(SelectItem-1),pos.y));
		}
		if(GetAsyncKeyState('0'))
		{
			m_fTime = 0.f;
			SoundManager::sharedManager()->play(SOUND_BUTTON);
			SelectItem = 10;
			m_bSelectItem = false;
			SelectItemSprite->setPosition(ccp(52*(SelectItem-1),pos.y));
		}
	}
}

void ItemManager::UpdateItemBox(CGPoint _pos, ccTime dt)
{
	CGPoint MousePos = MouseManager::sharedManager()->GetMousePos();
	CGPoint MapPos = m_pScene->getPosition();

	MousePos.x -= MapPos.x;
	MousePos.y -= MapPos.y;

	m_pMouseItem->setPosition(MousePos);
	this->RootItem(_pos, dt);
	if(GetAsyncKeyState(VK_MENU)) AltCheck = true;
	else if(!GetAsyncKeyState(VK_MENU)) AltCheck = false;
}

void ItemManager::ClickItemBox()
{
	CGPoint MousePos = MouseManager::sharedManager()->GetMousePos();
	CGPoint MapPos = m_pScene->getPosition();

	MousePos.x -= MapPos.x;
	MousePos.y -= MapPos.y;

	if(Inventory2->getIsVisible()==true)
	{
		for(int i=0; i<5; i++)
		{
			if(m_pMouseItem->getItemIndex() > 0) break;

			CGPoint FactoryPos = m_pFactoryItem[i]->getPosition();
			if(FactoryPos.x-26 < MousePos.x && FactoryPos.x +26 > MousePos.x && FactoryPos.y-26 < MousePos.y
				&& FactoryPos.y+26 > MousePos.y)
			{
				if(m_pFactoryItem[i]->getItemIndex() == 2 || m_pFactoryItem[i]->getItemIndex() == 3)
				{
					m_pMouseItem->setItemIndex(m_pFactoryItem[i]->getItemIndex());
					m_pMouseItem->Quantity = 1;


					m_pItem[BlockI][BlockJ]->Quantity -= (i+1)*5;

					m_pItem[BlockI][BlockJ]->Update();
					m_pMouseItem->Update();
					m_pFactoryItem[i]->Update();
					this->UpdateFactory();
				}
				if(m_pFactoryItem[i]->getItemIndex() == 4 || m_pFactoryItem[i]->getItemIndex() == 5)
				{
					m_pMouseItem->setItemIndex(m_pFactoryItem[i]->getItemIndex());
					m_pMouseItem->Quantity = 1;

					int a = i%2;
					m_pItem[StoneI][StoneJ]->Quantity -= (a+1)*5;
					
					m_pItem[StoneI][StoneJ]->Update();
					m_pMouseItem->Update();
					m_pFactoryItem[i]->Update();
					this->UpdateFactory();
				}
			}
		}
		for(int i=0; i<5; i++)
			for(int j=0; j<10; j++)
			{
				CGPoint ItemPos = m_pItem[i][j]->getPosition();
				if(ItemPos.x-26 < MousePos.x && ItemPos.x +26 > MousePos.x && ItemPos.y-26 < MousePos.y
					&& ItemPos.y+26 > MousePos.y)
				{
					if(AltCheck == true)
					{
						if(m_pMouseItem->getItemIndex() == m_pItem[i][j]->getItemIndex())
						{
							m_pItem[i][j]->Quantity += m_pMouseItem->Quantity;
							m_pMouseItem->Quantity = 0;
							m_pMouseItem->setItemIndex(0);
							m_pMouseItem->Update();
							m_pItem[i][j]->Update();
							break;
						}
						if(m_pMouseItem->getItemIndex() == 0 && m_pItem[i][j]->Quantity != 1)
						{
							m_pMouseItem->setItemIndex(m_pItem[i][j]->getItemIndex());
							m_pMouseItem->Quantity =1;
							m_pItem[i][j]->Quantity--;
							m_pMouseItem->Update();
							m_pItem[i][j]->Update();
							break;
						}
						int index = m_pMouseItem->getItemIndex();
						int quantity = m_pMouseItem->Quantity;
						m_pMouseItem->setItemIndex(m_pItem[i][j]->getItemIndex());
						m_pMouseItem->Quantity = m_pItem[i][j]->Quantity;

						m_pItem[i][j]->setItemIndex(index);
						m_pItem[i][j]->Quantity = quantity;

						m_pMouseItem->Update();
						m_pItem[i][j]->Update();
						break;
					}
					else
					{
						if(m_pMouseItem->getItemIndex() == m_pItem[i][j]->getItemIndex())
						{
							m_pItem[i][j]->Quantity += m_pMouseItem->Quantity;
							m_pMouseItem->setItemIndex(0);
							m_pMouseItem->Quantity = 0;
							m_pMouseItem->Update();
							m_pItem[i][j]->Update();
							break;
						}
						int index = m_pMouseItem->getItemIndex();
						int quantity = m_pMouseItem->Quantity;
						m_pMouseItem->setItemIndex(m_pItem[i][j]->getItemIndex());
						m_pMouseItem->Quantity = m_pItem[i][j]->Quantity;

						m_pItem[i][j]->setItemIndex(index);
						m_pItem[i][j]->Quantity = quantity;

						m_pMouseItem->Update();
						m_pItem[i][j]->Update();
						break;
					}

				}
			}
	}
}

void ItemManager::DropItem(CGPoint _pos, int _index)
{
	_pos.x += 16;
	_pos.y += 16;
	for(int i=0; i<MAX_ITEM; i++)
	{
		if( m_pDropItem[i]->getItemIndex() != 0 ) continue;

		m_pDropItem[i]->setPosition(_pos);
		m_pDropItem[i]->setItemIndex(_index);
		break;
	}
}

void ItemManager::RootItem(CGPoint _pos, ccTime dt)
{
	_pos.y+= 20;
	for(int i=0; i<MAX_ITEM; i++)
	{
		if(m_pDropItem[i]->itemIndex == 0) continue;
		
		CGPoint pos = m_pDropItem[i]->getPosition();
		float fDistance = MouseManager::sharedManager()->GetDistance(pos, _pos);
		if(fDistance<100.f)
		{
			CGPoint vec = MouseManager::sharedManager()->GetVector(pos, _pos);

			pos.x -= vec.x * 300.f * dt;
			pos.y -= vec.y * 300.f * dt;

			m_pDropItem[i]->setPosition(pos);
		}

		if(fDistance< 5.f)
		{
			SoundManager::sharedManager()->play(SOUND_ROOT);
			for(int j=0; j<5; j++)
				for(int z=0; z<10; z++)
				{
					
					if(m_pItem[j][z]->getItemIndex() == m_pDropItem[i]->getItemIndex())
					{
						m_pItem[j][z]->Quantity++;
						m_pItem[j][z]->Update();
						m_pDropItem[i]->setItemIndex(0);
						break;
					}

					if(m_pItem[j][z]->getItemIndex() != 0 ) continue;

					int index = m_pDropItem[i]->getItemIndex();
					m_pDropItem[i]->setItemIndex(0);
					m_pItem[j][z]->setItemIndex(index);
					m_pItem[j][z]->Quantity = 1;
					m_pItem[j][z]->Update();


					break;
				}
		}
		m_pDropItem[i]->Update();
	}
}
