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
	// 윈도우 초기화
	if (! (m_pMainWnd = new CCXEGLView()) || ! m_pMainWnd->Create(L"GameSchool", 1024, 600)){
			delete m_pMainWnd;
			return false;
	}

	// 얻어온 윈도우 창과 엔진을 연결한다.
	CCDirector::sharedDirector()->setOpenGLView(m_pMainWnd);

	// 방향을 설정합니다. (윈도우에서는 의미 없음)
	CCDirector::sharedDirector()->setDeviceOrientation(kCCDeviceOrientationPortrait);

	// 프레임레이트를 표시합니다.
	CCDirector::sharedDirector()->setDisplayFPS(true);

	// 엔진이 초당 그려지는 이미지를 셋팅합니다.
	CCDirector::sharedDirector()->setAnimationInterval(1.0 / 60);


	// 엔진에게 실행될 Scene을 전달합니다.
	CCDirector::sharedDirector()->runWithScene( Scene_Logo::scene() );

	return true;
}

// 어플리케이션이 백그라운드로 가면 아래 함수를 실행 합니다 (아이폰의 경우)
void AppDelegate::applicationDidEnterBackground(){
    CCDirector::sharedDirector()->pause();
	// 만약 심플오디오 엔진을 사용할 경우 아래 코드를 사용하면 사운드도 정지합니다.
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// 어플리케이션이 백그라운드로부터 돌아왔을경우 이 함수를 실행 합니다 (아이폰의 경우)
void AppDelegate::applicationWillEnterForeground(){
    CCDirector::sharedDirector()->resume();
	
	// 만약 심플오디오 엔진을 사용할 경우 아래코드를 사용하면 사운드가 복귀합니다.
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
