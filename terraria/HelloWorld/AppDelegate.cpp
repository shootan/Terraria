#include "cocos2d.h"
#include "AppDelegate.h"
#include "win32/Scene_Main.h"
#include "win32/Scene_Play.h"
#include "win32/Scene_Load.h"
#include "win32/Scene_Logo.h"

using namespace cocos2d;
AppDelegate::AppDelegate()
:m_pMainWnd(NULL){
}
AppDelegate::~AppDelegate(){
CCX_SAFE_DELETE(m_pMainWnd);
}
bool AppDelegate::applicationDidFinishLaunching()
{
	// ������ �ʱ�ȭ
	if (! (m_pMainWnd = new CCXEGLView()) || ! m_pMainWnd->Create(L"GameSchool", 1024, 600)){
			delete m_pMainWnd;
			return false;
	}

	// ���� ������ â�� ������ �����Ѵ�.
	CCDirector::sharedDirector()->setOpenGLView(m_pMainWnd);

	// ������ �����մϴ�. (�����쿡���� �ǹ� ����)
	CCDirector::sharedDirector()->setDeviceOrientation(kCCDeviceOrientationPortrait);

	// �����ӷ���Ʈ�� ǥ���մϴ�.
	CCDirector::sharedDirector()->setDisplayFPS(true);

	// ������ �ʴ� �׷����� �̹����� �����մϴ�.
	CCDirector::sharedDirector()->setAnimationInterval(1.0 / 60);


	// �������� ����� Scene�� �����մϴ�.
	CCDirector::sharedDirector()->runWithScene( Scene_Logo::scene() );

	return true;
}

// ���ø����̼��� ��׶���� ���� �Ʒ� �Լ��� ���� �մϴ� (�������� ���)
void AppDelegate::applicationDidEnterBackground(){
    CCDirector::sharedDirector()->pause();
	// ���� ���ÿ���� ������ ����� ��� �Ʒ� �ڵ带 ����ϸ� ���嵵 �����մϴ�.
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// ���ø����̼��� ��׶���κ��� ���ƿ������ �� �Լ��� ���� �մϴ� (�������� ���)
void AppDelegate::applicationWillEnterForeground(){
    CCDirector::sharedDirector()->resume();
	
	// ���� ���ÿ���� ������ ����� ��� �Ʒ��ڵ带 ����ϸ� ���尡 �����մϴ�.
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
