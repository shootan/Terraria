#pragma once
#include "cocos2d.h"
using namespace cocos2d;

#include "Object.h"

#define	MAX_BLOCK_X		300
#define	MAX_BLOCK_Y		30

struct Block
{
	int		index;
	int		Number;
	float	fDinstance;
	float	eDistance;
	CGRect	rc;
	bool	Active;
	int		LiveFlag;
	bool	Close;
	bool	EnemyClose;
	int		EnemyCloseIndex;
	int		CloseIndex;
	bool	AttackRange;
	int		Color;
};

class Object_block : public Object
{
public:
	bool	initWithBlock();
	void	addBlock(CGPoint _pos);
	Block	m_Block[MAX_BLOCK_Y][MAX_BLOCK_X];

protected:

};

