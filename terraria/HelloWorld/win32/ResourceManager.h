#pragma once
#include "cocos2d.h"
using namespace cocos2d;

typedef struct Animation{
	char* Name;
	CCAnimation* pAni;
	bool Loaded;
}Ani;

class ResourceManager
{
private:
	ResourceManager()
	{
		MapCount= 0;
		for(int i=0; i<4; i++)
		{
			HeroAni[i].Name = "HERO";
			HeroAni[i].Loaded = false;
		}
		
		Count = -1;

		ItemAni.Name = "ITEM";
		ItemAni.Loaded = false;
	}
	~ResourceManager()
	{
		delete instance;
		instance = NULL;	
	}

	int Count;
	int MapCount;

	CCTexture2D*	m_pMap[183];
	Ani				HeroAni[4];
	Ani				EnemyAni;
	Ani				ItemAni;

public:
	static ResourceManager* instance;
	static ResourceManager* sharedManager()
	{
		if( instance == NULL ) instance = new ResourceManager;
		return instance;
	}


	CCTexture2D* getMap(int index)
	{
		return m_pMap[index];
	}

	void LoadMap()
	{
		char Text[125] = {0};
		if(MapCount< 180)
		{
			for(int i=MapCount; i<MapCount+20; i++)
			{
				sprintf_s(Text,"BGA/Background_%d.png",i);
				m_pMap[i] = CCTextureCache::sharedTextureCache()->addImage(Text);
				m_pMap[i]->setAliasTexParameters();
			}
		}
		else
		{
			for(int i=MapCount; i<183; i++)
			{
				sprintf_s(Text,"BGA/Background_%d.png",i);
				m_pMap[i] = CCTextureCache::sharedTextureCache()->addImage(Text);
				m_pMap[i]->setAliasTexParameters();
			}
		}
		MapCount += 20;
	}

	CCAnimation* GetHeroAni(int index)
	{
		return HeroAni[index].pAni;
	}

	void LoadItem()
	{
		char szTemp[125] = {0};
		ItemAni.pAni = new CCAnimation;
		ItemAni.pAni->initWithName("ITEM");
		for(int i=0; i<7; i++)
		{
			sprintf_s(szTemp, "Item/Item_%d.png",i);
			ItemAni.pAni->addFrameWithFileName(szTemp);
		}
		ItemAni.Loaded = true;
	}

	CCAnimation* GetItemAni()
	{
		return ItemAni.pAni;
	}

	CCTexture2D* GetMapTexture(int index)
	{
		return m_pMap[index];
	}

	CGSize GetMapSize(int index)
	{
		return m_pMap[index]->getContentSize();
	}
	void LoadHero()
	{
		char szTemp[125] = {0};
		HeroAni[0].pAni = new CCAnimation;
		HeroAni[0].pAni->initWithName("IDLE");
		HeroAni[0].pAni->addFrameWithFileName("terraria/HERO_WALK_5.png");
		HeroAni[0].Loaded = true;

		HeroAni[1].pAni = new CCAnimation;
		HeroAni[1].pAni->initWithName("WALK");
		for(int i=0; i<14; i++)
		{
			sprintf_s(szTemp, "terraria/HERO_WALK_%d.png", i);
			HeroAni[1].pAni->addFrameWithFileName(szTemp);
		}
		HeroAni[1].Loaded = true;

		HeroAni[2].pAni = new CCAnimation;
		HeroAni[2].pAni->initWithName("ATTACK");
		for(int i=0; i<5; i++)
		{
			sprintf_s(szTemp, "terraria/HERO_ATTACK_%d.png", i);
			HeroAni[2].pAni->addFrameWithFileName(szTemp);
		}
		HeroAni[2].Loaded = true;

		HeroAni[3].pAni = new CCAnimation;
		HeroAni[3].pAni->initWithName("JUMP");
		HeroAni[3].pAni->addFrameWithFileName("terraria/HERO_JUMP_0.png");
		HeroAni[3].Loaded = true;
		
	}

	int AllLoading()
	{
		switch(Count)
		{
		case -1:
			{
				this->LoadMap();
				Count++;
				return Count;
			}
		case 0:
			{
				this->LoadMap();
				Count++;
				return Count;
			}
		case 1:
			{
				this->LoadMap();
				Count++;
				return Count;
			}
		case 2:
			{
				this->LoadMap();
				Count++;
				return Count;
			}
		case 3:
			{
				this->LoadMap();
				Count++;
				return Count;
			}
		case 4:
			{
				this->LoadMap();
				Count++;
				return Count;
			}
		case 5:
			{
				this->LoadMap();
				Count++;
				return Count;
			}
		case 6:
			{
				this->LoadMap();
				Count++;
				return Count;
			}
		case 7:
			{
				this->LoadMap();
				Count++;
				return Count;
			}
		case 8:
			{
				this->LoadMap();
				Count++;
				return Count;
			}
		case 9:
			{
				this->LoadHero();
				Count++;
				return Count;
			}
		case 10:
			{
				this->LoadItem();
				Count++;
				return Count;
			}
		}
	}	
};