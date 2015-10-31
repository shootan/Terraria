#include "Object_Item.h"
#include "ResourceManager.h"

void Object_Item::initWithItem()
{
	itemIndex = 0;

	CHAR szTemp[128] = {0};

	Quantity = 0;

	m_debug = CCLabelTTF::labelWithString("none", "Arial", 13.f);
	m_debug->setAnchorPoint(ccp(0.5,0.5));
	m_debug->setColor(ccc3(255,255,255));
	m_debug->setPosition(ccp(14, -14));
	m_debug->setIsVisible(false);
	this->addChild(m_debug);

	m_pItem = new CCSprite;
	m_pItem->init();
	m_pItem->addAnimation(ResourceManager::sharedManager()->GetItemAni());
	m_pItem->setDisplayFrame("ITEM", itemIndex);

	CGSize size = CGSizeMake(52,52);
	m_cgBoundSize = size;

	this->addChild(m_pItem);
}

void Object_Item::Update()
{
	CHAR szTemp[128] = {0};
	if(itemIndex == 0)
	{
		Quantity = 0;
		m_debug->setIsVisible( false);
	}

	if(Quantity > 0)
	{
		m_debug->setIsVisible(true);
		m_pItem->setIsVisible(true);
		sprintf_s(szTemp, "%d", Quantity);
		m_debug->setString(szTemp);
	}
	else
	{
		m_pItem->setIsVisible(false);
		m_debug->setIsVisible(false);
	}
}