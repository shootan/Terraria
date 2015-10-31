#include <math.h>
#include "Scene_Play.h"
#include "SoundManager.h"
#include "EnemyManager.h"


CCScene* Scene_Play::scene()
{
	CCScene *scene = CCScene::node();

	Scene_Play *layer = Scene_Play::node();
	
	scene->addChild(layer);

	return scene;
}

bool Scene_Play::init()
{
	if(!CCLayer::init()) return false;
	this->setIsTouchEnabled(true);
	this->setPosition(ccp(0,-600));
	cgDynamicTracking = ccp(0,-600);
	BlockIndex = 0;

	SoundManager::sharedManager()->stop(SOUND_MAIN_BGM);
	SoundManager::sharedManager()->play(SOUND_GAME_BGM);
	
	ObjectCore::sharedManager()->SetScene(this);
	ObjectCore::sharedManager()->initObject();

	m_debug = CCLabelTTF::labelWithString("none", "Arial", 15.f);
	m_debug->setAnchorPoint(ccp(0.5,0));
	m_debug->setColor(ccc3(0,0,255));
	m_debug->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, 0));
	this->addChild(m_debug);

	this->schedule(schedule_selector(Scene_Play::tick));

	return true;
}

void Scene_Play::tick(ccTime dt)
{
	this->SceneScroll(dt);
	this->DebugScreen();

	ObjectCore::sharedManager()->tick(dt);
	
}

void Scene_Play::ccTouchesBegan(NSSet *pTouches, UIEvent *pEvent)
{
	CCTouch* pT = (CCTouch*)pTouches->anyObject();
	CGPoint p = pT->locationInView( pT->view() );
	CGPoint pos = CCDirector::sharedDirector()->convertToGL(p);

	pos.x -= cgDynamicTracking.x;
	pos.y -= cgDynamicTracking.y;

	BlockIndex = BlockManager::sharedManager()->attackBlock(pos);

	ItemManager::sharedManager()->ClickItemBox();
	if(ItemManager::sharedManager()->CheckOpen() == false) AttackManager::sharedManager()->Attack(pos);
	RenderingManager::sharedManager()->Rendering();
}

void Scene_Play::SceneScroll(ccTime dt) 
{
	CGPoint HeroPos = ObjectCore::sharedManager()->GetHeroPosition();
	CGPoint BgaPos =this->getPosition();

	CGSize winSize = CCDirector::sharedDirector()->getWinSize();
	CGPoint MinWinSize = ccp(winSize.width * 0.492f, winSize.height * 0.2f);
	CGPoint MaxWinSize = ccp(winSize.width * 0.518f, winSize.height * 0.8f);

	float fTargetWorldPosX = HeroPos.x + BgaPos.x;
	float fTargetWorldPosY = HeroPos.y + BgaPos.y;

	if( MinWinSize.x > fTargetWorldPosX ) cgDynamicTracking.x += 300.f*dt;
	if( MaxWinSize.x < fTargetWorldPosX ) cgDynamicTracking.x -= 300.f*dt;
	if( MinWinSize.y > fTargetWorldPosY ) cgDynamicTracking.y += 300.f*dt;
	if( MaxWinSize.y < fTargetWorldPosY ) cgDynamicTracking.y -= 300.f*dt;

	if(cgDynamicTracking.x > 0) cgDynamicTracking.x = 0;
	if(cgDynamicTracking.x < -(MAP_X_SIZE-1024)) cgDynamicTracking.x = -(MAP_X_SIZE-1024);

	if(cgDynamicTracking.y > 0) cgDynamicTracking.y = 0;
	if(cgDynamicTracking.y < -(MAP_Y_SIZE-600)) cgDynamicTracking.y = -(MAP_Y_SIZE-600);

	this->dynamicTracking();
}

void Scene_Play::dynamicTracking()
{
	CGPoint bgaPos = this->getPosition();

	CGPoint gap = ccp(bgaPos.x - cgDynamicTracking.x, bgaPos.y- cgDynamicTracking.y);

	gap.x /= 2;
	gap.y /= 2;

	bgaPos.x -= gap.x;
	bgaPos.y -= gap.y;	

	this->setPosition(bgaPos);
	ObjectCore::sharedManager()->SetMainBga(ccp(-bgaPos.x, -bgaPos.y));
	CGPoint debugPos = m_debug->getPosition();
	debugPos.x = -bgaPos.x + 512.f;
	debugPos.y = -bgaPos.y;
	m_debug->setPosition(debugPos);
	ItemManager::sharedManager()->SetInventoryPos(bgaPos);
	ObjectCore::sharedManager()->DebugHeart(bgaPos);
}

void Scene_Play::DebugScreen()
{
	CHAR TEXT[128];

	CGPoint MapPos = this->getPosition();
	CGPoint HeroPos = ObjectCore::sharedManager()->GetHeroPosition();

	sprintf_s(TEXT, "MapX : %.2f, MapY : %.2f, HeroX : %.2f, HeroY : %.2f, BLOCK : %d", -MapPos.x, -MapPos.y,
		HeroPos.x, HeroPos.y, BlockIndex);

	m_debug->setString(TEXT);
}