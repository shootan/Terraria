#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#include "Object_Item.h"
#include "MouseManager.h"

#define		MAX_ITEM	20

class ItemManager
{
private:
	ItemManager()
	{
		m_pScene = NULL;
		instance = NULL;
		Inventory = NULL;
		Inventory2 = NULL;
		InvenCheck = false;
		for(int i=0; i<5; i++)
		{
			memset(m_pItem[i], NULL, sizeof(m_pItem[i]));
		}
		memset(m_pDropItem, NULL, sizeof(m_pDropItem));
	}

	~ItemManager()
	{
		delete instance;
		instance = NULL;
		
		delete[] m_pDropItem;
		memset(m_pDropItem, NULL, sizeof(m_pDropItem));

		for(int i=0; i<5; i++)
		{
			delete[] m_pItem[i];
			memset(m_pItem[i], NULL, sizeof(m_pItem[i]));
		}
	}


public:
	static ItemManager* instance;
	static ItemManager* sharedManager()
	{
		if( instance == NULL ) instance = new ItemManager;
		return instance;
	}

	void LoadInventory();
	void SetScene(CCNode* _scene);
	void OpenInventory(ccTime dt);
	void UpdateItemBox(CGPoint _pos, ccTime dt);
	void FindItem(CGPoint pos);
	void ClickItemBox();
	bool CheckOpen()
	{
		if(Inventory2->getIsVisible()==true) return true;
		return false;
	}
	void DropItem(CGPoint _pos, int _index);
	void RootItem(CGPoint _pos, ccTime dt);
	void SetInventoryPos(CGPoint _pos)
	{
		CGPoint InvenPos = Inventory->getPosition();
		InvenPos.x = -_pos.x;
		InvenPos.y = -_pos.y + 600.f;
		Inventory->setPosition(InvenPos);

		InvenPos = Inventory2->getPosition();
		InvenPos.x = -_pos.x;
		InvenPos.y = -_pos.y + 549.f;
		Inventory2->setPosition(InvenPos);

		InvenPos = SelectItemSprite->getPosition();
		InvenPos.x = -_pos.x + ((SelectItem-1)*52);
		InvenPos.y = -_pos.y + 600.f;
		SelectItemSprite->setPosition(InvenPos);

		InvenPos = Factory->getPosition();
		InvenPos.x = -_pos.x + 971.f;
		InvenPos.y = -_pos.y + 523.f;
		Factory->setPosition(InvenPos);

		for(int i=0; i<5; i++)
		{
			for(int j=0; j<10; j++)
			{
				m_pItem[i][j]->setPosition(ccp( -_pos.x + 26 +(52*j),-_pos.y + 574 - (52*i) ));
			}
		}

		for(int i=0; i<5; i++)
		{
			m_pFactoryItem[i]->setPosition(ccp(-_pos.x + 997, -_pos.y + 497 - (52*i)));
		}
	}

	void ReduceItemCount()
	{
		if(m_pItem[0][SelectItem-1]->getItemIndex() >3) return;
		if(!m_pItem[0][SelectItem-1]->ReduceCount())
			m_pItem[0][SelectItem-1]->setItemIndex(0);
	}
	int GetSelectItemIndex()
	{
		return m_pItem[0][SelectItem-1]->getItemIndex();
	}
	void UpdateFactory();

public:
	CCSprite*		Inventory;
	CCSprite*		Inventory2;
	CCSprite*		Factory;
	CCSprite*		SelectItemSprite;
	bool			InvenCheck;
	CCNode*			m_pScene;
	Object_Item*	m_pItem[5][10];
	Object_Item*	m_pMouseItem;
	Object_Item*	m_pDropItem[MAX_ITEM];
	Object_Item*	m_pFactoryItem[5];

	bool			m_bSelectItem;
	float			m_fTime;
	bool			AltCheck;
	int				SelectItem;
	int				MakeItem;
	int				BlockI;
	int				BlockJ;
	int				StoneI;
	int				StoneJ;
};