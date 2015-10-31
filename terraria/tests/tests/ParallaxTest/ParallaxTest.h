#ifndef _PARALLAX_TEST_H_
#define _PARALLAX_TEST_H_

#include "../testBasic.h"

class ParallaxDemo : public CCLayer
{
protected:
    CCTextureAtlas* m_atlas;

public:
	ParallaxDemo(void);
	~ParallaxDemo(void);

	virtual std::string title();
	virtual void onEnter();

	void restartCallback(NSObject* pSender);
	void nextCallback(NSObject* pSender);
	void backCallback(NSObject* pSender);
};

class Parallax1 : public ParallaxDemo
{
protected:
	CCNode*		m_root;
	CCNode*		m_target;
	CCMotionStreak*		m_streak;

public:
	Parallax1();
	virtual std::string title();
};

class Parallax2 : public ParallaxDemo
{
protected:
	CCNode*		m_root;
	CCNode*		m_target;
	CCMotionStreak*		m_streak;

public:
	Parallax2();
	
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch* touch, UIEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, UIEvent* event);
	virtual void ccTouchCancelled(CCTouch* touch, UIEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, UIEvent* event);

	virtual std::string title();
};

class ParallaxTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif
