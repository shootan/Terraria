#pragma once
#include "cocos2d.h"
using namespace cocos2d;

#include "Object_block.h"
#include "Object_Enemy.h"

#define		MAX_SPRITE		800

struct raycast
{
	float Vdistance;
	float Hdistance;
	Object_block* m_pBlock;
};

class BlockManager
{
private:
	BlockManager()
	{
		memset(CloseBlock, NULL, sizeof(CloseBlock));
		memset(EnemyBlock, NULL, sizeof(EnemyBlock));
		memset(RenderingBlock, NULL, sizeof(RenderingBlock));
		m_bLoaded = false;
		m_pGround =	 NULL;
	}
	~BlockManager()
	{
		delete instance;
		instance = NULL;
		delete[] m_pBlockSprite;
		memset(CloseBlock, NULL, sizeof(CloseBlock));
		memset(RenderingBlock, NULL, sizeof(RenderingBlock));
	}
	
	bool			m_bLoaded;
	
	CCTexture2D*	m_pTexture[13];
	CCNode*			m_pGround;
	Object_block*	m_pBlock;
	CCRenderTexture* m_pRender;
	Block* CloseBlock[21];
	Block* EnemyBlock[15];
	Block* RenderingBlock[600];
	CGRect WinRect;
	CCSprite*		m_pBlockSprite;
	bool			m_bLook;
	CCSprite*		m_pBgaSprite;

public:
	static BlockManager* instance;
	static BlockManager* sharedManager()
	{
		if( instance == NULL ) instance = new BlockManager;
		return instance;
	}

	void loadResource();

	void SetRender(CCRenderTexture* _Render)
	{
		m_pRender = _Render;
	}

	void setGround(CCNode *_ground);
	void setBlock(Object_block* _block);
	void SetBlockColor();
	int attackBlock(CGPoint _pos);
	void Rendering();
	int CheckCloseBlock(CGPoint _pos, CCNode* _bga);

	void PaintSprite(int _indexX, int _indexY);

	int CollisionChack(CGRect _rc, int _type);
	void Raycast(CGRect _rc, CGPoint _vec, float _distance, raycast* _ray, int _dir, int _type);

	int PointCollisionChack(CGPoint _pos, int _type);
	void PointRaycast(CGPoint _pos, CGPoint _vec, float _distance, raycast* _ray, int _dir, int _type);

	void Particle(CGPoint _pos);

	Object_Enemy* m_pEnemy;
	void SetEnemy(Object_Enemy* _enemy)
	{
		m_pEnemy = _enemy;
	}


};