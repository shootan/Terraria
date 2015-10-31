#include "SoundManager.h"

void SoundManager::init()
{
	result = FMOD::System_Create(&fsystem);
	ERRCHECK(result);

	fsystem->init(100, FMOD_INIT_NORMAL, NULL);
	ERRCHECK(result);

}

void SoundManager::sndLoad()
{
	result = fsystem->createSound("Sound/MainBgm.mp3", FMOD_LOOP_NORMAL, 0, &m_pMainBgm);
	ERRCHECK(result);

	result = fsystem->createSound("Sound/GameBgm.mp3", FMOD_LOOP_NORMAL, 0, &m_pGameBgm);
	ERRCHECK(result);

	result = fsystem->createSound("Sound/Sword.mp3", FMOD_DEFAULT, 0, &m_pAttack);
	ERRCHECK(result);

	result = fsystem->createSound("Sound/Button.mp3", FMOD_DEFAULT, 0, &m_pButton);
	ERRCHECK(result);

	result = fsystem->createSound("Sound/Dig.mp3", FMOD_DEFAULT, 0, &m_pDig);
	ERRCHECK(result);

	result = fsystem->createSound("Sound/Root.mp3", FMOD_DEFAULT, 0, &m_pRoot);
	ERRCHECK(result);

	result = fsystem->createSound("Sound/Jump.wav", FMOD_DEFAULT, 0, &m_pJump);
	ERRCHECK(result);

	

}
void SoundManager::play(int _val)
{
	fsystem->update();
	switch(_val)
	{
	case SOUND_MAIN_BGM:
		{
			fsystem->playSound(FMOD_CHANNEL_FREE, m_pMainBgm, false, &bgaCH);
			ERRCHECK(result);
			break;
		}
	case SOUND_GAME_BGM:
		{
			fsystem->playSound(FMOD_CHANNEL_FREE, m_pGameBgm, false, &bgaCH);
			ERRCHECK(result);
			break;
		}
	case SOUND_ATTACK:
		{
			fsystem->playSound(FMOD_CHANNEL_FREE, m_pAttack, false, &effCh);
			ERRCHECK(result);
			break;
		}
	case SOUND_BUTTON:
		{
			fsystem->playSound(FMOD_CHANNEL_FREE, m_pButton, false, &effCh);
			ERRCHECK(result);
			break;
		}
	case SOUND_DIG:
		{
			fsystem->playSound(FMOD_CHANNEL_FREE, m_pDig, false, &effCh);
			ERRCHECK(result);
			break;
		}
	case SOUND_ROOT:
		{
			fsystem->playSound(FMOD_CHANNEL_FREE, m_pRoot, false, &effCh);
			ERRCHECK(result);
			break;
		}
	case SOUND_JUMP:
		{
			fsystem->playSound(FMOD_CHANNEL_FREE, m_pJump, false, &effCh);
			ERRCHECK(result);
			break;
		}
	}
}

void SoundManager::stop(int _val)
{
	switch(_val)
	{
	case 0:
		bgaCH->stop();
		break;

	case 1:
		effCh->stop();
		break;
	}
}


void SoundManager::ERRCHECK(FMOD_RESULT result)
{
	TCHAR error[256];
	if(result!=FMOD_OK)
	{
		
	}
}