#include "Object_block.h"

bool Object_block::initWithBlock()
{
	int y = 0;

	for( int i = 0 ; i < MAX_BLOCK_Y ; i++ )
	{
		for(int j=0; j<MAX_BLOCK_X; j++)
		{
			m_Block[i][j].rc.origin = ccp(32*j, 32*i);
			m_Block[i][j].rc.size = CGSizeMake(32, 32);
			m_Block[i][j].fDinstance = 250.f;
			m_Block[i][j].eDistance = 250.f;
			m_Block[i][j].Active = false;
			m_Block[i][j].Number = 0;
			m_Block[i][j].LiveFlag = 1;
			m_Block[i][j].Close = false;
			m_Block[i][j].EnemyClose = false;
			m_Block[i][j].EnemyCloseIndex = 15;
			m_Block[i][j].CloseIndex = 21;
			m_Block[i][j].AttackRange = false;
			m_Block[i][j].Color  = 10;
			if(i == MAX_BLOCK_Y-1)
				m_Block[i][j].index = 0;
			else m_Block[i][j].index = rand()%4+2;
		}
	}
	return true;
}

void Object_block::addBlock(CGPoint _pos)
{
	

}