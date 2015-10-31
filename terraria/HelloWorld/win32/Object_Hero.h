#pragma once
#include "cocos2d.h"

using namespace cocos2d;
#include "Object.h"

class Object_Hero : public Object
{
public:
	virtual bool init();
	virtual void tick(ccTime dt);

	float getSpeed();

	void LoadingAnimation();

	void setWeapon(float _r)
	{
		WeaponRotate  = _r - 90.f;
		AttackOn = true;
	}

	int GetLiveFlag()
	{
		return m_iLiveFlag;
	}

	void SetDamage(int _damage, int _dir)
	{
		if(RecentDamage == false)
		{
			m_iLiveFlag -= _damage;
			RecentDamage = true;
			EnemyDir = _dir;
		}
	}

	void KnockBack(ccTime dt);

protected:
	void animation(ccTime dt);
	void action(ccTime dt);

	void Attack(ccTime dt);

	CGPoint m_TrackingPoint;
	CCSprite* m_pRender;

	CGRect Rect;

	bool JumpCheck;
	float RealSpeed;

	CCSprite* Weapon;
	bool AttackOn;
	float WeaponRotate;
	float AttackTime;

	bool RecentDamage;
	int m_iLiveFlag;
	float DamageTime;

	int EnemyDir;
};

