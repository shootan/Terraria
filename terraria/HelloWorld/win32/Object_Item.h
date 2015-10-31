#pragma once
#include "cocos2d.h"
using namespace cocos2d;

#include "Object.h"

class Object_Item : public Object
{
public:
	void initWithItem();
	void Update();
	int getItemIndex()
	{
		return itemIndex;
	}
	void setItemIndex(int _index)
	{
		itemIndex = _index;
		m_pItem->setDisplayFrame("ITEM", itemIndex);
	}
	bool ReduceCount()
	{
		Quantity--;
		if(Quantity ==0)
		{
			this->Update();
			return false;
		}
		else
		{
			this->Update();
			return true;
		}
	}
	
public:
	CCSprite* m_pItem;
	int itemIndex;
	CCLabelTTF* m_debug;
	int Quantity;

};