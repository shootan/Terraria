#pragma once
#include "cocos2d.h"
#include "fmod.hpp"
#include "fmod_errors.h"

#pragma comment(lib, "fmodex_vc.lib")

enum
{
	SOUND_MAIN_BGM,
	SOUND_GAME_BGM,
	SOUND_ATTACK,
	SOUND_BUTTON,
	SOUND_DIG,
	SOUND_ROOT,
	SOUND_JUMP
};

class SoundManager{
private:
	SoundManager()
	{
		instance = NULL;
	}
public:
	~SoundManager()
	{
		delete instance;
		instance = NULL;
	}

	static SoundManager* instance;
	static SoundManager* sharedManager()
	{
		if(instance==NULL) instance = new SoundManager;
		return instance;
	}

	FMOD::System*		fsystem; //FMOD 엔진
	
	FMOD::Channel*		bgaCH; // 채널
	FMOD::Channel*		effCh;

	FMOD::Sound*		m_pMainBgm;
	FMOD::Sound*		m_pGameBgm;
	FMOD::Sound*		m_pAttack;
	FMOD::Sound*		m_pButton;
	FMOD::Sound*		m_pDig;
	FMOD::Sound*		m_pRoot;
	FMOD::Sound*		m_pJump;

	FMOD_RESULT			result;


public:
	void init();
	void sndLoad();
	void play(int _val);
	void stop(int _val);
	void ERRCHECK(FMOD_RESULT reuslt);

};